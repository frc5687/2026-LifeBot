#include "subsystem/intake/roller2/Roller2.h"

Roller2::Roller2(std::unique_ptr<Roller2IO> io) :
    LoggedSubsystem("Intake"),
    m_io(std::move(io)) {
}

void Roller2::UpdateInputs() {
    m_io->UpdateInputs(m_inputs);
}

void Roller2::SetVoltage(units::volt_t voltage) {
    m_io -> SetVoltage(voltage);
}

void Roller2::Stop() {
    m_io -> Stop();
}

void Roller2::SetVelocity(units::turns_per_second_t roller2DesiredVelocity) {
    m_roller2DesiredVelocity = roller2DesiredVelocity;
    m_io->SetVelocity(m_roller2DesiredVelocity);
}



void Roller2::LogTelemetry() {
    Log("Roller 1 Desired Velocity", m_roller2DesiredVelocity.value());
    Log("Roller 1 Velocity", m_inputs.roller2AngularVelocity.value());
}
