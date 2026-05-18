#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

#include "Sintetizador.h"
#include "MiniMoogSound.h"

namespace sintetizador_monofonico {

class MiniMoogVoice : public juce::SynthesiserVoice
{
public:

  void prepare(double sampleRate, int samplesPerBlock);

  bool canPlaySound(juce::SynthesiserSound* sound) override;

  void startNote(int midiNoteNumber,
                 float velocity,
                 juce::SynthesiserSound* sound,
                 int currentPitchWheelPosition) override;

  void stopNote(float velocity, bool allowTailOff) override;

  void pitchWheelMoved(int) override {}
  void controllerMoved(int, int) override {}

  void renderNextBlock(juce::AudioBuffer<float>& buffer,
                       int startSample,
                       int numSamples) override;

  void setEnvelopeParameters(float attack,
                             float decay,
                             float sustain,
                             float release);

private:

  Sintetizador sintetizador;
  float currentFrequency = 440.f;
};

} // namespace sintetizador_monofonico