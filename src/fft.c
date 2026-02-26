//
// Created by ualace on 11/02/2023.
//
#include <math.h>
#include "fft.h"

static void fft_radix2(const double * input, s_complex * output, uint8_t size, uint8_t div) {
    s_complex t, e, mul;

    if (size == 1) {
        output[0].real = input[0];
        output[0].imag = 0.0;
        return;
    }

    fft_radix2(input, output, size / 2, 2 * div);
    fft_radix2(input + div, output + size / 2, size / 2, 2 * div);

    for (uint8_t k = 0; k < size / 2; k++) {
        t = output[k];

        e.real = cos(-2 * M_PI * k / size);
        e.imag = sin(-2 * M_PI * k / size);

        mul.real = (e.real * output[k + size / 2].real) - (e.imag * output[k + size / 2].imag);
        mul.imag = (e.real * output[k + size / 2].imag) + (e.imag * output[k + size / 2].real);

        output[k].real += mul.real;
        output[k].imag += mul.imag;

        output[k + size / 2].real = t.real - mul.real;
        output[k + size / 2].imag = t.imag - mul.imag;
    }
}

void fft(const double * input, s_complex * output, uint8_t size) {
    fft_radix2(input, output, size, 1);
}

uint8_t fft_magnitude(const s_complex * input, double * mag, uint8_t size) {
    // As the signal is always positive, let's not consider 0 Hz as a valid peak frequency
	uint8_t max_i = 1;

    for (uint8_t i = 0; i < size; i++) {
        mag[i] = sqrt(input[i].real * input[i].real + input[i].imag * input[i].imag);

        if(i == 0 || i == 1) {
            continue;
        }

        if (mag[i] > mag[max_i]) {
            max_i = i;
        }
    }

    return max_i;
}

uint8_t fft_magnitude_log(const s_complex * input, double * mag, uint8_t size) {
	// As the signal is always positive, let's not consider 0 Hz as a valid peak frequency
    uint8_t max_i = 1;

    for (uint8_t i = 0; i < size; i++) {
        mag[i] = log10(input[i].real * input[i].real + input[i].imag * input[i].imag);

        if(i == 0 || i == 1) {
            continue;
        }

        if (mag[i] > mag[max_i]) {
            max_i = i;
        }
    }

    return max_i;
}

void apply_window(double * input, const double * window, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        input[i] *= window[i];
    }
}
