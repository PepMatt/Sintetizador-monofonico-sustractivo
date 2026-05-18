#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

namespace sintetizador_monofonico {

class MiniMoogSound : public juce::SynthesiserSound
{
public:

  bool appliesToNote(int) override { return true; }
  bool appliesToChannel(int) override { return true; }
};

}