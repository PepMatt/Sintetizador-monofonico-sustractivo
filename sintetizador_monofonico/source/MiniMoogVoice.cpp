#include "MiniMoogVoice.h"

namespace sintetizador_monofonico {

// =========================================
// PREPARE
// =========================================
void MiniMoogVoice::prepare(double sampleRate, int samplesPerBlock)
{
  sintetizador.prepare(sampleRate, samplesPerBlock);
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

  currentFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

  sintetizador.setFrequency(currentFrequency);
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
    const float sample = sintetizador.processSample();

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
      buffer.addSample(ch, startSample + i, sample);
  }

  // seguridad extra (tu synth decide si sigue vivo)
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
} // namespace sintetizador_monofonico