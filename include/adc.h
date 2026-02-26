//
// Created by ualace on 11/02/2023.
//
#ifndef SPECTROGRAPH_NANO_ADC_H
#define SPECTROGRAPH_NANO_ADC_H

#include <stdint.h>

void ADC_init(void);
uint16_t ADC_measure(void);

#endif //SPECTROGRAPH_NANO_ADC_H
