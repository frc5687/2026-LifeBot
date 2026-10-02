
#pragma once

#include <units/angular_velocity.h>
#include <frc/simulation/DCMotorSim.h>
#include <frc/controller/PIDController.h>

#include "subsystem/intake/IntakeIO.h"

class SimIntakeIO : public IntakeIO {
public:
    SimIntakeIO();
    ~SimIntakeIO() = default;

    void UpdateInputs(IntakeIOInputs& inputs) override;
    void SetRoller1Velocity(units::radians_per_second_t roller1Velocity) override;
    void SetRoller2Velocity(units::radians_per_second_t roller2Velocity) override;

private:
    frc::sim::DCMotorSim m_intakeSim;
    frc::PIDController m_controller;
};