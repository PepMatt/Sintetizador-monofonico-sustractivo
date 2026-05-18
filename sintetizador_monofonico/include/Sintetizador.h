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

  float processSample();

  bool isActive() const;

  void setEnvelopeParameters(float attack,
                           float decay,
                           float sustain,
                           float release);

private:

  Waveforms waveforms;
  OscMixer mixer;
  LadderFilter filter;
  Envelope ampEnvelope;
};

} // namespace sintetizador_monofonico