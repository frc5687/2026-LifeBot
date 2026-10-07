
#pragma once

#include <units/length.h>
#include <units/mass.h>
#include <units/velocity.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/moment_of_inertia.h>
#include <frc/system/plant/DCMotor.h>

namespace Constants::Intake {

    namespace roller1{
    inline constexpr double kP = 0.001;
    inline constexpr double kI = 0.001;
    inline constexpr double kD = 0.001;

    inline constexpr bool kInverted = false;

    inline constexpr frc::DCMotor kMotor = frc::DCMotor::KrakenX44();
    inline constexpr units::kilogram_square_meter_t kInertia = 10_kg_sq_m;
    inline constexpr double kGearRatio = 12.0 / 13.0;
    }

    namespace roller2{
    inline constexpr double kP = 0.001;
    inline constexpr double kI = 0.001;
    inline constexpr double kD = 0.001;

    inline constexpr bool kInverted = false;

    inline constexpr frc::DCMotor kMotor = frc::DCMotor::KrakenX44();
    inline constexpr units::kilogram_square_meter_t kInertia = 10_kg_sq_m;
    inline constexpr double kGearRatio = 12.0 / 30.0;
    }






}
