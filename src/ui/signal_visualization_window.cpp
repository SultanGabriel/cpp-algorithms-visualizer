#include "signal_visualization_window.h"
#include "../imgui.h"
#include <vector>
#include <cmath>

namespace UI {

void SignalVisualizationWindow::Show(bool* open) {
    if (*open) {
        ImGui::Begin("Signal Visualization", open);

        // Parameters for signal generation
        static float amplitude = 1.0f;
        static float frequency = 1.0f; // in Hz
        static float phase = 0.0f;     // in radians
        static int samples = 100;
        static bool showFourier = false;

        ImGui::SliderFloat("Amplitude", &amplitude, 0.1f, 10.0f);
        ImGui::SliderFloat("Frequency (Hz)", &frequency, 0.1f, 10.0f);
        ImGui::SliderFloat("Phase (radians)", &phase, -3.14f, 3.14f);
        ImGui::SliderInt("Samples", &samples, 10, 1000);
        ImGui::Checkbox("Show Fourier Transform", &showFourier);

        // Generate time domain signal
        std::vector<float> time(samples);
        std::vector<float> signal(samples);
        for (int i = 0; i < samples; ++i) {
            time[i] = i / (float)samples; // Normalized time
            signal[i] = amplitude * std::sin(2 * M_PI * frequency * time[i] + phase);
        }

        // Plot time-domain signal
        ImGui::PlotLines("Time Domain Signal", signal.data(), signal.size());

        if (showFourier) {
            // Compute Fourier transform (magnitude spectrum)
            std::vector<float> magnitude(samples / 2);
            for (int k = 0; k < samples / 2; ++k) {
                float real = 0.0f, imag = 0.0f;
                for (int n = 0; n < samples; ++n) {
                    real += signal[n] * std::cos(2 * M_PI * k * n / samples);
                    imag -= signal[n] * std::sin(2 * M_PI * k * n / samples);
                }
                magnitude[k] = std::sqrt(real * real + imag * imag) / samples;
            }
            ImGui::PlotLines("Fourier Magnitude Spectrum", magnitude.data(), magnitude.size());
        }

        ImGui::End();
    }
}
} // namespace UI

