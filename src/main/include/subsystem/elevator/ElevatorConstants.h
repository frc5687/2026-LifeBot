#pragma once

#include "subsystem/elevator/ElevatorSubsystem.h"
#include "units/mass.h"
#include <numbers>

#include <units/length.h>
#include <frc/system/plant/DCMotor.h>

namespace ElevatorConstants {


inline constexpr double kGearRatio = 1.0;  // TODO: enter actual ratio

inline constexpr frc::DCMotor kMotors = frc::DCMotor::KrakenX60(2);

inline constexpr units::meter_t kDrumRadius = 1_m;  // TODO: measure it

inline constexpr units::kilogram_t kMass = 1_kg;

inline constexpr units::meter_t kMaxHeight = 1_m;
inline constexpr units::meter_t kMinHeight = .1_m;
inline constexpr units::meter_t kPositionTolorance = .01_m;

// -------------------- Motor / sensor directions --------------------
// Verify each direction with the elevator safely supported and motor output
// disabled. These are independent because the two sides may be mirror-mounted.
inline constexpr bool kLeftMotorInverted = false;   // TODO: verify
inline constexpr bool kRightMotorInverted = false;  // TODO: verify
inline constexpr bool kLeftEncoderCounterClockwisePositive = true;   // TODO
inline constexpr bool kRightEncoderCounterClockwisePositive = true;  // TODO

// -------------------- Motion Magic / PID --------------------
// Talon FX position units are mechanism rotations after applying the ratio above.
// Start with conservative values and tune under your team's controls lead.
inline constexpr double kP = 0.01;  // TODO: tune
inline constexpr double kI = 0.01;  // Usually start at 0
inline constexpr double kD = 0.01;  // TODO: tune

// Mechanism rotations per second and mechanism rotations per second squared.
inline constexpr units::meters_per_second_t kMaxVelocity = 1_mps;  // TODO: tune
inline constexpr units::meters_per_second_squared_t kMaxAcceleration = 1_mps_sq;   // TODO: tune
// inline constexpr double kMotionMagicCruiseVelocity = 1.0;
// inline constexpr double kMotionMagicAcceleration = 1.0;




}  // namespace ElevatorConstants
