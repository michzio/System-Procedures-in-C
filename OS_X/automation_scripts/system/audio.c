//
// Created by Michal Ziobro on 16/09/2016.
//

#import <AudioToolbox/AudioServices.h>
#include "audio.h"
#import "../../../../server/common/types.h"

enum audio_direction {
    kAudioOutput,
    kAudioInput
};
typedef enum audio_direction audio_direction_t;

static AudioDeviceID audio_default_device_id(audio_direction_t audioDirection) {

    AudioDeviceID deviceID = kAudioObjectUnknown;
    UInt32 deviceIDSize = (UInt32) sizeof(AudioDeviceID);

    AudioObjectPropertyAddress aopa;
    aopa.mScope = kAudioObjectPropertyScopeGlobal;
    aopa.mElement = kAudioObjectPropertyElementMaster;

    switch (audioDirection) {
        case kAudioOutput:
            aopa.mSelector = kAudioHardwarePropertyDefaultOutputDevice;
            break;
        case kAudioInput:
            aopa.mSelector = kAudioHardwarePropertyDefaultInputDevice;
            break;
        default:
            fprintf(stderr, "%s: Incorrect audio direction specified!\n", __func__);
            return deviceID;
    }

    // check availability of default device id
    if( AudioHardwareServiceHasProperty(kAudioObjectSystemObject, &aopa) == false ) {
        fprintf(stderr, "%s: Could not find default device id!\n", __func__);
        return deviceID;
    }

    // request to get default device id
    if( AudioHardwareServiceGetPropertyData(kAudioObjectSystemObject, &aopa, 0, NULL, &deviceIDSize, &deviceID) ) {
        fprintf(stderr, "%s: Could not find default device id!\n", __func__);
    }

    return deviceID;
}

static AudioDeviceID audio_output_default_device_id(void) {
    return audio_default_device_id(kAudioOutput);
}

static AudioDeviceID audio_input_default_device_id(void) {
    return audio_default_device_id(kAudioInput);
}

static result_t audio_get_property(audio_direction_t audioDirection, AudioObjectPropertySelector propertySelector, void *data, UInt32 *dataSize) {

    AudioObjectPropertyAddress aopa;
    aopa.mElement = kAudioObjectPropertyElementMaster;
    aopa.mSelector = propertySelector;

    switch(audioDirection) {
        case kAudioOutput:
            aopa.mScope = kAudioDevicePropertyScopeOutput;
            break;
        case kAudioInput:
            aopa.mScope = kAudioDevicePropertyScopeInput;
            break;
        default:
            fprintf(stderr, "%s: Incorrect audio direction specified!\n", __func__);
            data = NULL; *dataSize = 0;
            return FAILURE;
    }

    // get default device id
    AudioDeviceID deviceID = audio_default_device_id(audioDirection);
    if(deviceID == kAudioObjectUnknown) {
        fprintf(stderr, "%s: Unknown default device!\n", __func__);
        data = NULL; *dataSize = 0;
        return FAILURE;
    }

    // check availability of given property on device
    if( AudioHardwareServiceHasProperty(deviceID, &aopa) == false ) {
        fprintf(stderr, "%s: Device 0x%0x does not support given property.\n", __func__, deviceID);
        data = NULL; *dataSize = 0;
        return FAILURE;
    }

    // request to get value of given property on device
    if( AudioHardwareServiceGetPropertyData(deviceID, &aopa, 0, NULL, dataSize, data) ) {
        fprintf(stderr, "%s: Unable to get property for device 0x%0x\n", __func__, deviceID);
        data = NULL; *dataSize = 0;
        return FAILURE;
    }

    return SUCCESS;
}

static void audio_set_property(audio_direction_t audioDirection, AudioObjectPropertySelector propertySelector, const void *data, UInt32 dataSize) {

    AudioObjectPropertyAddress aopa;
    aopa.mElement = kAudioObjectPropertyElementMaster;
    aopa.mSelector = propertySelector;

    switch(audioDirection) {
        case kAudioOutput:
            aopa.mScope = kAudioDevicePropertyScopeOutput;
            break;
        case kAudioInput:
            aopa.mScope = kAudioDevicePropertyScopeInput;
            break;
        default:
            fprintf(stderr, "%s: Incorrect audio direction specified!\n", __func__);
            return;
    }

    // get default device id
    AudioDeviceID deviceID = audio_default_device_id(audioDirection);
    if(deviceID == kAudioObjectUnknown) {
        fprintf(stderr, "%s: Unknown default device!\n", __func__);
        return;
    }

    // check availability of given property on device
    if( AudioHardwareServiceHasProperty(deviceID, &aopa) == false ) {
        fprintf(stderr, "%s: Device 0x%0x does not support given property.\n", __func__, deviceID);
        return;
    }

    // check that given property can be set on device
    Boolean property_settable = false;
    OSStatus status = AudioHardwareServiceIsPropertySettable(deviceID, &aopa, &property_settable);
    if(status || !property_settable) {
        fprintf(stderr, "%s: Device 0x%0x does not support given property.\n", __func__, deviceID);
        return;
    }

    // request to set property on device
    if( AudioHardwareServiceSetPropertyData(deviceID, &aopa, 0, NULL, dataSize, data)) {
        fprintf(stderr, "%s: Unable to set property for device 0x%0x\n", __func__, deviceID);
    }
}

