
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
#include "subsystem/elevator/SimElevatorIO.h"
#include "subsystem/elevator/CTREElevatorIO.h"

RobotContainer::RobotContainer() {
  // Module encoder offsets (tune these per robot)
  constexpr std::array<units::turn_t, 4> kEncoderOffsets{
      0.079569_tr,                // FL
      0.43359375_tr - 0.5_tr,     // FR
      0.35595703125_tr - 0.5_tr,  // BL
      -0.2431540625_tr + 0.5_tr   // BR
  };

  // bool simulation = true;
  if (frc::RobotBase::IsSimulation()) {
    m_elevator = std::make_unique<ElevatorSubsystem>(
        std::make_unique<SimElevatorIO>());
  } else {
   auto elevatorIO = std::make_unique<CTREElevatorIO>(
        HardwareMap::kElevatorLeftMotor, HardwareMap::kElevatorRightMotor,
        HardwareMap::kElevatorLeftEncoder, HardwareMap::kElevatorRightEncoder);
    m_elevator = std::make_unique<ElevatorSubsystem>(std::move(elevatorIO));

  ConfigureBindings();
}

double RobotContainer::ApplyDeadband(double value, double deadband) {
  if (std::abs(value) < deadband) {
    return 0.0;
  }
  return (value - std::copysign(deadband, value)) / (1.0 - deadband);
}

void RobotContainer::ConfigureBindings() {
  using frc2::cmd::Run;
  using frc2::cmd::RunOnce;

//   m_drive->SetDefaultCommand(Run(
//       [this] {
//         const double xInput =
//             ApplyDeadband(-m_driver.GetLeftY(), Constants::kJoystickDeadband);
//         const double yInput =
//             ApplyDeadband(-m_driver.GetLeftX(), Constants::kJoystickDeadband);
//         const double rotInput =
//             ApplyDeadband(-m_driver.GetRightX(), Constants::kJoystickDeadband);

//         const auto xVelocity = xInput * Constants::SwerveDrive::kMaxLinearSpeed;
//         const auto yVelocity = yInput * Constants::SwerveDrive::kMaxLinearSpeed;
//         const auto rotVelocity =
//             rotInput * Constants::SwerveDrive::kMaxAngularSpeed;

//         m_drive->DriveFieldRelative(
//             frc::ChassisSpeeds{xVelocity, yVelocity, rotVelocity});
//       },
//       {m_drive.get()}));

  m_driver.Square().OnTrue(Run([this] { m_elevator->SetElevatorHeight(0.3_m); },
                               {m_elevator.get()}));

  m_driver.Triangle().OnTrue(Run(
      [this] { m_elevator->SetElevatorHeight(0.0_m); }, {m_elevator.get()}));


  // m_driver.Circle().OnTrue(
  //   Run([this] { m_elevator->SetElevatorHeight(0.6_m); },
  //   {m_elevator.get()}));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::Print("No autonomous command configured");
}