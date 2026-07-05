#include "VocoderSynthDSP.h"

using namespace ydaisy;

VocoderSynthDSP::VocoderSynthDSP()
: DSPKernel({
    {PlayMode, "Play Mode"},
    {Glide, "Glide"},
    {Release, "Release"},
}) {
}

void VocoderSynthDSP::init(int channelCount, double sampleRate) {
    DSPKernel::init(channelCount, sampleRate);

    synth.init(sampleRate);
    synth.setFixedEnvelope(kAttack, kDecay, kSustain);
    setParameterValue(PlayMode, 1.f);
    synth.setPolyMode(PolySynth::Mono);
    synth.setRelease(valueMapPow3(getValue(Release), 0.005f, 8.f));
}

PolySynth::EPolyMode VocoderSynthDSP::getPlayMode() const {
    return synth.getPolyMode();
}

bool VocoderSynthDSP::isPoly() const {
    return synth.getPolyMode() == PolySynth::Poly;
}


void VocoderSynthDSP::updateParameter(int index, float value) {
    switch (static_cast<Parameters>(index)) {
        case PlayMode:
            synth.setPolyMode(static_cast<PolySynth::EPolyMode>(valueMap(value, 0, 1)));
            break;
        case Glide:
            synth.setGlide(value);
            break;
        case Release:
            synth.setRelease(valueMapPow3(value, 0.005f, 8.f));
            break;
        default:
            break;
    }
}

void VocoderSynthDSP::processMIDI(MIDIMessageType messageType, int channel, int dataA, int dataB) {
    switch (messageType) {
        case MIDIMessageType::kNoteOn:
            synth.setNote(true, Note(dataA, dataB, timeStamp++));
            break;
        case MIDIMessageType::kNoteOff:
            synth.setNote(false, Note(dataA, 0, 0));
            break;
        case MIDIMessageType::kControlChange: {
            int parameterIndex = dataA - MIDI_CC_START;
            if (parameterIndex >= 0 && parameterIndex < getParameterCount()) {
                setParameterValue(parameterIndex, dataB / 127.f);
            }
        } break;
        default:
            break;
    }
}

void VocoderSynthDSP::process(float** buf, int frameCount) {
    DSPKernel::process(buf, frameCount);

    synth.setGlide(getValue(Glide));
    synth.setRelease(valueMapPow3(getValue(Release), 0.005f, 8.f));

    for (int i = 0; i < frameCount; i++) {
        const float out = synth.process();

        buf[0][i] = out;

        for (int channel = 1; channel < channelCount; channel++) {
            buf[channel][i] = out;
        }
    }
}
