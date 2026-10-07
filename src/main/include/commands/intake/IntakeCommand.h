#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/Command.h>
#include <units/voltage.h>


#include "frc2/command/CommandHelper.h"
#include "subsystem/intake/roller1/Roller1.h"
#include "subsystem/intake/roller2/Roller2.h"
#include "units/current.h"

class IntakeCommand : public frc2::CommandHelper<frc2::Command, IntakeCommand> {
    public:
       IntakeCommand(Roller1 *roller1, Roller2 *roller2);

    void Initialize() override;
    void Execute() override;
    void End(bool inturrupted) override;
    bool IsFinished() override;


    private:
        Roller1 *m_roller1;
        Roller2 *m_roller2;


        static constexpr units::volt_t kRoller1Voltage = 1_V;
        static constexpr units::volt_t kRoller2Voltage = 1_V;

        static constexpr units::ampere_t kRoller1Current = 1_A;
        static constexpr units::ampere_t kRoller2Current = 1_A;

};
