#pragma once

#include <units/length.h>

struct ElevatorIOInputs {
  units::meter_t leftHeight{0_m};
  units::meter_t rightHeight{0_m};
  bool configured{false};
};

/**
 * Hardware abstraction for the elevator.
 *
 * The subsystem talks to this interface instead of directly talking to CTRE.
 * That makes it possible to add a simulation implementation later.
 */
class ElevatorIO {
 public:
  virtual ~ElevatorIO() = default;

  virtual void UpdateInputs(ElevatorIOInputs& inputs) = 0;
  virtual void SetHeight(units::meter_t height) = 0;
  virtual void Stop() = 0;

  /**
   * Call ONLY when the elevator is physically resting at its known bottom
   * position. There is no limit switch, so software cannot independently
   * verify that condition.
   */
  virtual bool ZeroAtBottom() = 0;
};
