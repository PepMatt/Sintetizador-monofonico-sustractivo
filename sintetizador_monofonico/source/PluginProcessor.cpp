#pragma once



namespace sintetizador_monofonico {

PluginProcessor::PluginProcessor()
:
  apvts(*this,
        nullptr,
        "PARAMETERS",
        createParameters())
{
  // Polifonia de 8 voces
  // for (int i = 0; i < 8; ++i)
    synth.addVoice(new MiniMoogVoice());

  synth.addSound(new MiniMoogSound());
}

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  synth.setCurrentPlaybackSampleRate(sampleRate);

  for (int i = 0; i < synth.getNumVoices(); ++i)
    if (auto* v = dynamic_cast<MiniMoogVoice*>(synth.getVoice(i)))
      v->prepare(sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                   juce::MidiBuffer& midi)
{
  juce::ScopedNoDenormals noDenormals;

  for (int ch = getTotalNumInputChannels();
       ch < getTotalNumOutputChannels(); ++ch) {
    buffer.clear(ch, 0, buffer.getNumSamples());
  }
  const auto attack =
    apvts.getRawParameterValue("ATTACK")->load();

  const auto decay =
      apvts.getRawParameterValue("DECAY")->load();

  const auto sustain =
      apvts.getRawParameterValue("SUSTAIN")->load();

  const auto release =
      apvts.getRawParameterValue("RELEASE")->load();

  for (int i = 0; i < synth.getNumVoices(); ++i)
  {
    if (auto* voice =
        dynamic_cast<MiniMoogVoice*>(synth.getVoice(i)))
    {
      voice->setEnvelopeParameters(attack,
                                   decay,
                                   sustain,
                                   release);
    }
  }

  synth.renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
}

bool PluginProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
  return new juce::GenericAudioProcessorEditor(*this);
}

juce::AudioProcessorValueTreeState::ParameterLayout

PluginProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

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



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new sintetizador_monofonico::PluginProcessor();
}
