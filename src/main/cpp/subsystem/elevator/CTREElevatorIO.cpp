#include "subsystem/elevator/CTREElevatorIO.h"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <string>

#include <ctre/phoenix6/configs/CANcoderConfigs.hpp>
#include <ctre/phoenix6/configs/TalonFXConfigs.hpp>
#include <ctre/phoenix6/signals/SpnEnums.hpp>

#include "subsystem/elevator/ElevatorConstants.h"

using namespace ctre::phoenix6;

namespace {
std::string BusName(CANDevice device) {
  return std::string{device.bus};
}

// Converts linear elevator travel into rotations of the mechanism (the drum).
units::turn_t HeightToMechanismRotations(units::meter_t height) {
  const auto metersPerRotation =
      (ElevatorConstants::kDrumDiameter * std::numbers::pi) *
      ElevatorConstants::kStageTravelPerDrumRotation;
  return units::turn_t{height.value() / metersPerRotation.value()};
}

units::meter_t MechanismRotationsToHeight(units::turn_t rotations) {
  const auto metersPerRotation =
      (ElevatorConstants::kDrumDiameter * std::numbers::pi) *
      ElevatorConstants::kStageTravelPerDrumRotation;
  return units::meter_t{rotations.value() * metersPerRotation.value()};
}
}  // namespace

CTREElevatorIO::CTREElevatorIO(CANDevice leftMotor, CANDevice rightMotor,
                               CANDevice leftEncoder, CANDevice rightEncoder)
    : m_leftMotor{leftMotor.id, BusName(leftMotor)},
      m_rightMotor{rightMotor.id, BusName(rightMotor)},
      m_leftEncoder{leftEncoder.id, BusName(leftEncoder)},
      m_rightEncoder{rightEncoder.id, BusName(rightEncoder)} {
  m_configured = ConfigureHardware();
}

bool CTREElevatorIO::ConfigureHardware() {
  // Do not arm the mechanism with incomplete mechanical constants.
  if (ElevatorConstants::kGearReduction <= 0.0 ||
      ElevatorConstants::kDrumDiameter <= 0_m ||
      ElevatorConstants::kStageTravelPerDrumRotation <= 0.0 ||
      ElevatorConstants::kMaxHeight <= 0_m ||
      ElevatorConstants::kMotionMagicCruiseVelocity <= 0.0 ||
      ElevatorConstants::kMotionMagicAcceleration <= 0.0) {
    Stop();
    return false;
  }

  // Configure each CANcoder's positive direction. The two encoders may be
  // mounted as mirror images, so set these independently after checking them.
  configs::CANcoderConfiguration leftEncoderConfig{};
  leftEncoderConfig.MagnetSensor.SensorDirection =
      ElevatorConstants::kLeftEncoderCounterClockwisePositive
          ? signals::SensorDirectionValue::CounterClockwise_Positive
          : signals::SensorDirectionValue::Clockwise_Positive;
  m_leftEncoder.GetConfigurator().Apply(leftEncoderConfig);

  configs::CANcoderConfiguration rightEncoderConfig{};
  rightEncoderConfig.MagnetSensor.SensorDirection =
      ElevatorConstants::kRightEncoderCounterClockwisePositive
          ? signals::SensorDirectionValue::CounterClockwise_Positive
          : signals::SensorDirectionValue::Clockwise_Positive;
  m_rightEncoder.GetConfigurator().Apply(rightEncoderConfig);

  // The CANcoders are remote feedback sensors for their respective Talon FXs.
  // SensorToMechanismRatio is encoder rotations per drum/mechanism rotation.
  configs::TalonFXConfiguration leftConfig{};
  leftConfig.Feedback.FeedbackRemoteSensorID = m_leftEncoder.GetDeviceID();
  leftConfig.Feedback.FeedbackSensorSource =
      signals::FeedbackSensorSourceValue::RemoteCANcoder;
  leftConfig.Feedback.SensorToMechanismRatio =
      ElevatorConstants::kGearReduction;
  leftConfig.Slot0.kP = ElevatorConstants::kP;
  leftConfig.Slot0.kI = ElevatorConstants::kI;
  leftConfig.Slot0.kD = ElevatorConstants::kD;
  leftConfig.MotionMagic.MotionMagicCruiseVelocity =
      ElevatorConstants::kMotionMagicCruiseVelocity;
  leftConfig.MotionMagic.MotionMagicAcceleration =
      ElevatorConstants::kMotionMagicAcceleration;
  leftConfig.MotorOutput.NeutralMode = signals::NeutralModeValue::Brake;
  leftConfig.MotorOutput.Inverted =
      ElevatorConstants::kLeftMotorInverted
          ? signals::InvertedValue::Clockwise_Positive
          : signals::InvertedValue::CounterClockwise_Positive;

  configs::TalonFXConfiguration rightConfig{};
  rightConfig.Feedback.FeedbackRemoteSensorID = m_rightEncoder.GetDeviceID();
  rightConfig.Feedback.FeedbackSensorSource =
      signals::FeedbackSensorSourceValue::RemoteCANcoder;
  rightConfig.Feedback.SensorToMechanismRatio =
      ElevatorConstants::kGearReduction;
  rightConfig.Slot0.kP = ElevatorConstants::kP;
  rightConfig.Slot0.kI = ElevatorConstants::kI;
  rightConfig.Slot0.kD = ElevatorConstants::kD;
  rightConfig.MotionMagic.MotionMagicCruiseVelocity =
      ElevatorConstants::kMotionMagicCruiseVelocity;
  rightConfig.MotionMagic.MotionMagicAcceleration =
      ElevatorConstants::kMotionMagicAcceleration;
  rightConfig.MotorOutput.NeutralMode = signals::NeutralModeValue::Brake;
  rightConfig.MotorOutput.Inverted =
      ElevatorConstants::kRightMotorInverted
          ? signals::InvertedValue::Clockwise_Positive
          : signals::InvertedValue::CounterClockwise_Positive;

  const auto leftStatus = m_leftMotor.GetConfigurator().Apply(leftConfig);
  const auto rightStatus = m_rightMotor.GetConfigurator().Apply(rightConfig);

  Stop();
  return leftStatus.IsOK() && rightStatus.IsOK();
}

