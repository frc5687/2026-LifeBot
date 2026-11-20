// #include "subsystem/elevator/CTREElevatorIO.h"

// #include <algorithm>
// #include <cmath>
// #include <numbers>
// #include <string>

// #include <ctre/phoenix6/CANcoder.hpp>
// #include <ctre/phoenix6/TalonFX.hpp>
// #include <ctre/phoenix6/signals/SpnEnums.hpp>

// #include "subsystem/elevator/ElevatorConstants.h"

// using namespace ctre::phoenix6;

// namespace {
// std::string BusName(CANDevice device) {
//   return std::string{device.bus};
// }

// // Converts linear elevator travel into rotations of the mechanism (the drum).
// units::turn_t HeightToMechanismRotations(units::meter_t height) {
//   const auto metersPerRotation =
//       (ElevatorConstants::kDrumRadius * std::numbers::pi) *
//       ElevatorConstants::kStageTravelPerDrumRotation;
//   return units::turn_t{height.value() / metersPerRotation.value()};
// }

// units::meter_t MechanismRotationsToHeight(units::turn_t rotations) {
//   const auto metersPerRotation =
//       (ElevatorConstants::kDrumRadius * std::numbers::pi) *
//       ElevatorConstants::kStageTravelPerDrumRotation;
//   return units::meter_t{rotations.value() * metersPerRotation.value()};
// }
// }  // namespace

// CTREElevatorIO::CTREElevatorIO(CANDevice leftMotor, CANDevice rightMotor,
//                                CANDevice leftEncoder, CANDevice rightEncoder)
//     : m_leftMotor{leftMotor.id, BusName(leftMotor)},
//       m_rightMotor{rightMotor.id, BusName(rightMotor)},
//       m_leftEncoder{leftEncoder.id, BusName(leftEncoder)},
//       m_rightEncoder{rightEncoder.id, BusName(rightEncoder)} {
//   m_configured = ConfigureHardware();
// }

// bool CTREElevatorIO::ConfigureHardware() {
//   // Do not arm the mechanism with incomplete mechanical constants.
//   if (ElevatorConstants::kGearRatio <= 0.0 ||
//       ElevatorConstants::kDrumRadius <= 0_m ||
//       ElevatorConstants::kStageTravelPerDrumRotation <= 0.0 ||
//       ElevatorConstants::kMaxHeight <= 0_m ||
//       ElevatorConstants::kMotionMagicCruiseVelocity <= 0.0 ||
//       ElevatorConstants::kMotionMagicAcceleration <= 0.0) {
//     Stop();
//     return false;
//   }

//   // Configure each CANcoder's positive direction. The two encoders may be
//   // mounted as mirror images, so set these independently after checking them.
//   configs::CANcoderConfiguration leftEncoderConfig{};
//   leftEncoderConfig.MagnetSensor.SensorDirection =
//       ElevatorConstants::kLeftEncoderCounterClockwisePositive
//           ? signals::SensorDirectionValue::CounterClockwise_Positive
//           : signals::SensorDirectionValue::Clockwise_Positive;
//   m_leftEncoder.GetConfigurator().Apply(leftEncoderConfig);

//   configs::CANcoderConfiguration rightEncoderConfig{};
//   rightEncoderConfig.MagnetSensor.SensorDirection =
//       ElevatorConstants::kRightEncoderCounterClockwisePositive
//           ? signals::SensorDirectionValue::CounterClockwise_Positive
//           : signals::SensorDirectionValue::Clockwise_Positive;
//   m_rightEncoder.GetConfigurator().Apply(rightEncoderConfig);

//   // The CANcoders are remote feedback sensors for their respective Talon FXs.
//   // SensorToMechanismRatio is encoder rotations per drum/mechanism rotation.
//   configs::TalonFXConfiguration leftConfig{};
//   leftConfig.Feedback.FeedbackRemoteSensorID = m_leftEncoder.GetDeviceID();
//   leftConfig.Feedback.FeedbackSensorSource =
//       signals::FeedbackSensorSourceValue::RemoteCANcoder;
//   leftConfig.Feedback.SensorToMechanismRatio =
//       ElevatorConstants::kGearRatio;
//   leftConfig.Slot0.kP = ElevatorConstants::kP;
//   leftConfig.Slot0.kI = ElevatorConstants::kI;
//   leftConfig.Slot0.kD = ElevatorConstants::kD;
//   leftConfig.MotionMagic.MotionMagicCruiseVelocity =
//       ElevatorConstants::kMotionMagicCruiseVelocity;
//   leftConfig.MotionMagic.MotionMagicAcceleration =
//       ElevatorConstants::kMotionMagicAcceleration;
//   leftConfig.MotorOutput.NeutralMode = signals::NeutralModeValue::Brake;
//   leftConfig.MotorOutput.Inverted =
//       ElevatorConstants::kLeftMotorInverted
//           ? signals::InvertedValue::Clockwise_Positive
//           : signals::InvertedValue::CounterClockwise_Positive;

