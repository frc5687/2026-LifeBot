#pragma once

#include <units/length.h>
#include <units/velocity.h>

struct ElevatorIOInputs {
  units::meter_t elevatorHeight{0_m};
  units::meters_per_second_t elevatorVelocity{0_mps};
};


class ElevatorIO {
 public:
  virtual ~ElevatorIO() = default;

  virtual void UpdateInputs(ElevatorIOInputs& inputs);
  virtual void SetHeight(units::meter_t height);


  virtual bool AtSetpoint();
};
