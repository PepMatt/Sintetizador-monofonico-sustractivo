#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

namespace sintetizador_monofonico {

class JsonSerializer
{
public:

  static juce::Result saveToStream(const juce::ValueTree& state,
                                    juce::OutputStream& output);

  static juce::Result loadFromStream(juce::ValueTree& state,
                                      juce::InputStream& input);

  static juce::var valueTreeToVar(
    const juce::ValueTree& tree);

  static juce::ValueTree varToValueTree(
      const juce::var& v);
};

} // namespace sintetizador_monofonico