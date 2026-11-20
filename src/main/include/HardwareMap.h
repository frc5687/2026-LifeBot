
#pragma once

#include <string_view>

#include "utils/CANDevice.h"

namespace HardwareMap {
namespace Bus {
// inline constexpr std::string_view kDriveTrain = "DriveTrain";
// inline constexpr std::string_view kRio = "rio";
// inline constexpr std::string_view kStructure = "SuperStructure";
// inline constexpr std::string_view kIntake = "Intake";
inline constexpr std::string_view kElevator = "Elevator";
} // namespace Bus

namespace CAN {
namespace TalonFX {
// inline constexpr CANDevice FrontLeftDrive{5, Bus::kDriveTrain};
// inline constexpr CANDevice FrontLeftSteer{4, Bus::kDriveTrain};

// inline constexpr CANDevice FrontRightDrive{3, Bus::kDriveTrain};
// inline constexpr CANDevice FrontRightSteer{2, Bus::kDriveTrain};

// inline constexpr CANDevice BackLeftDrive{7, Bus::kDriveTrain};
// inline constexpr CANDevice BackLeftSteer{6, Bus::kDriveTrain};

// inline constexpr CANDevice BackRightDrive{1, Bus::kDriveTrain};
// inline constexpr CANDevice BackRightSteer{0, Bus::kDriveTrain};
inline constexpr CANDevice ElevatorMotorLeft{0, Bus::kElevator};
inline constexpr CANDevice ElevatorMotorRight{1, Bus::kElevator};

} // namespace TalonFX

namespace CANCoder {
// inline constexpr CANDevice FrontLeftEncoder{2, Bus::kDriveTrain};
// inline constexpr CANDevice FrontRightEncoder{1, Bus::kDriveTrain};
// inline constexpr CANDevice BackLeftEncoder{3, Bus::kDriveTrain};
// inline constexpr CANDevice BackRightEncoder{0, Bus::kDriveTrain};
inline constexpr CANDevice LeftEncodoer{2, Bus::kElevator};
inline constexpr CANDevice RightEncoder{3, Bus::kElevator};
} // namespace CANCoder

namespace Pidgeon2 {
// inline constexpr CANDevice IMU{0, Bus::kDriveTrain};
} // namespace Pidgeon2

} // namespace CAN

} // namespace HardwareMap
