//
// Created by ualace on 11/02/2023.
//
#ifndef SPECTROGRAPH_FFT_H
#define SPECTROGRAPH_FFT_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    double real;
    double imag;
} s_complex;

static void fft_radix2(const double * input, s_complex * output, uint8_t size, uint8_t div);
void fft(const double * input, s_complex * output, uint8_t size);
uint8_t fft_magnitude(const s_complex * input, double * mag, uint8_t size);
uint8_t fft_magnitude_log(const s_complex * input, double * mag, uint8_t size);
void apply_window(double * input, const double * window, uint8_t size);

#endif //SPECTROGRAPH_FFT_H
