#pragma once

#include <memory>

#include <units/length.h>

#include "subsystem/LoggedSubsystem.h"
#include "subsystem/elevator/ElevatorIO.h"

class ElevatorSubsystem final : public LoggedSubsystem {
 public:
  explicit ElevatorSubsystem(std::unique_ptr<ElevatorIO> io);
  ~ElevatorSubsystem() = default;
  void SetElevatorHeight(units::meter_t desiredHeight);
  bool AtSetpoint();

 protected:
  void UpdateInputs() override;
  void LogTelemetry() override;

 private:
  std::unique_ptr<ElevatorIO> m_io;
  ElevatorIOInputs m_inputs{};
  units::meter_t m_desiredPostion{0_m};
};