//   configs::TalonFXConfiguration rightConfig{};
//   rightConfig.Feedback.FeedbackRemoteSensorID = m_rightEncoder.GetDeviceID();
//   rightConfig.Feedback.FeedbackSensorSource =
//       signals::FeedbackSensorSourceValue::RemoteCANcoder;
//   rightConfig.Feedback.SensorToMechanismRatio =
//       ElevatorConstants::kGearRatio;
//   rightConfig.Slot0.kP = ElevatorConstants::kP;
//   rightConfig.Slot0.kI = ElevatorConstants::kI;
//   rightConfig.Slot0.kD = ElevatorConstants::kD;
//   rightConfig.MotionMagic.MotionMagicCruiseVelocity =
//       ElevatorConstants::kMotionMagicCruiseVelocity;
//   rightConfig.MotionMagic.MotionMagicAcceleration =
//       ElevatorConstants::kMotionMagicAcceleration;
//   rightConfig.MotorOutput.NeutralMode = signals::NeutralModeValue::Brake;
//   rightConfig.MotorOutput.Inverted =
//       ElevatorConstants::kRightMotorInverted
//           ? signals::InvertedValue::Clockwise_Positive
//           : signals::InvertedValue::CounterClockwise_Positive;

//   const auto leftStatus = m_leftMotor.GetConfigurator().Apply(leftConfig);
//   const auto rightStatus = m_rightMotor.GetConfigurator().Apply(rightConfig);

//   Stop();
//   return leftStatus.IsOK() && rightStatus.IsOK();
// }

// void CTREElevatorIO::UpdateInputs(ElevatorIOInputs& inputs) {


//   // Talon position is expressed in mechanism rotations because of the
//   // SensorToMechanismRatio configured above.

//   inputs.elevatorHeight =  MechanismRotationsToHeight(m_leftMotor.GetPosition().GetValue() + m_rightMotor.GetPosition().GetValue() /2);
// }
//   inputs.leftHeight =
//       MechanismRotationsToHeight(m_leftMotor.GetPosition().GetValue());
//   inputs.rightHeight =
//       MechanismRotationsToHeight(m_rightMotor.GetPosition().GetValue());
// }

// void CTREElevatorIO::SetHeight(units::meter_t height) {
//   if (!m_configured) {
//     Stop();
//     return;
//   }

//   const auto safeHeight =
//       std::clamp(height, 0_m, ElevatorConstants::kMaxHeight);
//   const auto targetRotations = HeightToMechanismRotations(safeHeight);

//   // Both sides receive the same position target, but each Talon closes its
//   // own loop using its own CANcoder. This lets us monitor side-to-side skew.
//   m_leftMotor.SetControl(m_leftMotionRequest.WithPosition(targetRotations));
//   m_rightMotor.SetControl(m_rightMotionRequest.WithPosition(targetRotations));
// }

// void CTREElevatorIO::Stop() {
//   m_leftMotor.StopMotor();
//   m_rightMotor.StopMotor();
// }

// bool CTREElevatorIO::ZeroAtBottom() {
//   if (!m_configured) {
//     Stop();
//     return false;
//   }

//   // This is a deliberate operator action, NOT something to do automatically
//   // at startup. Only call when the carriage is physically at the bottom.
//   const auto leftStatus = m_leftEncoder.SetPosition(0_tr);
//   const auto rightStatus = m_rightEncoder.SetPosition(0_tr);

//   Stop();
//   return leftStatus.IsOK() && rightStatus.IsOK();
// }
#include "subsystem/elevator/CTREElevatorIO.h"

#include "ctre/phoenix6/StatusSignal.hpp"
#include "subsystem/elevator/ElevatorConstants.h"
#include "subsystem/elevator/ElevatorIO.h"
#include "units/velocity.h"
#include "units/voltage.h"

