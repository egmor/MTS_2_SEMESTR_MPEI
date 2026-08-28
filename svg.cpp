#include "svg.h"

void
svg_begin(double width, double height) {
    std::cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    std::cout << "<svg ";
    std::cout << "width='" << width << "' ";
    std::cout << "height='" << height << "' ";
    std::cout << "viewBox='0 0 " << width << " " << height << "' ";
    std::cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    std::cout << "</svg>\n";
}

void
svg_text(double left, double baseline, std::string text) {
    std::cout << "<text x='" << left 
              << "' y='" << baseline 
              << "'>" << text 
              << "</text>";
}

void 
svg_rect(double left, double baseline, double width, double height, std::string stroke = "#000000", std::string fill = "#000000") {
    std::cout << "<rect x='" << left
              << "' y='" << baseline 
              << "' width='" << width 
              << "' height='" << height 
              << "' stroke='" << stroke
              << "' fill='" << fill << "' />\n";
}

void 
svg_stroke_horizontal(double baseline, const double IMAGE_WIDTH) {
    std::cout << "<line x1='0' y1='" << baseline
              << "' x2='" << IMAGE_WIDTH
              << "' y2='" << baseline 
              << "' stroke='black' stroke-width='2' stroke-dasharray = '10 10'/>\n";
}

void 
svg_stroke_vertical(double left, const double IMAGE_HEIGHT) {
    std::cout << "<line x1='" << left 
              << "' y1='0' x2='" << left
              << "' y2='" << IMAGE_HEIGHT
              << "' stroke='black' stroke-width='2' stroke-dasharray = '10 10'/>\n";
}

void
show_histogram_svg(const std::vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto AVAILABLE_WIDTH = IMAGE_WIDTH - TEXT_WIDTH;
    
    size_t max_bin = bins[0];
    for (size_t bin : bins) {if (bin > max_bin) {max_bin = bin;}}

    
    double scaling_factor = 1.0;
    
    if (max_bin > 0) {scaling_factor = static_cast<double>(AVAILABLE_WIDTH) / max_bin;}

    std::vector<std::string> strokes = {"#01188d", "#860000", "#007627", "#888a00", "#982e00", "#9c0070", "#5f009b"};
    std::vector<std::string> fills = {"#0021c7", "#c70000", "#00c742", "#e4e800", "#e84600", "#e800a6", "#8f00e8"};

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    size_t color_index = 0;

    for (size_t bin : bins) {
        const double bin_width = bin * scaling_factor;
        if (color_index >= 7) {color_index = 0;}
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, std::to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, strokes[color_index], fills[color_index]);
        svg_stroke_horizontal(top, IMAGE_WIDTH);
        color_index++;
        top += BIN_HEIGHT;
    }
    svg_stroke_horizontal(top, IMAGE_WIDTH);
    svg_stroke_vertical(0, top);
    svg_stroke_vertical(IMAGE_WIDTH, top);
    svg_end();
}

