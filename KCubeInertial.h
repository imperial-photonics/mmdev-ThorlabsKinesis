// Copied & modified from other files in mmdev-ThorlabsKinesis-main
// to include KIM into supported devices 
// 2021.11.17 BY H.Liu 

#pragma once

#include "KinesisDevice.h"

class KCubeInertialAccess final: public KinesisDeviceAccess{
    public:
        explicit KCubeInertialAccess(std::string const& serialNo) :
            KinesisDeviceAccess{ serialNo }
        {}

    protected:
        bool IsKinesisDriverAvailable() override;
        short Kinesis_Open() override;
        short Kinesis_Close() override;
        short Kinesis_GetNumChannels() override;
};


class KCubeInertial final: public MotorDrive {// maybe non-stepper? though KIM cannot use encoder now
    public:
        KCubeInertial(std::shared_ptr<KinesisDeviceConnection> connection, short channel) :
            MotorDrive{ connection, channel }
        {}

    protected: // general
        short Kinesis_RequestSettings() override;
        short Kinesis_RequestStatusBits() override;
        bool Kinesis_StartPolling(int intervalMs) override;
        void Kinesis_StopPolling() override;

        short Kinesis_GetHardwareInfo(char* modelNo, DWORD sizeOfModelNo,
            WORD* type, WORD* numChannels, char* notes, DWORD sizeOfNotes,
            DWORD* firmwareVersion, WORD* hardwareVersion, WORD* modificationState)
            override;

        DWORD Kinesis_GetStatusBits() override;

    protected: // Motor
        short Kinesis_EnableChannel() override;
        short Kinesis_DisableChannel() override;

        int Kinesis_GetMotorTravelMode() override;
        short Kinesis_SetMotorTravelMode(int mode) override;
        short Kinesis_ResetRotationModes() override;
        short Kinesis_SetRotationModes(int mode, int direction) override;

        short Kinesis_SetHomingParams(int direction, int limitSwitchMode, int offsetDistance, int velocity) override;
        short Kinesis_SetLimitSwitchParams(int ccwHardwareLimitMode, int ccwSoftwareLimitPosition,
            int cwHardwareLimitMode, int cwSoftwareLimitPosition, int softwareLimitMode) override;

        short Kinesis_RequestPosition() override;
        int Kinesis_GetPosition() override;
        long Kinesis_GetPositionCounter() override;
        short Kinesis_MoveToPosition(int index) override;

        bool Kinesis_CanHome() override;
        short Kinesis_Home() override;

        short Kinesis_GetRealValueFromDeviceUnit(int deviceUnits,
            double* realValue, int unitType) override;
        short Kinesis_GetDeviceUnitFromRealValue(double realValue,
            int* deviceUnits, int unitType) override;
};
