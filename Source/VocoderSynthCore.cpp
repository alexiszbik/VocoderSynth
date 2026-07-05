#include "VocoderSynthCore.h"

VocoderSynthCore::VocoderSynthCore()
: ModuleCore(&dsp, {
    {KnobGlide,     kKnob,      15,              "Glide"},
    {KnobRelease,   kKnob,      16,              "Release"},
    {ButtonPoly,    kButton,    7,              "Poly"},
    {PolyLed,       kLed,       4,              "Poly Led"},
    {MidiLed,       kLed,       1,              "Midi Led"}},
7 - 1) {
    
    
}

void VocoderSynthCore::updateHIDValue(unsigned int index, float value) {
    (void)index;
    (void)value;

    switch (index) {
        case ButtonPoly:
            isPoly = !isPoly;
            setHIDValue(PolyLed, isPoly);
            dspKernel->setParameterValue(VocoderSynthDSP::PlayMode, isPoly ? 1 : 0);
            break;
        case KnobGlide:
            dspKernel->setParameterValue(VocoderSynthDSP::Glide, value);
            break;
        case KnobRelease:
            dspKernel->setParameterValue(VocoderSynthDSP::Release, value);
            break;
    }
}


void VocoderSynthCore::processMIDI(MIDIMessageType messageType, int channel, int dataA, int dataB) {
    ModuleCore::processMIDI(messageType, channel, dataA, dataB);
    if (midiChannel == -1 || midiChannel == channel) { // Maybe do something better
        if (messageType == kNoteOn) {
            setHIDValue(MidiLed, 1);
        } else if (messageType == kNoteOff) {
            setHIDValue(MidiLed, 0);
        }
        
        if (messageType == kControlChange) {
            isPoly = dsp.isPoly();
            setHIDValue(PolyLed, isPoly);
        }
    }
}
