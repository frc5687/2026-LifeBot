#include "ctre/phoenix6/StatusSignal.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "subsystem/intake/roller1/CTRERolle1IO.h"
#include "units/time.h"
#include "utils/CANDevice.h"

#include <frc/Timer.h>

#include "subsystem/intake/IntakeConstants.h"

using namespace Constants::Intake::roller1;


CTRERoller1IO::CTRERoller1IO(const CANDevice &motor)
    :m_motor(motor.id, motor.bus),
    m_velocitySignal(m_motor.GetVelocity()),
    m_voltageSignal(m_motor.GetMotorVoltage()),
    m_supplySignal(m_motor.GetSupplyCurrent()),
    m_criticalSignals{&m_velocitySignal, &m_voltageSignal},
    m_batchedSignals{&m_supplySignal} {ConfigureDevices();
                                      ConfigureSignalFrequencies();
    }


void CTRERoller1IO::ConfigureDevices() {
    m_config.MotorOutput.NeutralMode = signals::NeutralModeValue::Coast;
    m_config.MotorOutput.Inverted =
        kInverted ? signals::InvertedValue::Clockwise_Positive
                           : signals::InvertedValue::CounterClockwise_Positive;


  ConfigureClosedLoop();
  m_motor.GetConfigurator().Apply(m_config);
}



void CTRERoller1IO::ConfigureClosedLoop() {
    m_config.Slot0.kP = kP;
    m_config.Slot0.kI = kI;
    m_config.Slot0.kD = kD;
}


void CTRERoller1IO::ConfigureSignalFrequencies() {
    m_velocitySignal.SetUpdateFrequency(100_Hz);
    m_voltageSignal.SetUpdateFrequency(100_Hz);
    m_supplySignal.SetUpdateFrequency(50_Hz);

    m_motor.OptimizeBusUtilization();
}


void CTRERoller1IO::UpdateInputs(Roller1IOInputs &inputs){
    BaseStatusSignal::RefreshAll(m_criticalSignals);
    BaseStatusSignal::RefreshAll(m_batchedSignals);

    inputs.motor1Velocity = m_velocitySignal.GetValue();
    inputs.appliedVolts = m_voltageSignal.GetValue();
    inputs.supplyCurrent = m_supplySignal.GetValue();
    inputs.timestamp = units::second_t{frc::Timer::GetFPGATimestamp().value()};
}

void CTRERoller1IO::SetVoltage(units::volt_t voltage) {
    m_motor.SetControl(m_voltageRequest.WithOutput(voltage));
}

void CTRERoller1IO::SetVelocity(units::turns_per_second_t tps) {
    m_motor.SetControl(
        m_velocityRequest.WithVelocity(tps).WithSlot(0).WithEnableFOC(true));
}


void CTRERoller1IO::Stop() {m_motor.SetControl(m_nutralRequest); }
