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
float Sintetizador::processSample(float frequency)
{
  waveforms.setFrequency(frequency);

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
void Sintetizador::setOscParameters(int osc1Wave,
                                   int osc2Wave,
                                   int osc3Wave,
                                   int osc1Oct,
                                   int osc2Oct,
                                   int osc3Oct,
                                   float osc2Detune,
                                   float osc3Detune)
{
  waveforms.setOsc1Waveform((Waveforms::WaveformType)osc1Wave);
  waveforms.setOsc2Waveform((Waveforms::WaveformType)osc2Wave);
  waveforms.setOsc3Waveform((Waveforms::WaveformType)osc3Wave);

  waveforms.setOsc1Octave(osc1Oct);
  waveforms.setOsc2Octave(osc2Oct);
  waveforms.setOsc3Octave(osc3Oct);

  waveforms.setOsc2Detune(osc2Detune);
  waveforms.setOsc3Detune(osc3Detune);
}
void Sintetizador::setFilterParameters(float cutoff,
                                       float resonance,
                                       float drive,
                                       int mode)
{
  filter.setCutoff(cutoff);
  filter.setResonance(resonance);
  filter.setDrive(drive);
  filter.setMode((LadderFilter::FilterMode)mode);
}

} // namespace sintetizador_monofonico