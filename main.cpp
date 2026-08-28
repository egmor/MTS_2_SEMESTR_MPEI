#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "histogram.h"
#include "text.h"
#include "svg.h"
#include "C:/Users/miricia/Desktop/programms/labs_3n4/curl/include/curl/curl.h"

struct Input {
    std::vector<double> numbers;
    size_t bin_count{};
};

Input 
input_data(std::istream &in, bool prompt) {
    size_t num_count, bin_count;
    Input in_num;

    if (prompt) {std::cerr << "Enter value of numbers: ";}
    in >> num_count;

    in_num.numbers.resize(num_count);
    if (prompt) {std::cerr << "\nEnter numbers in vector: \n";}
    for (size_t i = 0; i < num_count; i++) {in >> in_num.numbers[i];}

    if (prompt) {std::cerr << "Enter value of bins: ";}
    in >> in_num.bin_count;

    return in_num;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    std::stringstream* buffer = reinterpret_cast<std::stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

Input
download(const std::string& address) {
    std::stringstream buffer;

    CURL* curl = curl_easy_init();
    if(curl) {
            CURLcode result;
            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Lab4");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            result = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (result != CURLE_OK) {
                std::cerr << "Error: " << curl_easy_strerror(result);
                exit(1);
            }
        }

    return input_data(buffer, false);
}

int 
main(int argc, char** argv) {
    Input input;
    curl_global_init(CURL_GLOBAL_ALL);
    if (argc > 1) {input = download(argv[1]);} 
    if (argc > 2) {
        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-bins") {
                if (i + 1 < argc) {
                    input.bin_count = std::stoul(argv[i + 1]);
                    i++;
                } 
                else {
                    std::cerr << "Error: Missing value for -bins option\n";
                    return 1;
                }
            }
        }
    }
    else {input = input_data(std::cin, true);}

    const auto bins = make_histogram(input.numbers, input.bin_count);
    show_histogram_svg(bins);
    return 0;
}