static result_t audio_output_get_property(AudioObjectPropertySelector propertySelector, void *data, UInt32 *dataSize) {
    return audio_get_property(kAudioOutput, propertySelector, data, dataSize);
}

static void audio_output_set_property(AudioObjectPropertySelector propertySelector, const void *data, UInt32 dataSize) {
    audio_set_property(kAudioOutput, propertySelector, data, dataSize);
}

static result_t audio_input_get_property(AudioObjectPropertySelector propertySelector, void *data, UInt32 *dataSize) {
    return audio_get_property(kAudioInput, propertySelector, data, dataSize);
}

static void audio_input_set_property(AudioObjectPropertySelector propertySelector, const void *data, UInt32 dataSize) {
    audio_set_property(kAudioInput, propertySelector, data, dataSize);
}

// Speakers
float audio_output_get_volume(void) {

    Float32 level;
    UInt32 levelSize = (UInt32) sizeof(Float32);

    if(audio_output_get_property(kAudioHardwareServiceDeviceProperty_VirtualMasterVolume, &level, &levelSize) == FAILURE) {
        fprintf(stderr, "%s: Getting volume property for output device has failed!\n", __func__);
        return 0.0f;
    }

    // limit volume level to [0,1] range
    level = (level < 0.0f) ? 0.0f : ( (level > 1.0f) ? 1.0f : level );

    return level;
}

void audio_output_set_volume(float level) {

    // limit volume level to [0.0, 1.0] range
    level = (level < 0.0f) ? 0.0f : ( (level > 1.0f) ? 1.0f : level);
    if(level < 0.01) // just mute
        return audio_output_mute(true);

    printf("%s: Setting output audio volume to %d%%\n", __func__, (int) (level * 100));
    audio_output_set_property(kAudioHardwareServiceDeviceProperty_VirtualMasterVolume, &level, (UInt32) sizeof(level));

    // make sure output device is not muted
    audio_output_mute(false);
}

bool audio_output_is_muted(void) {

    UInt32 isMuted;
    UInt32 muteSize = (UInt32) sizeof(UInt32);

    if( audio_output_get_property(kAudioDevicePropertyMute, &isMuted, &muteSize) == FAILURE) {
        fprintf(stderr, "%s: Getting mute property for output device has fialed!\n", __func__);
        return false;
    }

    return (bool) isMuted;
}

void audio_output_mute(bool shouldBeMuted) {

    printf("%s: Muting/Unmuting audio output.\n", __func__);
    UInt32 mute = (UInt32) shouldBeMuted;

    audio_output_set_property(kAudioDevicePropertyMute, &mute, (UInt32) sizeof(mute));
}

// Microphone
float audio_input_get_volume(void) {

    Float32 level;
    UInt32 levelSize = (UInt32) sizeof(Float32);

    if(audio_input_get_property(kAudioHardwareServiceDeviceProperty_VirtualMasterVolume, &level, &levelSize) == FAILURE) {
        fprintf(stderr, "%s: Getting volume property for input device has failed!\n", __func__);
        return 0.0f;
    }

    // limit volume level to [0.0, 1.0] range
    level = (level < 0.0f) ? 0.0f : ( (level > 1.0f) ? 1.0f : level );

    return level;
}

void audio_input_set_volume(float level) {

    // limit volume level to [0.0, 1.0] range
    level = (level < 0.0f) ? 0.0f : ( (level > 1.0f) ? 1.0f : level);
    if(level < 0.01) // just mute
        return audio_input_mute(true);

    printf("%s: Setting input audio volume to %d%%\n", __func__, (int) (level * 100));
    audio_input_set_property(kAudioHardwareServiceDeviceProperty_VirtualMasterVolume, &level, (UInt32) sizeof(level));

    // make sure input device is not muted
    audio_input_mute(false);
}

bool audio_input_is_muted(void) {

    UInt32 isMuted;
    UInt32 muteSize = (UInt32) sizeof(UInt32);

    if( audio_input_get_property(kAudioDevicePropertyMute, &isMuted, &muteSize) == FAILURE) {
        fprintf(stderr, "%s: Getting mute property for input device has fialed!\n", __func__);
        return false;
    }

    return (bool) isMuted;
}

void audio_input_mute(bool shouldBeMuted) {

    printf("%s: Muting/Unmuting audio input.\n", __func__);
    UInt32 mute = (UInt32) shouldBeMuted;

    audio_input_set_property(kAudioDevicePropertyMute, &mute, (UInt32) sizeof(mute));
}
