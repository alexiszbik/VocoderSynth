#include "MainComponent.h"

MainComponent::MainComponent()
: TestModuleComponent({new Project("VocoderSynth", new VocoderSynthCore())}) {
}
