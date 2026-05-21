#pragma once


namespace sintetizador_monofonico {

Parameters::Parameters(
    juce::AudioProcessorValueTreeState& apvts)
{
  //GLIDE
  glide =
    apvts.getRawParameterValue("GLIDE");
  //GAIN
  masterGain =
    apvts.getRawParameterValue("MASTER_GAIN");
  // FILTER
  filterCutoff =
      apvts.getRawParameterValue("FILTER_CUTOFF");

  filterResonance =
      apvts.getRawParameterValue("FILTER_RESONANCE");

  filterDrive =
      apvts.getRawParameterValue("FILTER_DRIVE");

  filterMode =
      apvts.getRawParameterValue("FILTER_MODE");

  // DETUNE
  osc2Detune =
      apvts.getRawParameterValue("OSC2_DETUNE");

  osc3Detune =
      apvts.getRawParameterValue("OSC3_DETUNE");

  // WAVES
  osc1Wave =
      apvts.getRawParameterValue("OSC1_WAVE");

  osc2Wave =
      apvts.getRawParameterValue("OSC2_WAVE");

  osc3Wave =
      apvts.getRawParameterValue("OSC3_WAVE");

  // OCTAVES
  osc1Oct =
      apvts.getRawParameterValue("OSC1_OCT");

  osc2Oct =
      apvts.getRawParameterValue("OSC2_OCT");

  osc3Oct =
      apvts.getRawParameterValue("OSC3_OCT");

  // ADSR
  attack =
      apvts.getRawParameterValue("ATTACK");

  decay =
      apvts.getRawParameterValue("DECAY");

  sustain =
      apvts.getRawParameterValue("SUSTAIN");

  release =
      apvts.getRawParameterValue("RELEASE");
}
SynthParameters Parameters::get() const
{
  SynthParameters p;

  // WAVES
  p.osc1Wave = static_cast<int>(osc1Wave->load());
  p.osc2Wave = static_cast<int>(osc2Wave->load());
  p.osc3Wave = static_cast<int>(osc3Wave->load());

  // OCTAVES
  p.osc1Oct = static_cast<int>(osc1Oct->load());
  p.osc2Oct = static_cast<int>(osc2Oct->load());
  p.osc3Oct = static_cast<int>(osc3Oct->load());

  // DETUNE
  p.osc2Detune = osc2Detune->load();
  p.osc3Detune = osc3Detune->load();

  // FILTER
  p.cutoff = filterCutoff->load();
  p.resonance = filterResonance->load();
  p.drive = filterDrive->load();
  p.filterMode = static_cast<int>(filterMode->load());

  // ADSR
  p.attack = attack->load();
  p.decay = decay->load();
  p.sustain = sustain->load();
  p.release = release->load();

  // MASTER
  p.gain = masterGain->load();

  // GLIDE
  p.glide = glide->load();

  return p;
}
}