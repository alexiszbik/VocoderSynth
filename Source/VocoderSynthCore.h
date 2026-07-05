#pragma once

#include "DaisyYMNK/DSP/DSP.h"
#include "VocoderSynthDSP.h"

class VocoderSynthCore : public ydaisy::ModuleCore {
    
    enum {
        KnobGlide,
        KnobRelease,

        ButtonPoly,
        PolyLed,
        
        MidiLed
    };
    
public:
    VocoderSynthCore();

protected:
    void updateHIDValue(unsigned int index, float value) override;
    
    void processMIDI(MIDIMessageType messageType, int channel, int dataA, int dataB) override;

private:
    ydaisy::VocoderSynthDSP dsp;
};
