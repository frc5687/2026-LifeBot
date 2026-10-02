
#pragma once

#include <memory>
#include "subsystem/LoggedSubsystem.h"
#include "IntakeIO.h"

class Intake : public LoggedSubsystem {
public:
    explicit Intake(std::unique_ptr<IntakeIO> io);
    ~Intake() = default;

    void SetRoller1Velocity(radians_per_second_t roller1Velocity);
    void SetRoller2Velocity(radians_per_second_t roller2Velocity);

protected:
    void UpdateInputs() override;
    void LogTelemetry() override;

private:
    std::unique_ptr<IntakeIO> m_io;
    IntakeIOInputs m_inputs{};

    units::radians_per_second_t m_roller1DesiredVelocity{0_rad_per_s};
    units::radians_per_second_t m_roller2DesiredVelocity{0_rad_per_s};
};