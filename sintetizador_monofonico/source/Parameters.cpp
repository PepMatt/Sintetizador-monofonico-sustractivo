#pragma once

namespace sintetizador_monofonico
{

namespace
{
    auto& addParameter(juce::AudioProcessor& processor, auto parameter)
    {
        auto& ref = *parameter;
        processor.addParameter(parameter.release());
        return ref;
    }

    juce::AudioParameterChoice& createWaveform(juce::AudioProcessor& processor)
    {
        constexpr auto versionHint = 1;

        auto param = std::make_unique<juce::AudioParameterChoice>(
            juce::ParameterID{"osc.waveform", versionHint},
            "Waveform",
            juce::StringArray{"Sine", "Triangle", "Saw"},
            0);

        return addParameter(processor, std::move(param));
    }

    juce::AudioParameterInt& createUnisonVoices(juce::AudioProcessor& processor)
    {
        constexpr auto versionHint = 1;

        auto param = std::make_unique<juce::AudioParameterInt>(
            juce::ParameterID{"unison.voices", versionHint},
            "Unison Voices",
            1,
            8,
            3);

        return addParameter(processor, std::move(param));
    }

    juce::AudioParameterFloat& createDetune(juce::AudioProcessor& processor)
    {
        constexpr auto versionHint = 1;

        auto param = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"unison.detune", versionHint},
            "Detune",
            juce::NormalisableRange{0.0f, 1.0f, 0.001f},
            0.1f);

        return addParameter(processor, std::move(param));
    }

    juce::AudioParameterFloat& createStereoSpread(juce::AudioProcessor& processor)
    {
        constexpr auto versionHint = 1;

        auto param = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"unison.spread", versionHint},
            "Stereo Spread",
            juce::NormalisableRange{0.0f, 1.0f, 0.001f},
            0.2f);

        return addParameter(processor, std::move(param));
    }

    juce::AudioParameterFloat& createGain(juce::AudioProcessor& processor)
    {
        constexpr auto versionHint = 1;

        auto param = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"amp.gain", versionHint},
            "Gain",
            juce::NormalisableRange{-60.f, 12.f, 0.1f},
            0.f,
            juce::AudioParameterFloatAttributes{}.withLabel("dB"));

        return addParameter(processor, std::move(param));
    }

    juce::AudioParameterFloat& createADSR(
        juce::AudioProcessor& processor,
        const juce::String& id,
        const juce::String& name,
        float defaultValue,
        float min,
        float max)
    {
        constexpr auto versionHint = 1;

        auto param = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{id, versionHint},
            name,
            juce::NormalisableRange{min, max, 0.001f},
            defaultValue);

        return addParameter(processor, std::move(param));
    }
}

Parameters::Parameters(juce::AudioProcessor& processor)
    : waveform{createWaveform(processor)},
      unisonVoices{createUnisonVoices(processor)},
      detune{createDetune(processor)},
      stereoSpread{createStereoSpread(processor)},
      gainDB{createGain(processor)},

      attack{createADSR(processor, "env.attack", "Attack", 0.01f, 0.001f, 5.f)},
      decay{createADSR(processor, "env.decay", "Decay", 0.2f, 0.001f, 5.f)},
      sustain{createADSR(processor, "env.sustain", "Sustain", 0.8f, 0.f, 1.f)},
      release{createADSR(processor, "env.release", "Release", 0.3f, 0.001f, 5.f)}
{
}

} // namespace sintetizador_monofonico