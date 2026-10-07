
#pragma once

#include <memory>
#include "subsystem/LoggedSubsystem.h"
#include "Roller2IO.h"
#include "units/angular_velocity.h"
#include "units/voltage.h"

class Roller2 : public LoggedSubsystem {
public:
    explicit Roller2(std::unique_ptr<Roller2IO> io);
    ~Roller2() = default;

    void SetVelocity(turns_per_second_t roller2Velocity);
    void SetVoltage(volt_t Voltage);
    void Stop();

protected:
    void UpdateInputs() override;
    void LogTelemetry() override;

private:
    std::unique_ptr<Roller2IO> m_io;
    Roller2IOInputs m_inputs{};

    units::turns_per_second_t m_roller2DesiredVelocity{0_tps};
};
