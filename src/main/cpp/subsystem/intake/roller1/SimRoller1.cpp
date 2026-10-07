
#include "subsystem/intake/roller1/SimRoller1.h""
#include "units/angle.h"
#include "subsystem/intake/roller1/Roller1IO.h"
#include "units/angular_velocity.h"
#include "frc/system/plant/LinearSystemId.h"
#include "frc/Timer.h"
#include "subsystem/intake/IntakeConstants.h"
#include <units/voltage.h>

using namespace Constants::Intake::roller1;

SimRoller1IO::SimRoller1IO() :
    m_roller1Sim(frc::LinearSystemId::DCMotorSystem(
        kMotor,
        kInertia,
        kGearRatio
    ), kMotor, {0.001, 0.001}),
    m_controller(kP, kI, kD)
{
}

void    SimRoller1IO::UpdateInputs(Roller1IOInputs& inputs) {
    constexpr auto kDt = 20_ms;
    m_roller1Sim.Update(kDt);



    auto roller1Velocity = m_roller1Sim.GetAngularVelocity();
    inputs.motor1Velocity = (roller1Velocity *  kGearRatio) / (2.0 * std::numbers::pi * 1_rad) * 1_tr;
    // inputs.motor1Position = ()

    inputs.roller1AngularVelocity = roller1Velocity;
    inputs.timestamp = frc::Timer::GetFPGATimestamp();

    auto output = m_controller.Calculate(m_roller1Sim.GetAngularVelocity().value());
    m_roller1Sim.SetInputVoltage(units::volt_t{output});


}

void SimRoller1IO::SetVelocity(units::turns_per_second_t spins1){
    m_controller.SetSetpoint(spins1.value());
}

void SimRoller1IO::SetVoltage(units::volt_t Voltage){
    m_voltageCommand = Voltage;
}

void SimRoller1IO::Stop() {
    m_voltageCommand = 0_V;
}
