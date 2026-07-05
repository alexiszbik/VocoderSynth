#include "VocoderSynthCore.h"

VocoderSynthCore::VocoderSynthCore()
: ModuleCore(&dsp, {
    {KnobGlide,     kKnob,      5,              "Glide"},
    {KnobRelease,   kKnob,      6,              "Release"},
    {ButtonPoly,    kButton,    7,              "Poly"},
    {PolyLed,       kLed,       8,              "Poly Led"},
    {MidiLed,       kLed,       1,              "Midi Led"}},
7 - 1) {
}

void VocoderSynthCore::updateHIDValue(unsigned int index, float value) {
    (void)index;
    (void)value;
}


void VocoderSynthCore::processMIDI(MIDIMessageType messageType, int channel, int dataA, int dataB) {
    ModuleCore::processMIDI(messageType, channel, dataA, dataB);
    if (midiChannel == -1 || midiChannel == channel) { // Maybe do something better
        if (messageType == kNoteOn) {
            setHIDValue(MidiLed, 1);
        } else if (messageType == kNoteOff) {
            setHIDValue(MidiLed, 0);
        }
        
    }
}
