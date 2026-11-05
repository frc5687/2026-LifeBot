#pragma once

#include <numbers>

#include <units/length.h>

namespace ElevatorConstants {

// -------------------- CAN IDs --------------------
// Set these to unique, unused IDs on the roboRIO CAN bus.
inline constexpr int kLeftMotorId = 20;
inline constexpr int kRightMotorId = 21;
inline constexpr int kLeftCANcoderId = 22;
inline constexpr int kRightCANcoderId = 23;

// -------------------- Mechanical measurements --------------------
// IMPORTANT: Fill these in before enabling the elevator.
//
// Motor rotations per ONE drum rotation. Example: a 10:1 reduction means 10.0.
// If a CANcoder is mounted on the drum/output shaft instead of the motor shaft,
// use 1.0. This value is the CANcoder rotations per mechanism rotation.
inline constexpr double kGearReduction = 0.0;  // TODO: enter actual ratio

// Diameter of the cable drum / pulley that directly winds the elevator cable.
inline constexpr units::meter_t kDrumDiameter = 0_m;  // TODO: measure it

// Linear carriage travel for one drum revolution, divided by drum circumference.
// This accounts for the elevator cable routing / stage rigging.
// Do NOT assume 2.0 just because this is a two-stage elevator; measure/derive it.
inline constexpr double kStageTravelPerDrumRotation =
    0.0;  // TODO: determine from the actual rigging

// Maximum permitted carriage height measured from the calibrated bottom.
inline constexpr units::meter_t kMaxHeight = 0_m;  // TODO: enter safe max height

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
inline constexpr double kP = 0.0;  // TODO: tune
inline constexpr double kI = 0.0;  // Usually start at 0
inline constexpr double kD = 0.0;  // TODO: tune

// Mechanism rotations per second and mechanism rotations per second squared.
inline constexpr double kMotionMagicCruiseVelocity = 0.0;  // TODO: tune
inline constexpr double kMotionMagicAcceleration = 0.0;   // TODO: tune

}  // namespace ElevatorConstants
