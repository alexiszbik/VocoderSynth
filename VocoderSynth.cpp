#include "daisy_seed.h"
#include "daisysp.h"

#include "DaisyYMNK/Base/DaisyBase.h"
#include "Source/VocoderSynthCore.h"

using namespace daisy;
using namespace daisysp;
using namespace ydaisy;

DaisySeed hw;
VocoderSynthCore moduleCore;
DaisyBase db = DaisyBase(&hw, &moduleCore);

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) {
    db.process(out, size);
}

int main(void) {
    db.init(AudioCallback, 64);

    for (;;) {
        db.listen();
    }
}
