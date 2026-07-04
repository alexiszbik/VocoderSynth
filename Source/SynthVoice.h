#pragma once

#include "DaisyYMNK/Common/Common.h"
#include "DaisyYMNK/DSP/DSP.h"
#include "daisysp.h"

using namespace daisysp;
using namespace ydaisy;

class SynthVoice {
public:
    void init(double sampleRate);

    void setGlide(float glide);
    void setRelease(float release);
    void setFixedEnvelope(float attack, float decay, float sustain);

    void setNoteOn(Note note);
    void setNoteOff();
    void kill();

    float process();

    int currentPitch() noexcept { return static_cast<int>(pitch.getGoal()); }
    bool isPlaying() noexcept { return gate || adsr.IsRunning(); }
    bool isPressed() noexcept { return gate; }

    unsigned long noteTimeStamp = 0;

private:
    void setPitch(int pitch);
    void setGate(bool newGate);

    double sampleRate = 48000.0;
    long glideFrameLength = 0;

    SmoothValue pitch;
    bool gate = false;

    Oscillator osc;
    SynthEnv adsr;
};
