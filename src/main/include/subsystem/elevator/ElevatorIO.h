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

  virtual void UpdateInputs(ElevatorIOInputs& inputs) = 0;
  virtual void SetHeight(units::meter_t height) = 0;
  virtual void Stop() = 0;


  virtual bool ZeroAtBottom() = 0;
};
