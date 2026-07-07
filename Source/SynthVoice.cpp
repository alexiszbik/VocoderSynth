#include "SynthVoice.h"

void SynthVoice::init(double sampleRate) {
    this->sampleRate = sampleRate;
    noteTimeStamp = 0;

    pitch.setImmediate(60.f);

    squareOsc.Init(sampleRate);
    squareOsc.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
    squareOsc.SetAmp(1.f);

    sawOsc.Init(sampleRate);
    sawOsc.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    sawOsc.SetAmp(1.f);

    adsr.Init(sampleRate);
}

void SynthVoice::setGlide(float glide) {
    glideFrameLength = static_cast<long>((glide * glide) * sampleRate);
}

void SynthVoice::setRelease(float release) {
    adsr.SetReleaseTime(release);
}

void SynthVoice::setFixedEnvelope(float attack, float decay, float sustain) {
    adsr.SetAttackTime(attack);
    adsr.SetDecayTime(decay);
    adsr.SetSustainLevel(sustain);
}

void SynthVoice::setPitch(int pitchValue) {
    pitch.setValue(static_cast<float>(pitchValue));
}

void SynthVoice::setGate(bool newGate) {
    gate = newGate;
}

void SynthVoice::setNoteOn(Note note) {
    if (!adsr.IsRunning()) {
        squareOsc.Reset();
        sawOsc.Reset();
    }

    setPitch(note.pitch);
    adsr.Retrigger(false);
    setGate(true);
    noteTimeStamp = note.timeStamp;
}

void SynthVoice::setNoteOff() {
    setGate(false);
}

void SynthVoice::kill() {
    setGate(false);
    adsr.Kill();
}

float SynthVoice::process() {
    pitch.dezipperCheck(glideFrameLength);

    const float mainPitch = pitch.getAndStep();

    squareOsc.SetFreq(mtof(mainPitch));
    sawOsc.SetFreq(mtof(mainPitch - 12.f));

    const float oscMix = sqrtDryWet(squareOsc.Process(), sawOsc.Process(), 0.4f);

    return oscMix * adsr.Process(gate);
}
