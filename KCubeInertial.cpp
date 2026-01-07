// Copied & modified from other files in mmdev-ThorlabsKinesis-main
// to include KIM into supported devices 
// Last Modified 2021.11.22 BY H.Liu 

#include "KCubeInertial.h"

#include "DLLAccess.h"

#include "Thorlabs.MotionControl.KCube.InertialMotor.h"

static DLLAccess kinesisDll{ "Thorlabs.MotionControl.KCube.InertialMotor.dll" };

bool
KCubeInertialAccess::IsKinesisDriverAvailable() {
    return kinesisDll.IsValid(); // prove that this dll exists and can be loaded?
}

short
KCubeInertialAccess::Kinesis_Open() {
    STATIC_DLL_FUNC(kinesisDll, KIM_Open, func);
    return func(CSerialNo());
}

short
KCubeInertialAccess::Kinesis_Close() {
    STATIC_DLL_FUNC(kinesisDll, KIM_Close, func);
    func(CSerialNo());
    return 0;
}

short
KCubeInertialAccess::Kinesis_GetNumChannels() {
    //STATIC_DLL_FUNC(kinesisDll, TLI_GetDeviceInfo, func); // no KIM_GetNumChannels function
    //TLI_DeviceInfo *info; // not using gethardwareinfo?-- may need this before connecting to hardware
    //short ret = func(CSerialNo(),info);
    //if(ret==1){
    //    // return 1; successful
    //    return info->maxChannels;
    //} else {
        // return 0: failed
    //    return ret;
    //} 
    // S/N starting with 97 is specific to KIM101, 74 is for KIM001 
    if (CSerialNo()[0] == '9' && CSerialNo()[1] == '7') { return 4; }
    else if (CSerialNo()[0] == '7' && CSerialNo()[1] == '4') { return 1; }
    return -1; 
    // seems get device info not worked
    // just judge by serial no
} 

//////////////////////////////////////////////////////////////////////////////////////////

short
KCubeInertial::Kinesis_RequestSettings() {
    STATIC_DLL_FUNC(kinesisDll, KIM_RequestSettings, func);
    return func(CSerialNo());
}

short
KCubeInertial::Kinesis_RequestStatusBits() {
    STATIC_DLL_FUNC(kinesisDll, KIM_RequestStatusBits, func);
    return func(CSerialNo());
}

bool
KCubeInertial::Kinesis_StartPolling(int intervalMs) {
    STATIC_DLL_FUNC(kinesisDll, KIM_StartPolling, func);
    return func(CSerialNo(), intervalMs);
}

void
KCubeInertial::Kinesis_StopPolling() {
    STATIC_DLL_FUNC(kinesisDll, KIM_StopPolling, func);
    func(CSerialNo());
}

short
KCubeInertial::Kinesis_GetHardwareInfo(char* modelNo, DWORD sizeOfModelNo,
    WORD* type, WORD* numChannels, char* notes, DWORD sizeOfNotes,
    DWORD* firmwareVersion, WORD* hardwareVersion, WORD* modificationState) {

    STATIC_DLL_FUNC(kinesisDll, KIM_GetHardwareInfo, func);
    return func(CSerialNo(), modelNo, sizeOfModelNo,
        type, numChannels, notes, sizeOfNotes, firmwareVersion,
        hardwareVersion, modificationState);
}

DWORD
KCubeInertial::Kinesis_GetStatusBits() {
    STATIC_DLL_FUNC(kinesisDll, KIM_GetStatusBits, func);
    return func(CSerialNo(),static_cast<KIM_Channels>(Channel())); // need add static_cast<KIM_Channels> or not? it maybe different from general motor channels
}

short
KCubeInertial::Kinesis_EnableChannel() {
    STATIC_DLL_FUNC(kinesisDll, KIM_EnableChannel, func);
    return func(CSerialNo(),static_cast<KIM_Channels>(Channel()));// same as above
}

short
KCubeInertial::Kinesis_DisableChannel() {
    STATIC_DLL_FUNC(kinesisDll, KIM_DisableChannel, func);
    return func(CSerialNo(),static_cast<KIM_Channels>(Channel()));// same as above
}

int
KCubeInertial::Kinesis_GetMotorTravelMode() {
    //STATIC_DLL_FUNC(kinesisDll, KIM_GetMotorTravelMode, func);
    //return func(CSerialNo()); // No such func! // maybe just set to linear?
    // not really used; maybe just return linear and do nothing?
    return 1; // 1 -- linear; 2 -- rotational
}



