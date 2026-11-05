#pragma once

#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/controls/MotionMagicVoltage.hpp>
#include <units/length.h>

#include "subsystem/elevator/ElevatorIO.h"
#include "utils/CANDevice.h"

class CTREElevatorIO final : public ElevatorIO {
 public:
  CTREElevatorIO(CANDevice leftMotor, CANDevice rightMotor,
                 CANDevice leftEncoder, CANDevice rightEncoder);

  void UpdateInputs(ElevatorIOInputs& inputs) override;
  void SetHeight(units::meter_t height) override;
  void Stop() override;
  bool ZeroAtBottom() override;

 private:
  bool ConfigureHardware();

  ctre::phoenix6::hardware::TalonFX m_leftMotor;
  ctre::phoenix6::hardware::TalonFX m_rightMotor;
  ctre::phoenix6::hardware::CANcoder m_leftEncoder;
  ctre::phoenix6::hardware::CANcoder m_rightEncoder;

  ctre::phoenix6::controls::MotionMagicVoltage m_leftMotionRequest{0_tr};
  ctre::phoenix6::controls::MotionMagicVoltage m_rightMotionRequest{0_tr};

  bool m_configured{false};
};
