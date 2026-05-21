#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

#include "Sintetizador.h"
#include "MiniMoogSound.h"
#include "SynthParameters.h"

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

  // void setEnvelopeParameters(float attack,
  //                            float decay,
  //                            float sustain,
  //                            float release);
  // void setOscParameters(int osc1Wave,
  //                       int osc2Wave,
  //                       int osc3Wave,
  //                       int osc1Oct,
  //                       int osc2Oct,
  //                       int osc3Oct,
  //                       float osc2Detune,
  //                       float osc3Detune);
  // void setFilterParameters(float cutoff,
  //                        float resonance,
  //                        float drive,
  //                        int mode);
  // void setGlide(float v);
  void setParameters(const SynthParameters& params);
private:

  juce::SmoothedValue<float> smoothedFrequency;
  Sintetizador sintetizador;
  float currentFrequency = 440.f;
  float targetFrequency = 440.f;
  float glideTimeSeconds = 0.5f;
  float currentGlideTime = -1.f;
};

} // namespace sintetizador_monofonico