//
// Created by ualace on 11/02/2023.
//
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"

void ADC_init(void) {
    ADMUX = 0b01000000; // 01: Uses AVCC (5V), 0: 2bits-8bits result, 0: not used, 0000: ADC0 (pin A0)
    DIDR0 = 0b11111110; // 0: only ADC0 enabled
    ADCSRA = 0b10000111; // 1: enable ADC, 0: start conversion, 0: auto-trigger, 0: conversion finished, 0: enable interrupt, 111: 128 pre-scaler
    ADCSRB = 0x00; // Free running mode
}

uint16_t ADC_measure(void) {
    uint16_t output;
    ADCSRA |= 0x40;
    while((ADCSRA & 0x10) != 0x10);
    output = ADC;
    ADCSRA |= 0x10;

    return output;
}
