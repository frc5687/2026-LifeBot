#include "subsystem/elevator/ElevatorSubsystem.h"

#include <utility>

#include "subsystem/elevator/ElevatorConstants.h"

ElevatorSubsystem::ElevatorSubsystem(std::unique_ptr<ElevatorIO> io)
    : LoggedSubsystem("Elevator"), m_io{std::move(io)} {
  m_io->UpdateInputs(m_inputs);
}

void ElevatorSubsystem::SetElevatorHeight(units::meter_t height) {
  m_io->SetHeight(height);
}


bool ElevatorSubsystem::AtSetpoint(){
  if ( m_desiredPostion - m_inputs.elevatorHeight < ElevatorConstants::kPositionTolorance){
      return true;}
  else{
    return false;
  }
}

void ElevatorSubsystem::UpdateInputs() {
  m_io->UpdateInputs(m_inputs);
}

void ElevatorSubsystem::LogTelemetry() {
  Log("ElevatorHeight", m_inputs.elevatorHeight.value());
  Log("ElevatorVelocity", m_inputs.elevatorVelocity.value());
  Log("ElevatorDesiredHeight", m_inputs.desiredElevatorHeight.value());
}
