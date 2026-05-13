#pragma once

namespace sintetizador_monofonico {
class Waveform {
public:
  enum class WaveformType {
    sine,
    triangle,
    saw
};

  static float getSample(WaveformType type, float phase) {
    switch (type) {
      case WaveformType::sine:     return std::sin(phase);
      case WaveformType::triangle: return triangle(phase);
      case WaveformType::saw:      return saw(phase);
    }
    return 0.f;
  }


  static float triangle(float phase) {
    const auto offsetPhase = phase - juce::MathConstants<float>::halfPi;
    const auto ft = offsetPhase / juce::MathConstants<float>::twoPi;
    return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
  }

  static float saw(float phase) {
    const auto normalized = phase / juce::MathConstants<float>::twoPi;
    return 2.f * (normalized - std::floor(normalized + 0.5f));
  }
};

}
