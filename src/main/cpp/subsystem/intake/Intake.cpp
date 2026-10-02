#include "subsystem/intake/Intake.h"

Intake::Intake(std::unique_ptr<IntakeIO> io) :
    LoggedSubsystem("Intake"),
    m_io(std::move(io)) {
}

void Intake::UpdateInputs() {
    m_io->UpdateInputs(m_inputs);
}

void Intake::SetRoller1Velocity(units::radians_per_second_t roller1DesiredVelocity) {
    m_roller1DesiredVelocity = roller1DesiredVelocity;
    m_io->SetRoller1Velocity(m_roller1DesiredVelocity);
}

void Intake::SetRoller2Velocity(units::radians_per_second_t roller2DesiredVelocity) {
    m_roller2DesiredVelocity = roller2DesiredVelocity;
    m_io->SetRoller2Velocity(m_roller2DesiredVelocity);
}

void Intake::LogTelemetry() {
    Log("Roller 1 Desired Velocity", m_roller1DesiredVelocity.value());
    Log("Roller 2 Desired Velocity", m_roller2DesiredVelocity.value());
    Log("Roller 1 Velocity", m_inputs.roller1AngularVelocity.value());
    Log("Roller 2 Velocity", m_inputs.roller2AngularVelocity.value());
}