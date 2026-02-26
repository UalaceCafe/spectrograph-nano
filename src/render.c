//
// Created by ualace on 11/02/2023.
//
#include <stdio.h>
#include "util.h"
#include "render.h"

static struct {
    double xs[X_AXIS_QUANTITY];
    double x_dotted[DOTTED_QUANTITY];
    char buffer[5];
} render;

void init_render_data(const double * x, uint8_t size) {
    linspace(render.xs, x[0], x[size - 1], X_AXIS_QUANTITY);
    linspace(render.x_dotted, x[0], x[size - 1], DOTTED_QUANTITY);
}

void draw_frame(const double * x, uint8_t size) {
    SSD1306_ClearScreen();

    SSD1306_DrawLine(FRAME_X0, FRAME_XF, FRAME_Y0, FRAME_Y0);
    SSD1306_DrawLine(FRAME_X0, FRAME_XF, FRAME_YF, FRAME_YF);
    SSD1306_DrawLine(FRAME_X0, FRAME_X0, FRAME_Y0, FRAME_YF);
    SSD1306_DrawLine(FRAME_XF, FRAME_XF, FRAME_Y0, FRAME_YF);

    for(uint8_t i = 0; i < DOTTED_QUANTITY; i++) {
        uint8_t x_pos = map(render.x_dotted[i], x[0], x[size - 1], GRAPH_X0, GRAPH_XF);
        for(uint8_t j = 0; j < 10; j++) {
            uint8_t y_pos = map(j, 0, 9, FRAME_Y0, FRAME_YF);
            SSD1306_DrawPixel(x_pos, y_pos);
        }
    }

    for(uint8_t i = 0; i < X_AXIS_QUANTITY; i++) {
        uint8_t x_pos = map(render.xs[i], x[0], x[size - 1], GRAPH_X0, GRAPH_XF);
        SSD1306_DrawLine(x_pos, x_pos, FRAME_YF - 2, FRAME_YF + 2);

        if(render.xs[i] == 0.0) {
            snprintf(render.buffer, 5, "0.0");
        } else if(render.xs[i] < 1000.0) {
            snprintf(render.buffer, 5, "%.1fk", render.xs[i] / 1000);
        } else {
            snprintf(render.buffer, 5, "%uk", (uint16_t)(render.xs[i] / 1000));
        }
        SSD1306_SetPosition(x_pos - 1, 7);
        SSD1306_DrawString(render.buffer);
    }
}

void draw_graph(const double * y, const double * x, uint8_t max, uint8_t size) {
    double y_max = array_max(y, size);
    double y_min = array_min(y, size);

    for(uint8_t i = 0; i < size - 1; i++) {
        SSD1306_DrawLine(map(x[i], x[0], x[size - 1], GRAPH_X0, GRAPH_XF),
                         map(x[i + 1], x[0], x[size - 1], GRAPH_X0, GRAPH_XF),
                         map(y[i], y_min, y_max, GRAPH_YF, GRAPH_Y0),
                         map(y[i + 1], y_min, y_max, GRAPH_YF, GRAPH_Y0));
    }

    draw_triangle(map(max, 0, size - 1, GRAPH_X0, GRAPH_XF),
                  map(y[max], y_min, y_max, GRAPH_YF, GRAPH_Y0) - 2);
}

static void draw_triangle(uint8_t x, uint8_t y) {
    SSD1306_DrawLine(x, x, y, y - 3);
    SSD1306_DrawLine(x - 1, x - 1, y - 1, y - 3);
    SSD1306_DrawLine(x - 2, x - 2, y - 2, y - 3);
    SSD1306_DrawLine(x + 1, x + 1, y - 1, y - 3);
    SSD1306_DrawLine(x + 2, x + 2, y - 2, y - 3);
}
