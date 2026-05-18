#pragma once

namespace sintetizador_monofonico {

class OscMixer {
public:

    struct OscillatorState {
        float sample = 0.f;
        float level = 0.f;
        bool enabled = true;
    };

    void setOsc1Level(float newLevel)
    {
        osc1Level = newLevel;
    }

    void setOsc2Level(float newLevel)
    {
        osc2Level = newLevel;
    }

    void setOsc3Level(float newLevel)
    {
        osc3Level = newLevel;
    }

    void setNoiseLevel(float newLevel)
    {
        noiseLevel = newLevel;
    }

    void setMasterGain(float newGain)
    {
        masterGain = newGain;
    }

    float process(
        const OscillatorState& osc1,
        const OscillatorState& osc2,
        const OscillatorState& osc3,
        float noiseSample = 0.f)
    {
        float mixed = 0.f;

        // =========================================
        // OSC 1
        // =========================================
        if (osc1.enabled)
        {
            mixed += osc1.sample * osc1.level * osc1Level;
        }

        // =========================================
        // OSC 2
        // =========================================
        if (osc2.enabled)
        {
            mixed += osc2.sample * osc2.level * osc2Level;
        }

        // =========================================
        // OSC 3
        // =========================================
        if (osc3.enabled)
        {
            mixed += osc3.sample * osc3.level * osc3Level;
        }

        // =========================================
        // NOISE
        // =========================================
        mixed += noiseSample * noiseLevel;

        // =========================================
        // NORMALIZACIÓN
        // =========================================
        mixed *= outputCompensation;

        // =========================================
        // MASTER GAIN
        // =========================================
        mixed *= masterGain;

        return mixed;
    }

private:

    // =========================================
    // MIX LEVELS
    // =========================================
    float osc1Level = 0.8f;
    float osc2Level = 0.8f;
    float osc3Level = 0.8f;

    float noiseLevel = 0.f;

    // =========================================
    // MASTER
    // =========================================
    float masterGain = 1.f;

    // =========================================
    // Evita clipping excesivo al sumar osciladores
    // =========================================
    float outputCompensation = 0.33f;
};

}