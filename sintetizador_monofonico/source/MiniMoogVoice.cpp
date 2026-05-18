#include "MiniMoogVoice.h"

namespace sintetizador_monofonico {

// =========================================
// PREPARE
// =========================================
void MiniMoogVoice::prepare(double sampleRate, int samplesPerBlock)
{
  sintetizador.prepare(sampleRate, samplesPerBlock);

  smoothedFrequency.reset(sampleRate, 0.05); // default 50ms glide
  smoothedFrequency.setCurrentAndTargetValue(440.f);
}

// =========================================
// CAN PLAY SOUND
// =========================================
bool MiniMoogVoice::canPlaySound(juce::SynthesiserSound* sound)
{
  return dynamic_cast<MiniMoogSound*>(sound) != nullptr;
}

// =========================================
// START NOTE
// =========================================
void MiniMoogVoice::startNote(int midiNoteNumber,
                              float velocity,
                              juce::SynthesiserSound*,
                              int)
{
  juce::ignoreUnused(velocity);

  const float freq =
       juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

  smoothedFrequency.setTargetValue(freq);

  sintetizador.noteOn();
}

// =========================================
// STOP NOTE
// =========================================
void MiniMoogVoice::stopNote(float, bool allowTailOff)
{
  sintetizador.noteOff();

  if (!allowTailOff)
    clearCurrentNote();
}

// =========================================
// RENDER AUDIO
// =========================================
void MiniMoogVoice::renderNextBlock(juce::AudioBuffer<float>& buffer,
                                    int startSample,
                                    int numSamples)
{
  if (!isVoiceActive())
    return;

  for (int i = 0; i < numSamples; ++i)
  {
    const float freq = smoothedFrequency.getNextValue();

    sintetizador.setFrequency(freq);

    const float sample = sintetizador.processSample(freq);

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
      buffer.addSample(ch, startSample + i, sample);
  }

  if (!sintetizador.isActive())
    clearCurrentNote();
}
void MiniMoogVoice::setEnvelopeParameters(float attack,
                                          float decay,
                                          float sustain,
                                          float release)
{
  sintetizador.setEnvelopeParameters(attack,
                                     decay,
                                     sustain,
                                     release);
}
void MiniMoogVoice::setOscParameters(int osc1Wave,
                                     int osc2Wave,
                                     int osc3Wave,
                                     int osc1Oct,
                                     int osc2Oct,
                                     int osc3Oct,
                                     float osc2Detune,
                                     float osc3Detune)
{
  sintetizador.setOscParameters(
      osc1Wave, osc2Wave, osc3Wave,
      osc1Oct, osc2Oct, osc3Oct,
      osc2Detune, osc3Detune);
}
void MiniMoogVoice::setFilterParameters(float cutoff,
                                        float resonance,
                                        float drive,
                                        int mode)
{
  sintetizador.setFilterParameters(cutoff, resonance, drive, mode);
}
void MiniMoogVoice::setGlide(float glideTimeSeconds)
{
  if (currentGlideTime == glideTimeSeconds)
    return;

  currentGlideTime = glideTimeSeconds;

  smoothedFrequency.reset(
      getSampleRate(),
      glideTimeSeconds
  );
}
} // namespace sintetizador_monofonico