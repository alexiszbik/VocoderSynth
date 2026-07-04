#pragma once

#include "DaisyYMNK/Common/Common.h"
#include "SynthVoice.h"

#define VOICE_COUNT 4

class PolySynth {
public:
    PolySynth();
    ~PolySynth();

    void init(double sampleRate);
    void setNote(bool isNoteOn, Note note);

    void setGlide(float glide);
    void setRelease(float release);
    void setFixedEnvelope(float attack, float decay, float sustain);

    float process();

private:
    std::vector<SynthVoice*> voices;
    std::vector<Note> noteState;

    unsigned long timeStamp = 0;
};
