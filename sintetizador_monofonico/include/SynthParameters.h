#pragma once

namespace sintetizador_monofonico {

struct SynthParameters
{
  // OSC
  int osc1Wave = 0;
  int osc2Wave = 0;
  int osc3Wave = 0;

  int osc1Oct = 0;
  int osc2Oct = 0;
  int osc3Oct = 0;

  float osc2Detune = 0.f;
  float osc3Detune = 0.f;

  // FILTER
  float cutoff = 1000.f;
  float resonance = 0.2f;
  float drive = 1.f;
  int filterMode = 0;

  // ADSR
  float attack = 0.1f;
  float decay = 0.2f;
  float sustain = 0.8f;
  float release = 0.4f;

  // MASTER
  float gain = -6.f;

  // GLIDE
  float glide = 0.05f;
};

}