
#pragma once

#include <units/angular_velocity.h>
#include <frc/simulation/DCMotorSim.h>
#include <frc/controller/PIDController.h>

#include "subsystem/intake/roller1/Roller1IO.h"
#include "units/voltage.h"

class SimRoller1IO : public Roller1IO {
public:
    SimRoller1IO();
    ~SimRoller1IO() override = default;

    void UpdateInputs(Roller1IOInputs& inputs) override;
    void SetVoltage(units::volt_t Voltage);
    void SetVelocity(units::turns_per_second_t roller1Velocity) override;
    void Stop() override;
private:
    frc::sim::DCMotorSim m_roller1Sim;
    frc::PIDController m_controller;
    units::volt_t m_voltageCommand{0_V};
};
