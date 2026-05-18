#pragma once

namespace sintetizador_monofonico {

class ParameterLayoutBuilder
{
public:

  static juce::AudioProcessorValueTreeState::ParameterLayout
  create();
};

}