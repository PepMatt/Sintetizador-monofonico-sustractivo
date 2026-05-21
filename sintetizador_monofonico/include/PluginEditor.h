#pragma once

namespace sintetizador_monofonico {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;
private:

  using SliderAttachment =
      juce::AudioProcessorValueTreeState::SliderAttachment;

  using ComboAttachment =
      juce::AudioProcessorValueTreeState::ComboBoxAttachment;

  // =========================================
  // HELPERS
  // =========================================
  void setupKnob(juce::Slider& slider);
  void setupWaveBox(juce::ComboBox& box);
  void setupLabel(juce::Label& label,
                const juce::String& text);
  // =========================================
  // PROCESSOR
  // =========================================
  PluginProcessor& processorRef;

  // =========================================
  // OSC 1
  // =========================================
  juce::ComboBox osc1Wave;
  juce::Slider osc1Oct;

  // =========================================
  // OSC 2
  // =========================================
  juce::ComboBox osc2Wave;
  juce::Slider osc2Oct;
  juce::Slider osc2Detune;

  // =========================================
  // OSC 3
  // =========================================
  juce::ComboBox osc3Wave;
  juce::Slider osc3Oct;
  juce::Slider osc3Detune;

  // =========================================
  // FILTER
  // =========================================
  juce::Slider cutoff;
  juce::Slider resonance;
  juce::Slider drive;
  juce::ComboBox filterMode;

  // =========================================
  // ADSR
  // =========================================
  juce::Slider attack;
  juce::Slider decay;
  juce::Slider sustain;
  juce::Slider release;
  // =========================================
  // MASTER
  // =========================================
  juce::Slider glide;
  juce::Slider gain;
  // =========================================
  // LABELS
  // =========================================
  juce::Label osc2WaveLabel;
  juce::Label osc2OctLabel;
  juce::Label osc2DetuneLabel;

  juce::Label osc3WaveLabel;
  juce::Label osc3OctLabel;
  juce::Label osc3DetuneLabel;

  juce::Label cutoffLabel;
  juce::Label resonanceLabel;
  juce::Label driveLabel;
  juce::Label filterModeLabel;

  juce::Label attackLabel;
  juce::Label decayLabel;
  juce::Label sustainLabel;
  juce::Label releaseLabel;

  juce::Label glideLabel;
  juce::Label gainLabel;

  // =========================================
  // ATTACHMENTS
  // =========================================

  ComboAttachment osc1WaveAttachment;
  ComboAttachment osc2WaveAttachment;
  ComboAttachment osc3WaveAttachment;

  SliderAttachment osc1OctAttachment;
  SliderAttachment osc2OctAttachment;
  SliderAttachment osc3OctAttachment;

  SliderAttachment osc2DetuneAttachment;
  SliderAttachment osc3DetuneAttachment;

  SliderAttachment cutoffAttachment;
  SliderAttachment resonanceAttachment;
  SliderAttachment driveAttachment;

  ComboAttachment filterModeAttachment;

  SliderAttachment attackAttachment;
  SliderAttachment decayAttachment;
  SliderAttachment sustainAttachment;
  SliderAttachment releaseAttachment;

  SliderAttachment glideAttachment;
  SliderAttachment gainAttachment;

  juce::Label osc1Label;
  juce::Label osc2Label;
  juce::Label osc3Label;

  juce::Label osc1OctLabel;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
