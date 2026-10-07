#include "ctre/phoenix6/StatusSignal.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "subsystem/intake/roller2/CTRERolle2IO.h"
#include "units/time.h"
#include "utils/CANDevice.h"

#include <frc/Timer.h>

#include "subsystem/intake/IntakeConstants.h"

using namespace Constants::Intake::roller2;
using namespace ctre::phoenix6;

CTRERoller2IO::CTRERoller2IO(const CANDevice &motor)
    :m_motor(motor.id, motor.bus),
    m_velocitySignal(m_motor.GetVelocity()),
    m_voltageSignal(m_motor.GetMotorVoltage()),
    m_supplySignal(m_motor.GetSupplyCurrent()),
    m_criticalSignals{&m_velocitySignal, &m_voltageSignal},
    m_batchedSignals{&m_supplySignal} {ConfigureDevices();
                                      ConfigureSignalFrequencies();
    }


void CTRERoller2IO::ConfigureDevices() {
    m_config.MotorOutput.NeutralMode = signals::NeutralModeValue::Coast;
    m_config.MotorOutput.Inverted =
        kInverted ? signals::InvertedValue::Clockwise_Positive
                           : signals::InvertedValue::CounterClockwise_Positive;


  ConfigureClosedLoop();
  m_motor.GetConfigurator().Apply(m_config);
}



void CTRERoller2IO::ConfigureClosedLoop() {
    m_config.Slot0.kP = kP;
    m_config.Slot0.kI = kI;
    m_config.Slot0.kD = kD;
}


void CTRERoller2IO::ConfigureSignalFrequencies() {
    m_velocitySignal.SetUpdateFrequency(100_Hz);
    m_voltageSignal.SetUpdateFrequency(100_Hz);
    m_supplySignal.SetUpdateFrequency(50_Hz);

    m_motor.OptimizeBusUtilization();
}


void CTRERoller2IO::UpdateInputs(Roller2IOInputs &inputs){
    BaseStatusSignal::RefreshAll(m_criticalSignals);
    BaseStatusSignal::RefreshAll(m_batchedSignals);

    inputs.motor2Velocity = m_velocitySignal.GetValue();
    inputs.appliedVolts = m_voltageSignal.GetValue();
    inputs.supplyCurrent = m_supplySignal.GetValue();
    inputs.timestamp = units::second_t{frc::Timer::GetFPGATimestamp().value()};
}

void CTRERoller2IO::SetVoltage(units::volt_t voltage) {
    m_motor.SetControl(m_voltageRequest.WithOutput(voltage));
}

void CTRERoller2IO::SetVelocity(units::turns_per_second_t tps) {
    m_motor.SetControl(
        m_velocityRequest.WithVelocity(tps).WithSlot(0).WithEnableFOC(true));
}


void CTRERoller2IO::Stop() {m_motor.SetControl(m_nutralRequest); }
