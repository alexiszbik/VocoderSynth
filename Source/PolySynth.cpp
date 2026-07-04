#include "PolySynth.h"

#include <algorithm>

PolySynth::PolySynth() {
    for (size_t i = 0; i < VOICE_COUNT; i++) {
        voices.push_back(new SynthVoice());
    }
}

PolySynth::~PolySynth() {
    for (auto* voice : voices) {
        delete voice;
    }
    voices.clear();
}

void PolySynth::init(double sampleRate) {
    for (auto* voice : voices) {
        voice->init(sampleRate);
    }
}

void PolySynth::setFixedEnvelope(float attack, float decay, float sustain) {
    for (auto* voice : voices) {
        voice->setFixedEnvelope(attack, decay, sustain);
    }
}

void PolySynth::setGlide(float glide) {
    for (auto* voice : voices) {
        voice->setGlide(glide);
    }
}

void PolySynth::setRelease(float release) {
    for (auto* voice : voices) {
        voice->setRelease(release);
    }
}

void PolySynth::setNote(bool isNoteOn, Note note) {
    if (isNoteOn) {
        note.timeStamp = timeStamp++;
        noteState.push_back(note);

        int order[VOICE_COUNT];
        for (int k = 0; k < VOICE_COUNT; k++) {
            order[k] = k;
        }

        std::sort(order, order + VOICE_COUNT, [&](int a, int b) {
            unsigned long ta = voices.at(a)->noteTimeStamp;
            unsigned long tb = voices.at(b)->noteTimeStamp;
            if (ta != tb) {
                return ta < tb;
            }
            return a < b;
        });

        for (int j = 0; j < VOICE_COUNT; j++) {
            int i = order[j];
            if (!voices.at(i)->isPlaying()) {
                voices.at(i)->setNoteOn(note);
                return;
            }
        }

        for (int j = 0; j < VOICE_COUNT; j++) {
            int i = order[j];
            if (!voices.at(i)->isPressed()) {
                voices.at(i)->setNoteOn(note);
                return;
            }
        }

        voices.at(order[0])->setNoteOn(note);
        return;
    }

    for (auto it = noteState.begin(); it != noteState.end();) {
        if (it->pitch == note.pitch) {
            it = noteState.erase(it);
        } else {
            ++it;
        }
    }

    for (int i = 0; i < VOICE_COUNT; i++) {
        if (voices.at(i)->currentPitch() == note.pitch && voices.at(i)->isPlaying()) {
            voices.at(i)->setNoteOff();
        }
    }
}

float PolySynth::process() {
    float result = 0.f;

    for (auto* voice : voices) {
        result += voice->process();
    }

    return result * 0.707f * 0.65f;
}
