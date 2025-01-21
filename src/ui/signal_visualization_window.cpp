#include "signal_visualization_window.h"
#include "imgui.h"
#include "implot.h"
#include <cmath>
#include <complex>
#include <vector>

namespace UI {

// Utility Functions

std::vector<float> ParsePolynomial(const char *input) {
  std::vector<float> coefficients;
  std::stringstream ss(input);
  std::string token;
  while (std::getline(ss, token, ',')) {
    coefficients.push_back(std::stof(token));
  }
  return coefficients;
}

std::vector<float> ImpulseResponse(const std::vector<float> &numerator,
                                   const std::vector<float> &denominator,
                                   int samples) {
  std::vector<float> impulseResponse(samples, 0.0f);
  impulseResponse[0] = 1.0f; // Impulse at t=0
  for (int n = 1; n < samples; ++n) {
    float response = 0.0f;
    for (size_t i = 0; i < numerator.size() && n >= static_cast<int>(i); ++i) {
      response += numerator[i] * impulseResponse[n - i];
    }
    for (size_t i = 1; i < denominator.size() && n >= static_cast<int>(i);
         ++i) {
      response -= denominator[i] * impulseResponse[n - i];
    }
    response /= denominator[0];
    impulseResponse[n] = response;
  }
  return impulseResponse;
}

std::vector<std::complex<float>> ComputeFFT(const std::vector<float> &signal) {
  // Implement FFT (use external library like FFTW or write your own)
  std::vector<std::complex<float>> fft(signal.size() / 2);
  return fft; // Placeholder
}

std::vector<std::complex<float>>
ComputeTransferFunctionFFT(const std::vector<float> &numerator,
                           const std::vector<float> &denominator, int samples) {
  // Compute H(f) = FFT of impulse response
  std::vector<std::complex<float>> fft(samples / 2);
  return fft; // Placeholder
}

std::vector<float>
Magnitude(const std::vector<std::complex<float>> &complexSignal) {
  std::vector<float> magnitude(complexSignal.size());
  for (size_t i = 0; i < complexSignal.size(); ++i) {
    magnitude[i] = std::abs(complexSignal[i]);
  }
  return magnitude;
}

std::vector<float> FrequencyAxis(int samples) {
  std::vector<float> freqs(samples / 2);
  for (int i = 0; i < samples / 2; ++i) {
    freqs[i] = i / (float)samples; // Normalized frequency
  }
  return freqs;
}

std::vector<float> Convolve(const std::vector<float> &signal,
                            const std::vector<float> &impulseResponse) {
  int signalSize = signal.size();
  int responseSize = impulseResponse.size();
  std::vector<float> output(signalSize + responseSize - 1, 0.0f);

  for (int n = 0; n < static_cast<int>(output.size()); ++n) {
    for (int k = 0; k < responseSize; ++k) {
      if (n - k >= 0 && n - k < signalSize) {
        output[n] += signal[n - k] * impulseResponse[k];
      }
    }
  }
  return std::vector<float>(output.begin(),
                            output.begin() +
                                signalSize); // Truncate to input signal length
}

void SignalVisualizationWindow::Show(bool *open) {
  if (*open) {
    ImGui::Begin("Signal Visualization", open);

    // Parameters for signal generation
    static float amplitude1 = 1.0f, frequency1 = 1.0f, phase1 = 0.0f;
    static float amplitude2 = 0.5f, frequency2 = 2.0f, phase2 = 0.5f;
    static int samples = 500;

    // Transfer function editor
    static int impulseSamples = 50;
    static std::vector<float> impulseResponse(impulseSamples, 0.0f);
    static bool drawingMode = false;

    ImGui::Text("Signal 1 Parameters");
    ImGui::SliderFloat("Amplitude 1", &amplitude1, 0.1f, 10.0f);
    ImGui::SliderFloat("Frequency 1 (Hz)", &frequency1, 0.1f, 10.0f);
    ImGui::SliderFloat("Phase 1 (radians)", &phase1, -3.14f, 3.14f);

    ImGui::Separator();
    ImGui::Text("Signal 2 Parameters");
    ImGui::SliderFloat("Amplitude 2", &amplitude2, 0.1f, 10.0f);
    ImGui::SliderFloat("Frequency 2 (Hz)", &frequency2, 0.1f, 10.0f);
    ImGui::SliderFloat("Phase 2 (radians)", &phase2, -3.14f, 3.14f);

    ImGui::Separator();
    ImGui::SliderInt("Samples", &samples, 10, 1000);

    // Generate signals
    std::vector<float> time(samples);
    std::vector<float> signal1(samples);
    std::vector<float> signal2(samples);
    std::vector<float> mixedSignal(samples);

    for (int i = 0; i < samples; ++i) {
      time[i] = i / (float)samples;
      signal1[i] =
          amplitude1 * std::sin(2 * M_PI * frequency1 * time[i] + phase1);
      signal2[i] =
          amplitude2 * std::sin(2 * M_PI * frequency2 * time[i] + phase2);
      mixedSignal[i] = signal1[i] + signal2[i];
    }

    // Plot individual signals
    if (ImPlot::BeginPlot("Input Signals")) {
      ImPlot::PlotLine("Signal 1", time.data(), signal1.data(), samples);
      ImPlot::PlotLine("Signal 2", time.data(), signal2.data(), samples);
      ImPlot::PlotLine("Mixed Signal", time.data(), mixedSignal.data(),
                       samples);
      ImPlot::EndPlot();
    }

    // Graphical transfer function editor
    ImGui::Separator();
    ImGui::Text("Define Transfer Function (Impulse Response)");

    if (ImPlot::BeginPlot("Impulse Response Editor", ImVec2(-1, 150))) {
      ImPlot::SetupAxes("Samples", "Amplitude", ImPlotAxisFlags_AutoFit,
                        ImPlotAxisFlags_AutoFit);

      if (ImPlot::IsPlotHovered() && ImGui::IsMouseDown(0)) {
        drawingMode = true;
      } else if (drawingMode && ImGui::IsMouseReleased(0)) {
        drawingMode = false;
      }

      if (drawingMode) {
        ImPlotPoint mousePos = ImPlot::GetPlotMousePos();
        int idx = static_cast<int>(std::round(mousePos.x));
        if (idx >= 0 && idx < impulseSamples) {
          impulseResponse[idx] = static_cast<float>(mousePos.y);
        }
      }

      ImPlot::PlotLine("Impulse Response", impulseResponse.data(),
                       impulseSamples);
      ImPlot::EndPlot();
    }

    // Convolve mixed signal with custom impulse response
    std::vector<float> outputSignal = Convolve(mixedSignal, impulseResponse);

    // Plot output signal
    if (ImPlot::BeginPlot("Output Signal")) {
      ImPlot::PlotLine("Output Signal", time.data(), outputSignal.data(),
                       samples);
      ImPlot::EndPlot();
    }

    ImGui::End();
  }
}

} // namespace UI
