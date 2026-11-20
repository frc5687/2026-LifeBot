
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/DriverStation.h>
#include <frc/RobotBase.h>
#include <frc2/command/Commands.h>

#include <memory>
#include <utility>

#include "Constants.h"
#include "HardwareMap.h"
#include "subsystem/elevator/ElevatorSubsystem.h"
#include "subsystem/elevator/SimElevatorIO.h"
#include "subsystem/elevator/CTREElevatorIO.h"

RobotContainer::RobotContainer() {


    // if (frc::RobotBase::IsSimulation()) {
      auto elevatorIO = std::make_unique<SimElevatorIO>();
      m_elevator = std::make_unique<ElevatorSubsystem>(std::move(elevatorIO));
    // } else {
    //   auto elevatorIO = std::make_unique<CTREElevatorIO>(
    //       HardwareMap::CAN::TalonFX::LeftElevator,
    //       HardwareMap::CAN::TalonFX::RightElevator);
    //   m_elevator = std::make_unique<ElevatorSubsystem>(std::move(elevatorIO));
    // }
    ConfigureBindings();

}
void RobotContainer::ConfigureBindings() {
  using frc2::cmd::Run;
  using frc2::cmd::RunOnce;


  m_driver.Square().OnTrue(Run([this] { m_elevator->SetElevatorHeight(1.0_m); },{m_elevator.get()}));

  m_driver.Triangle().OnTrue(Run([this] { m_elevator->SetElevatorHeight(0.0_m); }, {m_elevator.get()}));


}
