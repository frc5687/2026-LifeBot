#include "subsystem/elevator/ElevatorSubsystem.h"

#include <utility>

#include "subsystem/elevator/ElevatorConstants.h"

ElevatorSubsystem::ElevatorSubsystem(std::unique_ptr<ElevatorIO> io)
    : LoggedSubsystem("Elevator"), m_io{std::move(io)} {
  m_io->UpdateInputs(m_inputs);
}

void ElevatorSubsystem::SetElevatorHeight(units::meter_t height) {
  if (!m_inputs.configured) {
    m_io->Stop();
    return;
  }

  m_io->SetHeight(height);
}

void ElevatorSubsystem::StopElevator() {
  m_io->Stop();
}

bool ElevatorSubsystem::ZeroAtBottom() {
  const bool zeroed = m_io->ZeroAtBottom();
  m_io->UpdateInputs(m_inputs);
  return zeroed;
}

void ElevatorSubsystem::UpdateInputs() {
  m_io->UpdateInputs(m_inputs);

  m_averageHeight = (m_inputs.leftHeight + m_inputs.rightHeight) / 2.0;
}

void ElevatorSubsystem::LogTelemetry() {
  Log("Configured", m_inputs.configured);
  Log("LeftHeightMeters", m_inputs.leftHeight.value());
  Log("RightHeightMeters", m_inputs.rightHeight.value());
  Log("AverageHeightMeters", m_averageHeight.value());
  Log("SideToSideErrorMeters",
      (m_inputs.leftHeight - m_inputs.rightHeight).value());
}