CTREElevatorIO::CTREElevatorIO(const CANDevice& leftMotor,
                               const CANDevice& rightMotor)
    : m_leftMotor(leftMotor.id, leftMotor.bus),
      m_rightMotor(rightMotor.id, rightMotor.bus),
      m_leftMotorPositionSignal(m_leftMotor.GetPosition()),
      m_leftMotorVelocitySignal(m_leftMotor.GetVelocity()),
      m_leftCurrentSignal(m_leftMotor.GetStatorCurrent()),
      m_rightMotorPositionSignal(m_rightMotor.GetPosition()),
      m_rightMotorVelocitySignal(m_rightMotor.GetVelocity()),
      m_rightCurrentSignal(m_rightMotor.GetStatorCurrent()),
      m_batchSignals{&m_leftMotorPositionSignal,  &m_leftMotorVelocitySignal,
                     &m_leftCurrentSignal,        &m_rightMotorPositionSignal,
                     &m_rightMotorVelocitySignal, &m_rightCurrentSignal},
      m_leftController(0_tr),
      m_rightController(0_tr),
      m_leftVoltage(0_V),
      m_rightVoltage(0_V) {
  m_leftConfig.MotorOutput.Inverted =
      ElevatorConstants::kLeftMotorInverted
          ? ctre::phoenix6::signals::InvertedValue::Clockwise_Positive
          : ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive;

  m_rightConfig.MotorOutput.Inverted =
      ElevatorConstants::kRightMotorInverted
          ? ctre::phoenix6::signals::InvertedValue::Clockwise_Positive
          : ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive;

  m_leftConfig.Voltage.PeakForwardVoltage = 12_V;
  m_leftConfig.Voltage.PeakReverseVoltage = -12_V;

  m_rightConfig.Voltage.PeakForwardVoltage = 12_V;
  m_rightConfig.Voltage.PeakReverseVoltage = -12_V;

  m_leftConfig.Slot0.kP = ElevatorConstants::kP;
  m_leftConfig.Slot0.kI = ElevatorConstants::kI;
  m_leftConfig.Slot0.kD = ElevatorConstants::kD;

  m_rightConfig.Slot0.kP = ElevatorConstants::kP;
  m_rightConfig.Slot0.kI = ElevatorConstants::kI;
  m_rightConfig.Slot0.kD = ElevatorConstants::kD;

  m_leftConfig.MotionMagic.MotionMagicCruiseVelocity =
      ElevatorConstants::kMaxVelocity / ElevatorConstants::kDrumRadius *
      ElevatorConstants::kGearRatio * 1_tr;
  m_leftConfig.MotionMagic.MotionMagicAcceleration =
      ElevatorConstants::kMaxAcceleration / ElevatorConstants::kDrumRadius *
      ElevatorConstants::kGearRatio * 1_tr;
  m_leftConfig.MotionMagic.MotionMagicJerk = 10000_tr_per_s_cu;

  m_rightConfig.MotionMagic.MotionMagicCruiseVelocity =
      ElevatorConstants::kMaxVelocity / ElevatorConstants::kDrumRadius *
      ElevatorConstants::kGearRatio * 1_tr;
  m_rightConfig.MotionMagic.MotionMagicAcceleration =
      ElevatorConstants::kMaxAcceleration / ElevatorConstants::kDrumRadius *
      ElevatorConstants::kGearRatio * 1_tr;
  m_rightConfig.MotionMagic.MotionMagicJerk = 10000_tr_per_s_cu;

  m_leftMotor.GetConfigurator().Apply(m_leftConfig);
  m_rightMotor.GetConfigurator().Apply(m_rightConfig);
}

void CTREElevatorIO::UpdateInputs(ElevatorIOInputs& inputs) {
  ctre::phoenix6::BaseStatusSignal::RefreshAll(m_batchSignals);

  inputs.leftMotorPosition = m_leftMotorPositionSignal.GetValue();
  inputs.rightMotorPosition = m_rightMotorPositionSignal.GetValue();

  units::meter_t leftPositionMeters = inputs.leftMotorPosition *
                                      ElevatorConstants::kCircumference /
                                      ElevatorConstants::kGearRatio / 1_tr;
  units::meter_t rightPositionMeters = inputs.rightMotorPosition *
                                       ElevatorConstants::kCircumference /
                                       ElevatorConstants::kGearRatio / 1_tr;

  inputs.elevatorHeight = (leftPositionMeters + rightPositionMeters) / 2.0;

  inputs.leftMotorVelocity = m_leftMotorVelocitySignal.GetValue();
  inputs.rightMotorVelocity = m_rightMotorVelocitySignal.GetValue();

  units::meters_per_second_t leftVelocity =
      inputs.leftMotorVelocity * ElevatorConstants::kCircumference /
      ElevatorConstants::kGearRatio / 1_tr;
  units::meters_per_second_t rightVelocity =
      inputs.rightMotorVelocity * ElevatorConstants::kCircumference /
      ElevatorConstants::kGearRatio / 1_tr;

  inputs.elevatorVelocity = (leftVelocity + rightVelocity) / 2.0;

  // inputs.timestamp = frc::Timer::GetFPGATimestamp();
}

void CTREElevatorIO::SetHeight(units::meter_t desiredHeight) {
  units::turn_t leftMotorTurns = desiredHeight /
                                 ElevatorConstants::kCircumference *
                                 ElevatorConstants::kGearRatio * 1_tr;
  units::turn_t rightMotorTurns = desiredHeight /
                                  ElevatorConstants::kCircumference *
                                  ElevatorConstants::kGearRatio * 1_tr;

  m_leftMotor.SetControl(m_leftController.WithPosition(leftMotorTurns));
  m_rightMotor.SetControl(m_rightController.WithPosition(rightMotorTurns));
}

void CTREElevatorIO::SetVoltage(units::volt_t voltage) {
  m_rightMotor.SetControl(m_rightVoltage.WithOutput(voltage));
  m_leftMotor.SetControl(m_leftVoltage.WithOutput(voltage));
}
