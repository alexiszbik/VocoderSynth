#pragma once

#include "DaisyYMNK/DSP/DSP.h"
#include "PolySynth.h"

#define MIDI_CC_START 10

namespace ydaisy {

class VocoderSynthDSP : public DSPKernel {
public:
    enum Parameters {
        Glide,
        Release,
        Count
    };

    VocoderSynthDSP();

    void init(int channelCount, double sampleRate) override;
    void process(float** buf, int frameCount) override;
    void processMIDI(MIDIMessageType messageType, int channel, int dataA, int dataB) override;

protected:
    void updateParameter(int index, float value) override;

private:
    static constexpr float kAttack = 0.02f;
    static constexpr float kDecay = 0.02f;
    static constexpr float kSustain = 1.f;

    PolySynth synth;
    unsigned long timeStamp = 0;
};

}
