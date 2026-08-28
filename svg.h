#pragma once
#include <iostream>
#include <vector>
#include <string>

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, std::string text);
void svg_rect(double x, double y, double width, double height, std::string stroke, std::string fill);
void svg_stroke_horizontal(double baseline, const double IMAGE_WIDTH);
void svg_stroke_vertical(double left, const double IMAGE_HEIGHT);
void show_histogram_svg(const std::vector<size_t>& bins);
