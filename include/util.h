//
// Created by ualace on 07/02/2023.
//
#ifndef SPECTROGRAPH_UTIL_H
#define SPECTROGRAPH_UTIL_H

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define TWO_PI (2 * M_PI)

double array_max(const double * array, uint8_t size);
double array_min(const double * array, uint8_t size);
double array_mean(const double * array, uint8_t size);
uint8_t array_index(double value, const double * array, uint8_t size);
uint8_t map(double x, double a1, double a2, uint8_t b1, uint8_t b2);
void linspace(double * output, double start, double end, uint8_t size);
void hamming_window(double * output, uint8_t size, double alpha);

#endif //SPECTROGRAPH_UTIL_H
