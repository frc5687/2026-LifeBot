// #pragma once

// #include <ctre/phoenix6/CANcoder.hpp>
// #include <ctre/phoenix6/TalonFX.hpp>
// #include <ctre/phoenix6/controls/MotionMagicVoltage.hpp>
// #include <units/length.h>

// #include "subsystem/elevator/ElevatorIO.h"
// #include "utils/CANDevice.h"

// class CTREElevatorIO final : public ElevatorIO {
//  public:
//   CTREElevatorIO(CANDevice leftMotor, CANDevice rightMotor,
//                  CANDevice leftEncoder, CANDevice rightEncoder);

//   void UpdateInputs(ElevatorIOInputs& inputs) override;
//   void SetHeight(units::meter_t height) override;
//   void Stop() override;
//   bool ZeroAtBottom() override;

//  private:
//   bool ConfigureHardware();

//   ctre::phoenix6::hardware::TalonFX m_leftMotor;
//   ctre::phoenix6::hardware::TalonFX m_rightMotor;
//   ctre::phoenix6::hardware::CANcoder m_leftEncoder;
//   ctre::phoenix6::hardware::CANcoder m_rightEncoder;

//   ctre::phoenix6::controls::MotionMagicVoltage m_leftMotionRequest{0_tr};
//   ctre::phoenix6::controls::MotionMagicVoltage m_rightMotionRequest{0_tr};

//   bool m_configured{false};
// };
#pragma once

#include "ElevatorIO.h"
#include "ctre/phoenix6/StatusSignal.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/controls/MotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/VoltageOut.hpp"
#include "ctre/phoenix6/core/CoreTalonFX.hpp"
#include "units/angle.h"
#include "units/angular_velocity.h"
#include "utils/CANDevice.h"

class CTREElevatorIO : public ElevatorIO {
 public:
  CTREElevatorIO(const CANDevice& leftMotor, const CANDevice& rightMotor);
  void UpdateInputs(ElevatorIOInputs& inputs) override;
  void SetHeight(units::meter_t desiredHeight) override;
  void SetVoltage(units::volt_t voltage) override;

 private:
  ctre::phoenix6::hardware::TalonFX m_leftMotor;
  ctre::phoenix6::hardware::TalonFX m_rightMotor;

  // Remember that CTRE singals are OWNED by the motor, so we just get a
  // reference to that signal
  ctre::phoenix6::StatusSignal<units::turn_t>& m_leftMotorPositionSignal;
  ctre::phoenix6::StatusSignal<units::turns_per_second_t>&
      m_leftMotorVelocitySignal;
  ctre::phoenix6::StatusSignal<units::ampere_t>& m_leftCurrentSignal;

  ctre::phoenix6::StatusSignal<units::turn_t>& m_rightMotorPositionSignal;
  ctre::phoenix6::StatusSignal<units::turns_per_second_t>&
      m_rightMotorVelocitySignal;
  ctre::phoenix6::StatusSignal<units::ampere_t>& m_rightCurrentSignal;

  std::array<ctre::phoenix6::BaseStatusSignal*, 6> m_batchSignals;

  // ctre::phoenix6::controls::PositionVoltage m_leftController;
  // ctre::phoenix6::controls::PositionVoltage m_rightController;

  ctre::phoenix6::controls::MotionMagicVoltage m_leftController;
  ctre::phoenix6::controls::MotionMagicVoltage m_rightController;

  ctre::phoenix6::controls::VoltageOut m_leftVoltage;
  ctre::phoenix6::controls::VoltageOut m_rightVoltage;

  ctre::phoenix6::configs::TalonFXConfiguration m_leftConfig{};
  ctre::phoenix6::configs::TalonFXConfiguration m_rightConfig{};
};
