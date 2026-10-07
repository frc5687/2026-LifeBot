#include "commands/intake/IntakeCommand.h"

#include "subsystem/intake/roller1/Roller1.h"
#include "subsystem/intake/roller2/Roller2.h"

IntakeCommand::IntakeCommand(Roller1 *roll1, Roller2 *roll2) : m_roller1(roll1), m_roller2(roll2) {
    AddRequirements({roll1, roll2});
    SetName("intakeCommand");
}

void IntakeCommand::Initialize() {
}

void IntakeCommand::Execute() {
    m_roller1 -> SetVoltage(kRoller1Voltage);
    m_roller2 -> SetVoltage(kRoller2Voltage);
}


void IntakeCommand::End(bool inturrupted) {
    m_roller1 -> Stop();
    m_roller2 -> Stop();
}

bool::IntakeCommand::IsFinished() {return false;}
