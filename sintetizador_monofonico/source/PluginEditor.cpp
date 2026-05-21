#include "PluginEditor.h"

namespace sintetizador_monofonico {

PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),

      osc1WaveAttachment(p.apvts, "OSC1_WAVE", osc1Wave),
      osc2WaveAttachment(p.apvts, "OSC2_WAVE", osc2Wave),
      osc3WaveAttachment(p.apvts, "OSC3_WAVE", osc3Wave),

      osc1OctAttachment(p.apvts, "OSC1_OCT", osc1Oct),
      osc2OctAttachment(p.apvts, "OSC2_OCT", osc2Oct),
      osc3OctAttachment(p.apvts, "OSC3_OCT", osc3Oct),

      osc2DetuneAttachment(p.apvts, "OSC2_DETUNE", osc2Detune),
      osc3DetuneAttachment(p.apvts, "OSC3_DETUNE", osc3Detune),

      cutoffAttachment(p.apvts, "FILTER_CUTOFF", cutoff),
      resonanceAttachment(p.apvts, "FILTER_RESONANCE", resonance),
      driveAttachment(p.apvts, "FILTER_DRIVE", drive),

      filterModeAttachment(p.apvts, "FILTER_MODE", filterMode),

      attackAttachment(p.apvts, "ATTACK", attack),
      decayAttachment(p.apvts, "DECAY", decay),
      sustainAttachment(p.apvts, "SUSTAIN", sustain),
      releaseAttachment(p.apvts, "RELEASE", release),

      glideAttachment(p.apvts, "GLIDE", glide),
      gainAttachment(p.apvts, "MASTER_GAIN", gain)
{
    setSize(1280, 620);

    // =========================================
    // KNOBS
    // =========================================
    for (auto* slider : {
        &osc1Oct,
        &osc2Oct,
        &osc3Oct,
        &osc2Detune,
        &osc3Detune,
        &cutoff,
        &resonance,
        &drive,
        &attack,
        &decay,
        &sustain,
        &release,
        &glide,
        &gain
    })
    {
        setupKnob(*slider);
    }

    // =========================================
    // WAVE SELECTORS
    // =========================================
    const juce::StringArray waveformItems
    {
        "SINE",
        "TRI",
        "SAW",
        "RSAW",
        "SQR",
        "WPULSE",
        "NPULSE"
    };

    for (auto* box : { &osc1Wave, &osc2Wave, &osc3Wave })
    {
        for (int i = 0; i < waveformItems.size(); ++i)
        {
            box->addItem(
                waveformItems[i],
                i + 1);
        }

        setupWaveBox(*box);
    }

    // =========================================
    // FILTER MODES
    // =========================================
    filterMode.addItem("LP", 1);
    filterMode.addItem("HP", 2);
    filterMode.addItem("BP", 3);

    setupWaveBox(filterMode);

    // =========================================
    // LABELS
    // =========================================
    setupLabel(osc1Label, "OSC 1");
    setupLabel(osc2Label, "OSC 2");
    setupLabel(osc3Label, "OSC 3");

    setupLabel(filterModeLabel, "FILTER");

    setupLabel(osc1OctLabel, "OCTAVA");
    setupLabel(osc2OctLabel, "OCTAVA 2");
    setupLabel(osc2DetuneLabel, "DETUNE 2");
    setupLabel(osc3OctLabel, "OCTAVA 3");
    setupLabel(osc3DetuneLabel, "DETUNE 3");

    setupLabel(cutoffLabel, "CUTOFF");
    setupLabel(resonanceLabel, "RESONANCE");
    setupLabel(driveLabel, "DRIVE");
    setupLabel(glideLabel, "GLIDE");

    setupLabel(attackLabel, "ATTACK");
    setupLabel(decayLabel, "DECAY");
    setupLabel(sustainLabel, "SUSTAIN");
    setupLabel(releaseLabel, "RELEASE");
    setupLabel(gainLabel, "GAIN");
}

// =========================================
// SETUP KNOB
// =========================================
void PluginEditor::setupKnob(juce::Slider& slider)
{
    slider.setSliderStyle(
        juce::Slider::RotaryVerticalDrag);

    slider.setColour(
        juce::Slider::rotarySliderFillColourId,
        juce::Colours::pink);

    slider.setColour(
        juce::Slider::thumbColourId,
        juce::Colours::white);

    slider.setColour(
        juce::Slider::textBoxTextColourId,
        juce::Colours::white);

    slider.setColour(
        juce::Slider::textBoxOutlineColourId,
        juce::Colours::pink);

    slider.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        false,
        60,
        20);

    addAndMakeVisible(slider);
}

// =========================================
// SETUP WAVE BOX
// =========================================
void PluginEditor::setupWaveBox(juce::ComboBox& box)
{
    addAndMakeVisible(box);
}

// =========================================
// SETUP LABEL
// =========================================
void PluginEditor::setupLabel(juce::Label& label,
                              const juce::String& text)
{
    label.setText(
        text,
        juce::dontSendNotification);

    label.setJustificationType(
        juce::Justification::centred);

    label.setColour(
        juce::Label::textColourId,
        juce::Colours::white);

    addAndMakeVisible(label);
}