short
KCubeInertial::Kinesis_SetMotorTravelMode(int mode) {
    //STATIC_DLL_FUNC(kinesisDll, KIM_SetMotorTravelMode, func);
    //return func(CSerialNo(), static_cast<MOT_TravelModes>(mode)); 
    // not really used; maybe just return ok and do nothing?
    return 0; // 0 -- ok
}


short
KCubeInertial::Kinesis_ResetRotationModes() {
    // STATIC_DLL_FUNC(kinesisDll, KIM_ResetRotationModes, func);
    // return func(CSerialNo()); // maybe KIM_Reset?
    // not really used; just do nothing and return a good value
    return 0; // 0 -- ok
}


short
KCubeInertial::Kinesis_SetRotationModes(int mode, int direction) {
    // STATIC_DLL_FUNC(kinesisDll, KIM_SetRotationModes, func);
    //return func(CSerialNo(), static_cast<MOT_MovementModes>(mode),
    //    static_cast<MOT_MovementDirections>(direction));
    // not really used; just do nothing and return a good value
    return 0; // 0 -- ok
}

short
KCubeInertial::Kinesis_SetHomingParams(int direction, int limitSwitchMode, int offsetDistance, int velocity) {
    // not really used; just do nothing and return a good value
    return 0; // 0 -- ok
}

short
KCubeInertial::Kinesis_SetLimitSwitchParams(int ccwHardwareLimitMode, int ccwSoftwareLimitPosition,
    int cwHardwareLimitMode, int cwSoftwareLimitPosition, int softwareLimitMode) {
    // not really used; just do nothing and return a good value
    return 0; // 0 -- ok
}


short
KCubeInertial::Kinesis_RequestPosition() {
    STATIC_DLL_FUNC(kinesisDll, KIM_RequestCurrentPosition, func);
    return func(CSerialNo(), static_cast<KIM_Channels>(Channel()));//no such function as KIM_RequestPosition
}

int
KCubeInertial::Kinesis_GetPosition() {
    //STATIC_DLL_FUNC(kinesisDll, KIM_GetPosition, func);
    //return func(CSerialNo()); // this func is not used actually; and no such function as KIM_GetPosition
    return Kinesis_GetPositionCounter();
}

long
KCubeInertial::Kinesis_GetPositionCounter() {
    STATIC_DLL_FUNC(kinesisDll, KIM_GetCurrentPosition, func);
    return func(CSerialNo(), static_cast<KIM_Channels>(Channel()));//no such function as KIM_GetPositionCounter
}

short
KCubeInertial::Kinesis_MoveToPosition(int index) {
    STATIC_DLL_FUNC(kinesisDll, KIM_MoveAbsolute, func);
    return func(CSerialNo(), static_cast<KIM_Channels>(Channel()), index); // no such function as KIM_MoveToPosition
}

bool
KCubeInertial::Kinesis_CanHome() {
    // STATIC_DLL_FUNC(kinesisDll, KIM_CanHome, func);
    // return func(CSerialNo()); // no such function as KIM_CanHome, maybe just set yes
    return true;
}

short
KCubeInertial::Kinesis_Home() {
    // too dangerous to move to limit switch now as we are not sure if it has one now
    // and this seems require additional efforts to set
    // use move to 0 instead
    //STATIC_DLL_FUNC(kinesisDll, KIM_Home, func);
    //return func(CSerialNo(),static_cast<KIM_Channels>(Channel())); // same as above
    return Kinesis_MoveToPosition(0);
}


short
KCubeInertial::Kinesis_GetRealValueFromDeviceUnit(int deviceUnits,
    double* realValue, int unitType) {

    //STATIC_DLL_FUNC(kinesisDll, KIM_GetRealValueFromDeviceUnit, func);
    //return func(CSerialNo(), deviceUnits, realValue, unitType); // no such function
    // not really used; just do nothing and return a good value
    return 0; // 0 -- ok
} 

short
KCubeInertial::Kinesis_GetDeviceUnitFromRealValue(double realValue,
    int* deviceUnits, int unitType) {

    // STATIC_DLL_FUNC(kinesisDll, KIM_GetDeviceUnitFromRealValue, func);
    // return func(CSerialNo(), realValue, deviceUnits, unitType);
    // not really used; just do nothing and return a good value
    return 0; // 0 -- ok
}
