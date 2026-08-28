#include "text.h"

void
show_histogram_text(const std::vector<size_t> &bins, size_t &bin_count) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    double max_star = bins[0];
    for (size_t i = 1; i < bin_count; i++) {
        if (bins[i] > max_star) {max_star = bins[i];}
    }
    
    for (size_t i = 0; i < bin_count; i++) {
        if (bins[i] < 10) {std::cout << "  " << bins[i]; }
        else if (bins[i] < 100) {std::cout << " " <<  bins[i] ; }
        else {std::cout << bins[i];}
        std::cout << "| ";
        if (max_star > 76) {
            size_t height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_star);
            for (size_t j = 0; j < height; j++) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
        else {
            for (size_t j = 0; j < bins[i]; j++) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }

    return;
}