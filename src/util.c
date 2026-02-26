//
// Created by ualace on 07/02/2023.
//
#include "util.h"

double array_max(const double * array, uint8_t size) {
    double max = array[0];

    for(uint8_t i = 1; i < size; i++) {
        if(array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

double array_min(const double * array, uint8_t size) {
    double min = array[0];

    for(uint8_t i = 1; i < size; i++) {
        if(array[i] < min) {
            min = array[i];
        }
    }

    return min;
}

double array_mean(const double * array, uint8_t size) {
    double sum = 0.0;

    for(uint8_t i = 0; i < size; i++) {
        sum += array[i];
    }

    return sum / size;
}

double array_mean_abs(const double * array, uint8_t size) {
    double sum = 0.0;

    for(uint8_t i = 0; i < size; i++) {
        sum += fabs(array[i]);
    }

    return sum / size;
}

uint8_t array_index(double value, const double * array, uint8_t size) {
    for(uint8_t i = 0; i < size; i++) {
        if(array[i] == value) {
            return i;
        }
    }

    return 0;
}

uint8_t map(double x, double a1, double a2, uint8_t b1, uint8_t b2) {
    return (uint8_t)(b1 + (x - a1) * (b2 - b1) / (a2 - a1));
}

void linspace(double * output, double start, double end, uint8_t size) {
    double step = (end - start) / (size - 1);

    for(uint8_t i = 0; i < size; i++) {
        output[i] = start + step * i;
    }
}

void hamming_window(double * output, uint8_t size, double alpha) {
    double one_over_m_minus_1 = 1.0 / (size - 1);

    for(uint8_t i = 0; i < size; i++) {
        output[i] = alpha - (1.0 - alpha) * cos(TWO_PI * i * one_over_m_minus_1);
    }
}
