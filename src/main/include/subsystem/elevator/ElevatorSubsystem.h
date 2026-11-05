#pragma once

#include <memory>

#include <units/length.h>

#include "subsystem/LoggedSubsystem.h"
#include "subsystem/elevator/ElevatorIO.h"

class ElevatorSubsystem final : public LoggedSubsystem {
 public:
  explicit ElevatorSubsystem(std::unique_ptr<ElevatorIO> io);

  /**
   * Request a target height above the calibrated bottom position.
   * The target is clamped to the configured software travel range.
   */
  void SetElevatorHeight(units::meter_t height);

  void StopElevator();

  /**
   * Manually establish zero. The elevator must already be physically at the
   * bottom, with the mechanism supported and the robot safely disabled.
   */
  bool ZeroAtBottom();

  units::meter_t GetHeight() const { return m_averageHeight; }
  bool IsConfigured() const { return m_inputs.configured; }

 protected:
  void UpdateInputs() override;
  void LogTelemetry() override;

 private:
  std::unique_ptr<ElevatorIO> m_io;
  ElevatorIOInputs m_inputs{};

  units::meter_t m_averageHeight{0_m};
};
