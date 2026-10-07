#pragma once

#include <array>


#include <ctre/phoenix6/StatusSignal.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/controls/NeutralOut.hpp>
#include <ctre/phoenix6/controls/VelocityVoltage.hpp>
#include <ctre/phoenix6/controls/TorqueCurrentFOC.hpp>
#include <ctre/phoenix6/controls/VoltageOut.hpp>
#include <ctre/phoenix6/core/CoreTalonFX.hpp>


#include "subsystem/intake/roller1/Roller1IO.h"

#include "utils/CANDevice.h"

using namespace ctre::phoenix6;



class CTRERoller1IO : public Roller1IO {
    public:
        explicit CTRERoller1IO(const CANDevice &motor);

    void UpdateInputs(Roller1IOInputs &inputs) override;
    void SetVoltage(units::volt_t voltage) override;
    void SetVelocity(units::turns_per_second_t tps) override;
    void Stop() override;


    private:
        hardware::TalonFX m_motor;

        StatusSignal<units::turns_per_second_t> &m_velocitySignal;
        StatusSignal<units::volt_t> &m_voltageSignal;
        StatusSignal<units::ampere_t> &m_supplySignal;

        std::array<ctre::phoenix6::BaseStatusSignal *, 2> m_criticalSignals;
        std::array<ctre::phoenix6::BaseStatusSignal *, 1> m_batchedSignals;


        controls::VelocityVoltage m_velocityRequest{0_tps};
        controls::VoltageOut m_voltageRequest{0_V};
        controls::VoltageOut m_voltafeRequest{0_V};
        controls::NeutralOut m_nutralRequest{};

        configs::TalonFXConfiguration m_config{};



        void ConfigureDevices();
        void ConfigureClosedLoop();
        void ConfigureSignalFrequencies();
    };
