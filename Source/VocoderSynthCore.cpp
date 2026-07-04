#include "VocoderSynthCore.h"

VocoderSynthCore::VocoderSynthCore()
: ModuleCore(&dsp, {}, -1) {
}

void VocoderSynthCore::updateHIDValue(unsigned int index, float value) {
    (void)index;
    (void)value;
}
