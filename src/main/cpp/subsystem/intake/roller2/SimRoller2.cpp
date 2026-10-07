
#include "subsystem/intake/roller2/SimRoller2.h"
#include "units/angle.h"
#include "subsystem/intake/roller2/Roller2IO.h"
#include "units/angular_velocity.h"
#include "frc/system/plant/LinearSystemId.h"
#include "frc/Timer.h"
#include "subsystem/intake/IntakeConstants.h"
#include <units/voltage.h>

using namespace Constants::Intake::roller2;

SimRoller2IO::SimRoller2IO() :
    m_roller2Sim(frc::LinearSystemId::DCMotorSystem(
        kMotor,
        kInertia,
        kGearRatio
    ), kMotor, {0.001, 0.001}),
    m_controller(kP, kI, kD)
{
}

void    SimRoller2IO::UpdateInputs(Roller2IOInputs& inputs) {
    constexpr auto kDt = 20_ms;
    m_roller2Sim.Update(kDt);



    auto roller2Velocity = m_roller2Sim.GetAngularVelocity();
    inputs.motor2Velocity = (roller2Velocity *  kGearRatio) / (2.0 * std::numbers::pi * 1_rad) * 1_tr;
    // inputs.motor1Position = ()

    inputs.roller2AngularVelocity = roller2Velocity;
    inputs.timestamp = frc::Timer::GetFPGATimestamp();

    auto output = m_controller.Calculate(m_roller2Sim.GetAngularVelocity().value());
    m_roller2Sim.SetInputVoltage(units::volt_t{output});


}

void SimRoller2IO::SetVelocity(units::turns_per_second_t spins1){
    m_controller.SetSetpoint(spins1.value());
}

void SimRoller2IO::SetVoltage(units::volt_t Voltage){
    m_voltageCommand = Voltage;
}

void SimRoller2IO::Stop() {
    m_voltageCommand = 0_V;
}