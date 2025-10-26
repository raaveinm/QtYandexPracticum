#pragma once
#include <cstdint>
#include <vector>
#include <cmath>
#include <numbers>
#include <cassert>

enum class SignalType {
    kSin,
    kCos,
    kMeander
};

struct SignalData {
    SignalType signal_type; // Тип сигнала.
    int samples;            // Длина сигнала.
    int wave_length;        // Длина волны.
    int16_t amplitude;      // Максимальное значение.
    double cycle;           // Скважность меандра.
};


inline void ReplicateSignal(std::vector<int16_t>& signal, size_t desired_length) {
    assert(!signal.empty());

    const std::vector<int16_t> original_period = signal;
    const size_t wave_length = original_period.size();

    while (signal.size() < desired_length) {
        size_t max_insert = desired_length - signal.size();
        const size_t to_insert = std::min(wave_length, max_insert);
        std::copy_n(original_period.begin(), to_insert, std::back_inserter(signal));
    }
}

inline std::vector<int16_t> GenerateSignal(const SignalData &data) {
    std::vector<int16_t> signal;

    switch (data.signal_type) {
        case SignalType::kCos:
            for (int i = 0; i < data.wave_length; ++i) {
                const double amplitude = data.amplitude * cos(i * 2 * std::numbers::pi / data.wave_length);
                signal.push_back(static_cast<int16_t>(amplitude));
            }
            break;

        case SignalType::kSin:
            for (int i = 0; i < data.wave_length; ++i) {
                const double amplitude = data.amplitude * sin(i * 2 * std::numbers::pi / data.wave_length);
                signal.push_back(static_cast<int16_t>(amplitude));
            }
            break;

        case SignalType::kMeander:
            const int positive_samples = static_cast<int>(data.cycle * data.wave_length);
            const int negative_samples = data.wave_length - positive_samples;

            std::fill_n(std::back_inserter(signal), positive_samples, data.amplitude);
            std::fill_n(std::back_inserter(signal), negative_samples, -data.amplitude);

            break;
    }

    ReplicateSignal(signal, data.samples);
    return signal;
}

inline void ApplyDecayAndAttack(std::vector<int16_t>& signal,
                                size_t max_length) {

    size_t decay_length = std::min(signal.size(), max_length);
    size_t attack_length = decay_length;

    auto decay_transformer = [=, i = decay_length](const int16_t source) mutable {
        const double factor = static_cast<double>(i--) / static_cast<double>(decay_length);
        return static_cast<int16_t>(source * factor);
    };

    std::transform(
        signal.end() - decay_length,
        signal.end(),
        signal.end() - decay_length, decay_transformer
        );

    auto attack_transformer = [=, i = 0](int16_t source) mutable {
        const double factor = static_cast<double>(i++) / static_cast<double>(attack_length);
        return static_cast<int16_t>(source * factor);
    };
    std::transform(
        signal.begin(),
        signal.begin() + attack_length,
        signal.begin(), attack_transformer
        );
}