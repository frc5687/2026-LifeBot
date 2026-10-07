#include "subsystem/intake/roller1/Roller1.h"

Roller1::Roller1(std::unique_ptr<Roller1IO> io) :
    LoggedSubsystem("Intake"),
    m_io(std::move(io)) {
}

void Roller1::UpdateInputs() {
    m_io->UpdateInputs(m_inputs);
}

void Roller1::SetVoltage(units::volt_t voltage) {
    m_io -> SetVoltage(voltage);
}

void Roller1::Stop() {
    m_io -> Stop();
}

void Roller1::SetVelocity(units::turns_per_second_t roller1DesiredVelocity) {
    m_roller1DesiredVelocity = roller1DesiredVelocity;
    m_io->SetVelocity(m_roller1DesiredVelocity);
}



void Roller1::LogTelemetry() {
    Log("Roller 1 Desired Velocity", m_roller1DesiredVelocity.value());
    Log("Roller 1 Velocity", m_inputs.roller1AngularVelocity.value());
}
