#pragma once

namespace sintetizador_monofonico {

juce::AudioProcessorValueTreeState::ParameterLayout
ParameterLayoutBuilder::create()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
  parameters.push_back(
    std::make_unique<juce::AudioParameterFloat>(
        "GLIDE",
        "Glide",
        juce::NormalisableRange<float>{
            0.f,
            10.f,
            0.001f,
            0.4f
        },
        0.05f));

  parameters.push_back(
    std::make_unique<juce::AudioParameterFloat>(
        "MASTER_GAIN",
        "Master Gain",
        juce::NormalisableRange<float>{
            -24.f,
            0.f,
            0.01f,
            1.f
        },
        -6.f));

parameters.push_back(
    std::make_unique<juce::AudioParameterFloat>(
        "FILTER_CUTOFF",
        "Cutoff",
        juce::NormalisableRange{20.f, 20000.f, 0.01f, 0.5f},
        1000.f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "FILTER_RESONANCE",
          "Resonance",
          juce::NormalisableRange{0.1f, 0.9f, 0.01f},
          0.2f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "FILTER_DRIVE",
          "Drive",
          juce::NormalisableRange<float>{
              1.f,
              35.f,
              0.01f,
              0.4f
          },
          1.f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterChoice>(
          "FILTER_MODE",
          "Mode",
          juce::StringArray{"LP", "HP", "BP"},
          0));

  parameters.push_back(
    std::make_unique<juce::AudioParameterFloat>(
        "OSC2_DETUNE",
        "Osc2 Detune",
        juce::NormalisableRange{-12.f, 12.f, 0.01f},
        0.f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "OSC3_DETUNE",
          "Osc3 Detune",
          juce::NormalisableRange{-12.f, 12.f, 0.01f},
          0.f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterChoice>(
          "OSC1_WAVE",
          "Osc1 Wave",
          juce::StringArray{"Sine", "Triangle", "Saw", "Square"},
          2));

  parameters.push_back(
      std::make_unique<juce::AudioParameterChoice>(
          "OSC2_WAVE",
          "Osc2 Wave",
          juce::StringArray{"Sine", "Triangle", "Saw", "Square"},
          2));

  parameters.push_back(
      std::make_unique<juce::AudioParameterChoice>(
          "OSC3_WAVE",
          "Osc3 Wave",
          juce::StringArray{"Sine", "Triangle", "Saw", "Square"},
          2));

  parameters.push_back(
    std::make_unique<juce::AudioParameterInt>(
        "OSC1_OCT",
        "Osc1 Octave",
        -2, 2,
        0));

  parameters.push_back(
      std::make_unique<juce::AudioParameterInt>(
          "OSC2_OCT",
          "Osc2 Octave",
          -2, 2,
          0));

  parameters.push_back(
      std::make_unique<juce::AudioParameterInt>(
          "OSC3_OCT",
          "Osc3 Octave",
          -2, 2,
          0));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "ATTACK",
          "Attack",
          0.01f,
          5.f,
          0.1f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "DECAY",
          "Decay",
          0.01f,
          5.f,
          0.2f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "SUSTAIN",
          "Sustain",
          0.f,
          1.f,
          0.8f));

  parameters.push_back(
      std::make_unique<juce::AudioParameterFloat>(
          "RELEASE",
          "Release",
          0.01f,
          5.f,
          0.4f));
  return { parameters.begin(), parameters.end() };
}

}