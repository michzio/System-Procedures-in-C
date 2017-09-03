//
// Created by Michal Ziobro on 16/09/2016.
//

#ifndef AUTOMATION_SCRIPTS_AUDIO_H
#define AUTOMATION_SCRIPTS_AUDIO_H

// Speakers
float audio_output_get_volume(void);
void audio_output_set_volume(float level);
bool audio_output_is_muted(void);
void audio_output_mute(bool shouldBeMuted);

// Microphone
float audio_input_get_volume(void);
void audio_input_set_volume(float level);
bool audio_input_is_muted(void);
void audio_input_mute(bool shouldBeMuted);

#endif //AUTOMATION_SCRIPTS_AUDIO_H
