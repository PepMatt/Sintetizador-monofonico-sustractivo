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

}