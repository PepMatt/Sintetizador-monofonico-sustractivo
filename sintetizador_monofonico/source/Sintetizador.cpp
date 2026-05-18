#include "Sintetizador.h"

namespace sintetizador_monofonico {

// =========================================
// PREPARE
// =========================================
void Sintetizador::prepare(double sampleRate, int samplesPerBlock)
{
  waveforms.prepare(sampleRate, samplesPerBlock);
  filter.prepare(sampleRate);
  ampEnvelope.prepare(sampleRate);
}

// =========================================
// RESET
// =========================================
void Sintetizador::reset()
{
  waveforms.reset();
  filter.reset();
  ampEnvelope.reset();
}

// =========================================
// FREQUENCY
// =========================================
void Sintetizador::setFrequency(float frequency)
{
  waveforms.setFrequency(frequency);
}

// =========================================
// NOTE ON / OFF
// =========================================
void Sintetizador::noteOn()
{
  ampEnvelope.noteOn();
}

void Sintetizador::noteOff()
{
  ampEnvelope.noteOff();
}

// =========================================
// AUDIO RENDER
// =========================================
float Sintetizador::processSample()
{
  OscMixer::OscillatorState osc1 { waveforms.processOsc1(), 1.f, true };
  OscMixer::OscillatorState osc2 { waveforms.processOsc2(), 1.f, true };
  OscMixer::OscillatorState osc3 { waveforms.processOsc3(), 1.f, true };

  float mixed   = mixer.process(osc1, osc2, osc3);
  float filtered = filter.process(mixed);
  float output   = ampEnvelope.process(filtered);

  return output;
}

// =========================================
// STATE
// =========================================
bool Sintetizador::isActive() const
{
  return ampEnvelope.isActive();
}
void Sintetizador::setEnvelopeParameters(float attack,
                                         float decay,
                                         float sustain,
                                         float release)
{
  ampEnvelope.setParameters(attack,
                            decay,
                            sustain,
                            release);
}

} // namespace sintetizador_monofonico