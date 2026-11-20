#pragma once

#include <units/length.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/angular_velocity.h>

struct ElevatorIOInputs {
  units::turn_t leftMotorPosition{0_tr};
  units::turn_t rightMotorPosition{0_tr};
  units::turns_per_second_t leftMotorVelocity{0_tps};
  units::turns_per_second_t rightMotorVelocity{0_tps};

  units::meter_t elevatorHeight{0_m};
  units::meter_t desiredElevatorHeight{0_m};

  units::meters_per_second_t elevatorVelocity{0_mps};
};


class ElevatorIO {
 public:
  virtual ~ElevatorIO() = default;

  virtual void UpdateInputs(ElevatorIOInputs& inputs) = 0;
  virtual void SetHeight(units::meter_t height) = 0;
  virtual void SetVoltage(units::volt_t voltage){}

  virtual bool AtSetpoint() = 0;
};
