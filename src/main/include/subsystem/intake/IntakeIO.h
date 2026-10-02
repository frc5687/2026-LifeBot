
#pragma once

#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/mass.h>
#include <units/time.h>

using namespace units;

struct IntakeIOInputs {
    turn_t motor1Position{0_tr};
    turns_per_second_t motor1Velocity{0_tps};

    turn_t motor2Position{0_tr};
    turns_per_second_t motor2Velocity{0_tps};

    radian_t roller1Angle{0_rad};
    radians_per_second_t roller1AngularVelocity{0_rad_per_s};

    radian_t roller2Angle{0_rad};
    radians_per_second_t roller2AngularVelocity{0_rad_per_s};

    second_t timestamp{0_s};
};

class IntakeIO {
public:
    virtual ~IntakeIO() = default;

    virtual void UpdateInputs(IntakeIOInputs& inputs) = 0;
    virtual void SetRoller1Velocity(radians_per_second_t roller1Velocity) = 0;
    virtual void SetRoller2Velocity(radians_per_second_t roller2Velocity) = 0;
};