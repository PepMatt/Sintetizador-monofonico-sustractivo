#pragma once

namespace sintetizador_monofonico {

struct Parameters
{
  explicit Parameters(
      juce::AudioProcessorValueTreeState& apvts);

  // =========================================
  // FILTER
  // =========================================
  std::atomic<float>* filterCutoff = nullptr;
  std::atomic<float>* filterResonance = nullptr;
  std::atomic<float>* filterDrive = nullptr;
  std::atomic<float>* filterMode = nullptr;

  // =========================================
  // DETUNE
  // =========================================
  std::atomic<float>* osc2Detune = nullptr;
  std::atomic<float>* osc3Detune = nullptr;

  // =========================================
  // WAVEFORMS
  // =========================================
  std::atomic<float>* osc1Wave = nullptr;
  std::atomic<float>* osc2Wave = nullptr;
  std::atomic<float>* osc3Wave = nullptr;

  // =========================================
  // OCTAVES
  // =========================================
  std::atomic<float>* osc1Oct = nullptr;
  std::atomic<float>* osc2Oct = nullptr;
  std::atomic<float>* osc3Oct = nullptr;

  // =========================================
  // ADSR
  // =========================================
  std::atomic<float>* attack = nullptr;
  std::atomic<float>* decay = nullptr;
  std::atomic<float>* sustain = nullptr;
  std::atomic<float>* release = nullptr;

  JUCE_DECLARE_NON_COPYABLE(Parameters)
  JUCE_DECLARE_NON_MOVEABLE(Parameters)
};

} // namespace sintetizador_monofonico