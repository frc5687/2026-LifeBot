
#pragma once

#include <units/angular_velocity.h>
#include <frc/simulation/DCMotorSim.h>
#include <frc/controller/PIDController.h>

#include "subsystem/intake/roller2/Roller2IO.h"
#include "units/voltage.h"

class SimRoller2IO : public Roller2IO {
public:
    SimRoller2IO();
    ~SimRoller2IO() override = default;

    void UpdateInputs(Roller2IOInputs& inputs) override;
    void SetVoltage(units::volt_t Voltage);
    void SetVelocity(units::turns_per_second_t roller2Velocity) override;
    void Stop() override;
private:
    frc::sim::DCMotorSim m_roller2Sim;
    frc::PIDController m_controller;
    units::volt_t m_voltageCommand{0_V};
};
