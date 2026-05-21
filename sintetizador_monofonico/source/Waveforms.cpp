#include "Waveforms.h"
#include <cmath>
namespace sintetizador_monofonico {

// =========================================
// PREPARE
// =========================================
void Waveforms::prepare(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate       = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels      = 1;

    osc1.prepare(spec);
    osc2.prepare(spec);
    osc3.prepare(spec);

    rebuildOscillator(osc1, osc1Waveform);
    rebuildOscillator(osc2, osc2Waveform);
    rebuildOscillator(osc3, osc3Waveform);

    updateFrequencies();
}

// =========================================
// RESET
// =========================================
void Waveforms::reset()
{
    osc1.reset();
    osc2.reset();
    osc3.reset();
}

// =========================================
// PROCESS
// =========================================
float Waveforms::processOsc1()
{
    return osc1.processSample(0.f);
}

float Waveforms::processOsc2()
{
    return osc2.processSample(0.f);
}

float Waveforms::processOsc3()
{
    return osc3.processSample(0.f);
}

// =========================================
// FREQUENCY
// =========================================
void Waveforms::setFrequency(float frequency)
{
    currentFrequency = frequency;

    updateFrequencies();
}

// =========================================
// WAVEFORM REBUILD
// =========================================
void Waveforms::rebuildOscillator(
    juce::dsp::Oscillator<float>& osc,
    WaveformType type)
{
    switch (type)
    {
        case WaveformType::sine:
            osc.initialise(sine);
            break;

        case WaveformType::triangle:
            osc.initialise(triangle);
            break;

        case WaveformType::saw:
            osc.initialise(saw);
            break;

        case WaveformType::square:
            osc.initialise(square);
            break;
      case WaveformType::reverseSaw:
        osc.initialise(reverseSaw);
        break;

      case WaveformType::widePulse:
        osc.initialise(widePulse);
        break;

      case WaveformType::narrowPulse:
        osc.initialise(narrowPulse);
        break;
    }
}

// =========================================
// FREQUENCY UPDATE
// =========================================
void Waveforms::updateFrequencies()
{
    osc1.setFrequency(
        currentFrequency *
        std::pow(2.f, static_cast<float>(osc1Octave))
    );

    osc2.setFrequency(
        currentFrequency *
        std::pow(2.f, static_cast<float>(osc2Octave)) *
        std::pow(2.f, osc2Detune / 12.f)
    );

    osc3.setFrequency(
        currentFrequency *
        std::pow(2.f, static_cast<float>(osc3Octave)) *
        std::pow(2.f, osc3Detune / 12.f)
    );
}

// =========================================
// SETTERS
// =========================================
void Waveforms::setOsc1Waveform(WaveformType w)
{
    osc1Waveform = w;
    rebuildOscillator(osc1, w);
}

void Waveforms::setOsc2Waveform(WaveformType w)
{
    osc2Waveform = w;
    rebuildOscillator(osc2, w);
}

void Waveforms::setOsc3Waveform(WaveformType w)
{
    osc3Waveform = w;
    rebuildOscillator(osc3, w);
}

void Waveforms::setOsc2Detune(float v)
{
    osc2Detune = v;
    updateFrequencies();
}

void Waveforms::setOsc3Detune(float v)
{
    osc3Detune = v;
    updateFrequencies();
}

void Waveforms::setOsc1Octave(int v)
{
    osc1Octave = v;
    updateFrequencies();
}

void Waveforms::setOsc2Octave(int v)
{
    osc2Octave = v;
    updateFrequencies();
}

void Waveforms::setOsc3Octave(int v)
{
    osc3Octave = v;
    updateFrequencies();
}

// =========================================
// WAVEFORMS
// =========================================
float Waveforms::sine(float phase)
{
    return std::sin(phase);
}

float Waveforms::triangle(float phase)
{
    const auto offsetPhase =
        phase - juce::MathConstants<float>::halfPi;

    const auto ft =
        offsetPhase / juce::MathConstants<float>::twoPi;

    return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
}

float Waveforms::saw(float phase)
{
    const auto normalized =
        phase / juce::MathConstants<float>::twoPi;

    return 2.f * (normalized - std::floor(normalized + 0.5f));
}

float Waveforms::reverseSaw(float phase)
{
  const auto normalized =
      phase / juce::MathConstants<float>::twoPi;

  return -2.f * (normalized - std::floor(normalized + 0.5f));
}

float Waveforms::square(float phase)
{
    return std::sin(phase) >= 0.f ? 1.f : -1.f;
}

float Waveforms::widePulse(float phase)
{
  const auto normalized =
      (phase + juce::MathConstants<float>::pi)
      / juce::MathConstants<float>::twoPi;

  return normalized < 0.75f ? 1.f : -1.f;
}

float Waveforms::narrowPulse(float phase)
{
  const auto normalized =
      (phase + juce::MathConstants<float>::pi)
      / juce::MathConstants<float>::twoPi;

  return normalized < 0.25f ? 1.f : -1.f;
}

} // namespace sintetizador_monofonico