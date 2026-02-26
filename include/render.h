//
// Created by ualace on 11/02/2023.
//
#ifndef SPECTROGRAPH_RENDER_H
#define SPECTROGRAPH_RENDER_H

#include "../lib/SSD1306/lib/ssd1306.h"

#define FRAME_X0 1
#define FRAME_XF (MAX_X - 8)
#define FRAME_Y0 16
#define FRAME_YF (MAX_Y - 14)

#define GRAPH_X0 (FRAME_X0 + 3)
#define GRAPH_XF (FRAME_XF - 3)
#define GRAPH_Y0 (FRAME_Y0 + 3)
#define GRAPH_YF (FRAME_YF - 3)

#define X_AXIS_QUANTITY 5
#define DOTTED_QUANTITY 9 // 2 * x axis points quantity - 1

void init_render_data(const double * x, uint8_t size);
void draw_frame(const double * x, uint8_t size);
void draw_graph(const double * y, const double * x, uint8_t max, uint8_t size);
static void draw_triangle(uint8_t x, uint8_t y);

#endif //SPECTROGRAPH_RENDER_H
