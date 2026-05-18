#pragma once

#include "Envelope.h"
#include "LadderFilter.h"
#include "OscMixer.h"
#include "Waveforms.h"

namespace sintetizador_monofonico {

class Sintetizador {
public:

  void prepare(double sampleRate, int samplesPerBlock);
  void reset();

  void setFrequency(float frequency);

  void noteOn();
  void noteOff();

  float processSample(float frequency);

  bool isActive() const;

  void setEnvelopeParameters(float attack,
                           float decay,
                           float sustain,
                           float release);
  void setOscParameters(int osc1Wave,
                        int osc2Wave,
                        int osc3Wave,
                        int osc1Oct,
                        int osc2Oct,
                        int osc3Oct,
                        float osc2Detune,
                        float osc3Detune);
  void setFilterParameters(float cutoff,
                         float resonance,
                         float drive,
                         int mode);

private:

  Waveforms waveforms;
  OscMixer mixer;
  LadderFilter filter;
  Envelope ampEnvelope;
};

} // namespace sintetizador_monofonico