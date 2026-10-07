
#pragma once

#include "units/current.h"
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/mass.h>
#include <units/time.h>
#include <units/voltage.h>

using namespace units;

struct Roller1IOInputs {
    turn_t motor1Position{0_tr};
    turns_per_second_t motor1Velocity{0_tps};

    volt_t appliedVolts{0_V};

    current::ampere_t supplyCurrent{0_A};



    radian_t roller1Angle{0_rad};
    radians_per_second_t roller1AngularVelocity{0_tps};


    second_t timestamp{0_s};


};

class Roller1IO {
public:
    virtual ~Roller1IO() = default;

    virtual void UpdateInputs(Roller1IOInputs& inputs) = 0;
    virtual void SetVoltage(volt_t Voltage) = 0;
    virtual void SetVelocity(turns_per_second_t croller1Velocity) = 0;
    virtual void Stop() = 0;

};
