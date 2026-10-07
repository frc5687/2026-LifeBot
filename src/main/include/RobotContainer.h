// RobotContainer.h
#pragma once

#include <frc2/command/button/CommandPS5Controller.h>
#include <frc2/command/CommandPtr.h>

#include <units/angle.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

#include <array>
#include <memory>

#include "subsystem/drive/DriveSubsystem.h"
#include "subsystem/intake/roller1/Roller1.h"
#include "subsystem/intake/roller2/Roller2.h"

class RobotContainer {
 public:
  RobotContainer();

  frc2::Command *GetAutonomousCommand();

 private:
  void ConfigureBindings();


  // std::unique_ptr<DriveSubsystem> CreateDrive();
  // std::unique_ptr<Roller1> CreateRoller1();
  // std::unique_ptr<Roller2> CreateRoller2();
  // std::unique_ptr<VisionSubsystem> CreateVision();
  std::unique_ptr<Roller1> m_roller1;
  std::unique_ptr<Roller2> m_roller2;

  // std::unique_ptr<DriveSubsystem> m_drive;
  // std::unique_ptr<VisionSubsystem> m_vision;
  frc2::CommandPS5Controller m_driver{0};
  frc::SendableChooser<frc2::Command *> m_autoChooser;
};