// =========================================
// PAINT
// =========================================
void PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(20, 20, 20));

    g.setColour(juce::Colours::pink);

    g.setFont(32.f);

    g.drawFittedText(
        "MINIMOOG STYLE SYNTH",
        0,
        10,
        getWidth(),
        40,
        juce::Justification::centred,
        1);
}

// =========================================
// RESIZED
// =========================================
void PluginEditor::resized()
{
    auto bounds = getLocalBounds().reduced(20);

    bounds.removeFromTop(55);

    constexpr int knobSize = 90;
    constexpr int labelHeight = 20;
    constexpr int comboHeight = 30;
    constexpr int columnWidth = 200;

    // =========================================
    // TOP ROW
    // =========================================
    auto topRow = bounds.removeFromTop(60);

    auto osc1Area = topRow.removeFromLeft(250);
    auto osc2Area = topRow.removeFromLeft(250);
    auto osc3Area = topRow.removeFromLeft(250);
    auto filterArea = topRow;

    osc1Label.setBounds(osc1Area.removeFromTop(20));
    osc1Wave.setBounds(osc1Area.removeFromTop(comboHeight));

    osc2Label.setBounds(osc2Area.removeFromTop(20));
    osc2Wave.setBounds(osc2Area.removeFromTop(comboHeight));

    osc3Label.setBounds(osc3Area.removeFromTop(20));
    osc3Wave.setBounds(osc3Area.removeFromTop(comboHeight));

    filterModeLabel.setBounds(filterArea.removeFromTop(20));
    filterMode.setBounds(filterArea.removeFromTop(comboHeight));

    bounds.removeFromTop(10);

    // =========================================
    // ROW 1
    // =========================================
    auto row1 = bounds.removeFromTop(120);

    auto oct1Area = row1.removeFromLeft(columnWidth);
    auto oct2Area = row1.removeFromLeft(columnWidth);
    auto det2Area = row1.removeFromLeft(columnWidth);
    auto oct3Area = row1.removeFromLeft(columnWidth);
    auto det3Area = row1.removeFromLeft(columnWidth);

    osc1Oct.setBounds(oct1Area.removeFromTop(knobSize));
    osc1OctLabel.setBounds(oct1Area.removeFromTop(labelHeight));

    osc2Oct.setBounds(oct2Area.removeFromTop(knobSize));
    osc2OctLabel.setBounds(oct2Area.removeFromTop(labelHeight));

    osc2Detune.setBounds(det2Area.removeFromTop(knobSize));
    osc2DetuneLabel.setBounds(det2Area.removeFromTop(labelHeight));

    osc3Oct.setBounds(oct3Area.removeFromTop(knobSize));
    osc3OctLabel.setBounds(oct3Area.removeFromTop(labelHeight));

    osc3Detune.setBounds(det3Area.removeFromTop(knobSize));
    osc3DetuneLabel.setBounds(det3Area.removeFromTop(labelHeight));

    // =========================================
    // ROW 2
    // =========================================
    auto row2 = bounds.removeFromTop(120);

    row2.removeFromLeft(100);

    auto cutoffArea = row2.removeFromLeft(200);
    auto resonanceArea = row2.removeFromLeft(200);
    auto driveArea = row2.removeFromLeft(200);
    auto glideArea = row2.removeFromLeft(200);

    cutoff.setBounds(cutoffArea.removeFromTop(knobSize));
    cutoffLabel.setBounds(cutoffArea.removeFromTop(labelHeight));

    resonance.setBounds(resonanceArea.removeFromTop(knobSize));
    resonanceLabel.setBounds(resonanceArea.removeFromTop(labelHeight));

    drive.setBounds(driveArea.removeFromTop(knobSize));
    driveLabel.setBounds(driveArea.removeFromTop(labelHeight));

    glide.setBounds(glideArea.removeFromTop(knobSize));
    glideLabel.setBounds(glideArea.removeFromTop(labelHeight));

    // =========================================
    // ROW 3
    // =========================================
    auto row3 = bounds.removeFromTop(120);

    auto attackArea = row3.removeFromLeft(columnWidth);
    auto decayArea = row3.removeFromLeft(columnWidth);
    auto sustainArea = row3.removeFromLeft(columnWidth);
    auto releaseArea = row3.removeFromLeft(columnWidth);
    auto gainArea = row3.removeFromLeft(columnWidth);

    attack.setBounds(attackArea.removeFromTop(knobSize));
    attackLabel.setBounds(attackArea.removeFromTop(labelHeight));

    decay.setBounds(decayArea.removeFromTop(knobSize));
    decayLabel.setBounds(decayArea.removeFromTop(labelHeight));

    sustain.setBounds(sustainArea.removeFromTop(knobSize));
    sustainLabel.setBounds(sustainArea.removeFromTop(labelHeight));

    release.setBounds(releaseArea.removeFromTop(knobSize));
    releaseLabel.setBounds(releaseArea.removeFromTop(labelHeight));

    gain.setBounds(gainArea.removeFromTop(knobSize));
    gainLabel.setBounds(gainArea.removeFromTop(labelHeight));
}

} // namespace sintetizador_monofonico