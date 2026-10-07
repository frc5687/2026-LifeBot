// RobotContainer.cpp
#include "RobotContainer.h"

#include <frc/RobotBase.h>
#include <frc2/command/Commands.h>
#include <units/angle.h>
#include <units/length.h>

#include <array>
#include <memory>
#include <utility>

#include "HardwareMap.h"
// #include "commands/drive/DriveMaintainingHeadingCommand.h"
#include "commands/intake/IntakeCommand.h"
#include "pathplanner/lib/auto/AutoBuilder.h"
// #include "subsystem/drive/PigeonIO.h"
#include "subsystem/drive/SimGyroIO.h"
#include "subsystem/drive/module/ModuleConfig.h"
#include "subsystem/drive/module/SimModuleIO.h"
// #include "commands/drive/DriveWithNormalVectorAlignment.h"
// #include "subsystem/drive/module/CTREModuleIO.h"
#include "subsystem/intake/roller1/CTRERolle1IO.h"
#include "subsystem/intake/roller1/Roller1.h"
#include "subsystem/intake/roller1/Roller1IO.h"
#include "subsystem/intake/roller1/SimRoller1.h"
#include "subsystem/intake/roller1/CTRERolle1IO.h"
#include "subsystem/intake/roller2/Roller2.h"
#include "subsystem/intake/roller2/Roller2IO.h"
#include "subsystem/intake/roller2/SimRoller2.h"
#include <subsystem/intake/roller2/CTRERolle2IO.h>
// #include "subsystem/vision/SimVisionIO.h"

RobotContainer::RobotContainer() {
  // m_drive = CreateDrive();
//   m_roller1 = CreateRoller1();
//   m_roller2 = CreateRoller2();
//   m_elevator = CreateElevator();
//   m_vision = CreateVision();
  ConfigureBindings();

  // m_autoChooser = pathplanner::AutoBuilder::buildAutoChooser();
  // frc::SmartDashboard::PutData("Auto Chooser", &m_autoChooser);
}

// std::unique_ptr<DriveSubsystem> RobotContainer::CreateDrive() {
//   // Module encoder offsets (tune these per robot)
//   constexpr std::array<units::turn_t, 4> kEncoderOffsets{
//       -0.403076171875_tr,         // FL
//       0.2744140625_tr,            // FR
//       0.44921875_tr,                 // BL
//       -0.15185546875_tr          // BR
//   };

//   if (frc::RobotBase::IsSimulation()) {
//     return std::make_unique<DriveSubsystem>(
//         std::make_unique<SimModuleIO>(
//             ModuleConfig{ModulePosition::FrontLeft, 0_tr}),
//         std::make_unique<SimModuleIO>(
//             ModuleConfig{ModulePosition::FrontRight, 0_tr}),
//         std::make_unique<SimModuleIO>(
//             ModuleConfig{ModulePosition::BackLeft, 0_tr}),
//         std::make_unique<SimModuleIO>(
//             ModuleConfig{ModulePosition::BackRight, 0_tr}),
//         std::make_unique<SimGyroIO>());
//   }

  // Real hardware
//   return std::make_unique<DriveSubsystem>(
//       std::make_unique<CTREModuleIO>(
//           CTREModuleIO::DeviceIDs{
//               HardwareMap::CAN::TalonFX::FrontLeftDrive,
//               HardwareMap::CAN::TalonFX::FrontLeftSteer,
//               HardwareMap::CAN::CANCoder::FrontLeftEncoder},
//           ModuleConfig{ModulePosition::FrontLeft, kEncoderOffsets[0]}),

//       std::make_unique<CTREModuleIO>(
//           CTREModuleIO::DeviceIDs{
//               HardwareMap::CAN::TalonFX::FrontRightDrive,
//               HardwareMap::CAN::TalonFX::FrontRightSteer,
//               HardwareMap::CAN::CANCoder::FrontRightEncoder},
//           ModuleConfig{ModulePosition::FrontRight, kEncoderOffsets[1]}),

//       std::make_unique<CTREModuleIO>(
//           CTREModuleIO::DeviceIDs{
//               HardwareMap::CAN::TalonFX::BackLeftDrive,
//               HardwareMap::CAN::TalonFX::BackLeftSteer,
//               HardwareMap::CAN::CANCoder::BackLeftEncoder},
//           ModuleConfig{ModulePosition::BackLeft, kEncoderOffsets[2]}),

//       std::make_unique<CTREModuleIO>(
//           CTREModuleIO::DeviceIDs{
//               HardwareMap::CAN::TalonFX::BackRightDrive,
//               HardwareMap::CAN::TalonFX::BackRightSteer,
//               HardwareMap::CAN::CANCoder::BackRightEncoder},
//           ModuleConfig{ModulePosition::BackRight, kEncoderOffsets[3]}),

//       std::make_unique<PigeonIO>(HardwareMap::CAN::Pidgeon2::IMU));
// }

// std::unique_ptr<ElevatorSubsystem> RobotContainer::CreateElevator() {
//   if (frc::RobotBase::IsSimulation()) {
//     return std::make_unique<ElevatorSubsystem>(
//         std::make_unique<SimElevatorIO>());
//   }

//   return std::make_unique<ElevatorSubsystem>(
//       std::make_unique<CTREElevatorIO>(
//           HardwareMap::CAN::TalonFX::LeftElevator,
//           HardwareMap::CAN::TalonFX::RightElevator));
// }

// std::unique_ptr<VisionSubsystem> RobotContainer::CreateVision() {
//   return std::make_unique<VisionSubsystem>(
//       std::make_unique<SimVisionIO>(),
//       m_drive->GetOdometryThread());
// }


std::unique_ptr<Roller1IO> MakeRoller1IO () {
    if (frc::RobotBase::IsSimulation()){
        return std::make_unique<SimRoller1IO>();
    }
    return std::make_unique<CTRERoller1IO>(HardwareMap::CAN::TalonFX::Roller1Motor);
}


std::unique_ptr<Roller2IO> MakeRoller2IO () {
    if (frc::RobotBase::IsSimulation()){
        return std::make_unique<SimRoller2IO>();
    }
    return std::make_unique<CTRERoller2IO>(HardwareMap::CAN::TalonFX::Roller2Motor);
}

void RobotContainer::ConfigureBindings() {
  using frc2::cmd::Run;

  // Set default drive command
//   m_drive->SetDefaultCommand(DriveMaintainingHeadingCommand(
//       m_drive.get(),
//       [this] { return -m_driver.GetLeftY(); },
//       [this] { return -m_driver.GetLeftX(); },
//       [this] { return -m_driver.GetRightX(); },
//       false)); //s lew limiter

//   m_driver.Square().WhileTrue(
//       DriveWithNormalVectorAlignment(
//           m_drive.get(),
//           []() { return frc::Pose2d{5_m, 3_m, frc::Rotation2d{45_deg}}; },
//           false)
//       .ToPtr());


//   m_driver.L1().WhileTrue(Run([this] {}))
//         }


}

frc2::Command *RobotContainer::GetAutonomousCommand() {
  return m_autoChooser.GetSelected();
}

// frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
//   return frc2::cmd::Print("No autonomous command configured");
// }
