#pragma once

namespace sintetizador_monofonico {
class Parameters {
public:
  float cutoff = 2000.f;
  float resonance = 0.5f;

  float attack = 0.01f;
  float decay = 0.2f;
  float sustain = 0.8f;
  float release = 0.3f;

  float masterGain = 0.8f;

  // UNISON
  int unisonVoices = 3;
  float detune = 0.1f;   // en semitonos o ratio
  float spread = 0.2f;   // estéreo
};


}
