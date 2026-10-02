
#include "subsystem/intake/SimIntake.h"
#include "frc/system/plant/LinearSystemId.h"
#include "frc/Timer.h"
#include "Constants.h"
#include <units/voltage.h>

// using namespace Constants::Subsystem;

// SimIntakeIO::SimIntakeIO() :
//     m_intakeSim(frc::LinearSystemId::DCMotorSystem(
//         kMotor,
//         kInertia,
//         kGearRatio
//     ), kMotor, {0.001, 0.001}),
//     m_controller(kP, kI, kD)
// {    
// }