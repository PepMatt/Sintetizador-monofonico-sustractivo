#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

namespace sintetizador_monofonico {

class Envelope {
public:

  void prepare(double sampleRate)
  {
    adsr.setSampleRate(sampleRate);
    update();
  }

  void noteOn()  { adsr.noteOn(); }
  void noteOff() { adsr.noteOff(); }
  void reset()   { adsr.reset(); }

  float process(float inputSample)
  {
    return inputSample * adsr.getNextSample();
  }

  void setAttack(float v)  { parameters.attack = v; update(); }
  void setDecay(float v)   { parameters.decay = v; update(); }
  void setSustain(float v) { parameters.sustain = v; update(); }
  void setRelease(float v) { parameters.release = v; update(); }

  void setParameters(float a, float d, float s, float r)
  {
    parameters.attack = a;
    parameters.decay = d;
    parameters.sustain = s;
    parameters.release = r;
    update();
  }
  bool isActive() const
  {
    return adsr.isActive();
  }
private:

  void update()
  {
    adsr.setParameters(parameters);
  }

private:

  juce::ADSR adsr;

  juce::ADSR::Parameters parameters;
};

}