#include "SynthVoice.h"

void SynthVoice::init(double sampleRate) {
    this->sampleRate = sampleRate;
    noteTimeStamp = 0;

    pitch.setImmediate(60.f);

    osc.Init(sampleRate);
    osc.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
    osc.SetAmp(1.f);

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
        osc.Reset();
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

    osc.SetFreq(mtof(pitch.getAndStep()));

    return osc.Process() * adsr.Process(gate);
}
