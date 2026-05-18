#pragma once
#include <juce_dsp/juce_dsp.h>

namespace sintetizador_monofonico {

class Waveforms {
public:

  enum class WaveformType {
    sine,
    triangle,
    saw,
    square
};

  void prepare(double sampleRate, int samplesPerBlock);
  void reset();

  float processOsc1();
  float processOsc2();
  float processOsc3();

  void setFrequency(float frequency);

  void setOsc1Waveform(WaveformType waveform);
  void setOsc2Waveform(WaveformType waveform);
  void setOsc3Waveform(WaveformType waveform);

  void setOsc2Detune(float semitones);
  void setOsc3Detune(float semitones);

  void setOsc1Octave(int octave);
  void setOsc2Octave(int octave);
  void setOsc3Octave(int octave);

private:

  void rebuildOscillator(juce::dsp::Oscillator<float>& osc, WaveformType type);
  void updateFrequencies();



  float currentFrequency = 440.f;

  float osc2Detune = 0.f;
  float osc3Detune = 0.f;

  int osc1Octave = 0;
  int osc2Octave = 0;
  int osc3Octave = 0;

  WaveformType osc1Waveform = WaveformType::saw;
  WaveformType osc2Waveform = WaveformType::saw;
  WaveformType osc3Waveform = WaveformType::saw;

  juce::dsp::Oscillator<float> osc1;
  juce::dsp::Oscillator<float> osc2;
  juce::dsp::Oscillator<float> osc3;


  static float sine(float phase);
  static float triangle(float phase);
  static float saw(float phase);
  static float square(float phase);
};

} // namespace sintetizador_monofonico