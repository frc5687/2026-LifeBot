#include "subsystem/elevator/SimElevatorIO.h"

#include "frc/Timer.h"
#include "frc/trajectory/TrapezoidProfile.h"
#include "subsystem/elevator/ElevatorConstants.h"
#include "units/voltage.h"

SimElevatorIO::SimElevatorIO() :
    m_elevatorSim(ElevatorConstants::kMotors, ElevatorConstants::kGearRatio, ElevatorConstants::kMass, ElevatorConstants::kDrumRadius, ElevatorConstants:: kMaxHeight, ElevatorConstants::kMaxHeight, true, {0.001,0.001}),
    m_pidController(100, 0, 0, frc::TrapezoidProfile<units::meter>::Constraints(ElevatorConstants::kMaxVelocity, ElevatorConstants::kMaxAcceleration)) {}


    void SimElevatorIO::UpdateInputs(ElevatorIOInputs &inputs) {
        m_elevatorSim.Update(20_ms);
        inputs.elevatorHeight = m_elevatorSim.GetPosition();
        inputs.elevatorVelocity = m_elevatorSim.GetVelocity();
    }

    void SimElevatorIO::SetHeight(units::meter_t desiredHeight){
        auto postion = m_elevatorSim.GetPosition();
        auto pidOutput = m_pidController.Calculate(postion, disiredHeight);

        m_elevatorSim.SetInputVoltage(units::volt_t{pidOutput});
    }
