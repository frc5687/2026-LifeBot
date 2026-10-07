
#pragma once

#include <string_view>

#include "utils/CANDevice.h"

namespace HardwareMap {
namespace Bus {
// inline constexpr std::string_view kDriveTrain = "DriveTrain";
inline constexpr std::string_view kRio = "rio";
inline constexpr std::string_view kStructure = "SuperStructure";
inline constexpr std::string_view kIntake = "Intake";
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
inline constexpr CANDevice Roller1Motor{0, Bus::kIntake};
inline constexpr CANDevice Roller2Motor{1, Bus::kIntake};

} // namespace TalonFX

namespace CANCoder {
// inline constexpr CANDevice FrontLeftEncoder{2, Bus::kDriveTrain};
// inline constexpr CANDevice FrontRightEncoder{1, Bus::kDriveTrain};
// inline constexpr CANDevice BackLeftEncoder{3, Bus::kDriveTrain};
// inline constexpr CANDevice BackRightEncoder{0, Bus::kDriveTrain};
} // namespace CANCoder

namespace Pidgeon2 {
// inline constexpr CANDevice IMU{0, Bus::kDriveTrain};
} // namespace Pidgeon2

} // namespace CAN

} // namespace HardwareMap
