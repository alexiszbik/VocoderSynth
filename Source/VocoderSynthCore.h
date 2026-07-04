#pragma once

#include "DaisyYMNK/DSP/DSP.h"
#include "VocoderSynthDSP.h"

class VocoderSynthCore : public ydaisy::ModuleCore {
public:
    VocoderSynthCore();

protected:
    void updateHIDValue(unsigned int index, float value) override;

private:
    ydaisy::VocoderSynthDSP dsp;
};
