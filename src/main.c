#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "util.h"
#include "fft.h"
#include "adc.h"
#include "render.h"

#define NO_OF_SAMPLES 32
#define SAMPLING_FREQUENCY 2.5e3
#define ADC_DELAY_US (((1 / SAMPLING_FREQUENCY) - (1 / (16e6 / (128 * 13)))) * 1e6)
#define FREQUENCY_RESOLUTION (SAMPLING_FREQUENCY / NO_OF_SAMPLES)

#define WINDOW_ALPHA 0.5434782608695652

#define BUFFER_SIZE 30

struct {
    double * signal;
    double mean;
    double * frequencies;
    uint8_t peak_bin;
    double * window;
    s_complex * fft;
    double * magnitude;
} data;

static uint8_t log_mode = 0;
static uint8_t use_window = 0;

void init_data(void);
void capture_and_analyse_signal(void);

ISR(INT0_vect) {
    log_mode = !log_mode;
}

ISR(INT1_vect) {
    use_window = !use_window;
}

int main(void) {
    char buffer[BUFFER_SIZE];

    DDRD = 0x00;
    EICRA = 0b00001111;
    EIMSK = 0b00000011;
    sei();

    init_data();
    ADC_init();
    SSD1306_Init(SSD1306_ADDR);
    init_render_data(data.frequencies, NO_OF_SAMPLES / 2);

    // Discard first measurement to stabilize ADC
    ADC_measure();

    while(1) {
        capture_and_analyse_signal();

        draw_frame(data.frequencies, NO_OF_SAMPLES / 2);
        draw_graph(data.magnitude, data.frequencies, data.peak_bin, NO_OF_SAMPLES / 2);

        snprintf(buffer, BUFFER_SIZE, "Mode: %s", log_mode == 0 ? "Mag." : "Log.");
        SSD1306_SetPosition(FRAME_X0, 0);
        SSD1306_DrawString(buffer);

        snprintf(buffer, BUFFER_SIZE, "Peak: %.1f Hz", data.frequencies[data.peak_bin]);
        SSD1306_SetPosition(FRAME_X0, 1);
        SSD1306_DrawString(buffer);

        if(use_window) {
            snprintf(buffer, BUFFER_SIZE, "Window");
            SSD1306_SetPosition(MAX_X - 46, 0);
            SSD1306_DrawString(buffer);
        }

        SSD1306_UpdateScreen(SSD1306_ADDR);
    }
}

void init_data(void) {
    data.signal = malloc(NO_OF_SAMPLES * sizeof(double));

    data.frequencies = malloc((NO_OF_SAMPLES / 2) * sizeof(double));
    for(uint8_t i = 0; i < NO_OF_SAMPLES / 2; i++) {
        data.frequencies[i] = i * FREQUENCY_RESOLUTION;
    }

    data.window = malloc(NO_OF_SAMPLES * sizeof(double));
    hamming_window(data.window, NO_OF_SAMPLES, WINDOW_ALPHA);

    data.fft = malloc(NO_OF_SAMPLES * sizeof(s_complex));
    data.magnitude = malloc((NO_OF_SAMPLES / 2) * sizeof(double));
}

void capture_and_analyse_signal(void) {
    for (uint8_t i = 0; i < NO_OF_SAMPLES; i++) {
        // No need to convert the ADC value to a voltage since we are only interested in the frequencies.
        data.signal[i] = ADC_measure();
        _delay_us(ADC_DELAY_US);
    }

    if (use_window) {
        apply_window(data.signal, data.window, NO_OF_SAMPLES);
    }

    fft(data.signal, data.fft, NO_OF_SAMPLES);
    if (log_mode) {
        data.peak_bin = fft_magnitude_log(data.fft, data.magnitude, NO_OF_SAMPLES / 2);
    } else {
        data.peak_bin = fft_magnitude(data.fft, data.magnitude, NO_OF_SAMPLES / 2);
    }
}