void CTREElevatorIO::UpdateInputs(ElevatorIOInputs& inputs) {
  inputs.configured = m_configured;

  if (!m_configured) {
    inputs.leftHeight = 0_m;
    inputs.rightHeight = 0_m;
    return;
  }

  // Talon position is expressed in mechanism rotations because of the
  // SensorToMechanismRatio configured above.
  inputs.leftHeight =
      MechanismRotationsToHeight(m_leftMotor.GetPosition().GetValue());
  inputs.rightHeight =
      MechanismRotationsToHeight(m_rightMotor.GetPosition().GetValue());
}

void CTREElevatorIO::SetHeight(units::meter_t height) {
  if (!m_configured) {
    Stop();
    return;
  }

  const auto safeHeight =
      std::clamp(height, 0_m, ElevatorConstants::kMaxHeight);
  const auto targetRotations = HeightToMechanismRotations(safeHeight);

  // Both sides receive the same position target, but each Talon closes its
  // own loop using its own CANcoder. This lets us monitor side-to-side skew.
  m_leftMotor.SetControl(m_leftMotionRequest.WithPosition(targetRotations));
  m_rightMotor.SetControl(m_rightMotionRequest.WithPosition(targetRotations));
}

void CTREElevatorIO::Stop() {
  m_leftMotor.StopMotor();
  m_rightMotor.StopMotor();
}

bool CTREElevatorIO::ZeroAtBottom() {
  if (!m_configured) {
    Stop();
    return false;
  }

  // This is a deliberate operator action, NOT something to do automatically
  // at startup. Only call when the carriage is physically at the bottom.
  const auto leftStatus = m_leftEncoder.SetPosition(0_tr);
  const auto rightStatus = m_rightEncoder.SetPosition(0_tr);

  Stop();
  return leftStatus.IsOK() && rightStatus.IsOK();
}
