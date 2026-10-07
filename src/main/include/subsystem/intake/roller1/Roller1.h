
#pragma once

#include <memory>
#include "subsystem/LoggedSubsystem.h"
#include "Roller1IO.h"
#include "units/angular_velocity.h"
#include "units/voltage.h"

class Roller1 : public LoggedSubsystem {
public:
    explicit Roller1(std::unique_ptr<Roller1IO> io);
    ~Roller1() = default;

    void SetVelocity(turns_per_second_t roller1Velocity);
    void SetVoltage(volt_t Voltage);
    void Stop();

protected:
    void UpdateInputs() override;
    void LogTelemetry() override;

private:
    std::unique_ptr<Roller1IO> m_io;
    Roller1IOInputs m_inputs{};

    units::turns_per_second_t m_roller1DesiredVelocity{0_tps};
};
