#pragma once

namespace sintetizador_monofonico {
struct Parameters
{
  explicit Parameters(juce::AudioProcessor&);

  // ===== OSC =====
  juce::AudioParameterChoice& waveform;

  // ===== UNISON =====
  juce::AudioParameterInt& unisonVoices;
  juce::AudioParameterFloat& detune;
  juce::AudioParameterFloat& stereoSpread;

  // ===== AMP =====
  juce::AudioParameterFloat& gainDB;

  // ===== ADSR =====
  juce::AudioParameterFloat& attack;
  juce::AudioParameterFloat& decay;
  juce::AudioParameterFloat& sustain;
  juce::AudioParameterFloat& release;

  JUCE_DECLARE_NON_COPYABLE(Parameters)
  JUCE_DECLARE_NON_MOVEABLE(Parameters)
};

} // namespace sintetizador_monofonico