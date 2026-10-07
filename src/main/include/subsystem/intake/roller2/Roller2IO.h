
#pragma once

#include "units/current.h"
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/mass.h>
#include <units/time.h>
#include <units/voltage.h>

using namespace units;

struct Roller2IOInputs {
    turn_t motor2Position{0_tr};
    turns_per_second_t motor2Velocity{0_tps};

    volt_t appliedVolts{0_V};

    current::ampere_t supplyCurrent{0_A};



    radian_t roller2Angle{0_rad};
    radians_per_second_t roller2AngularVelocity{0_tps};


    second_t timestamp{0_s};


};

class Roller2IO {
public:
    virtual ~Roller2IO() = default;

    virtual void UpdateInputs(Roller2IOInputs& inputs) = 0;
    virtual void SetVoltage(volt_t Voltage) = 0;
    virtual void SetVelocity(turns_per_second_t croller2Velocity) = 0;
    virtual void Stop() = 0;

};
