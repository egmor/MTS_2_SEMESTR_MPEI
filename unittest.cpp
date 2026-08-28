#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "histogram_internal.h"

TEST_CASE("distinct positive numbers") {
    double min = 0;
    double max = 0;
    bool TEST = find_minmax({1, 2}, min, max);
    CHECK(TEST);
    CHECK(min == 1);
    CHECK(max == 2);
}

TEST_CASE("many values") {
    double min = 0;
    double max = 0;
    bool TEST = find_minmax({1, 2, 99, 17, 0, -1, 95, 1934, -999, 3, 4}, min, max);
    CHECK(TEST);
    CHECK(min == -999);
    CHECK(max == 1934);
}

TEST_CASE("one element") {
    double min = 0;
    double max = 0;
    bool TEST = find_minmax({1}, min, max);
    CHECK(TEST);
    CHECK(min == 1);
    CHECK(max == 1);
}

TEST_CASE("distinct negative numbers") {
    double min = 0;
    double max = 0;
    bool TEST = find_minmax({-19, -99}, min, max);
    CHECK(TEST);
    CHECK(min == -99);
    CHECK(max == -19);
}

TEST_CASE("same numbers") {
    double min = 0;
    double max = 0;
    bool TEST = find_minmax({77, 77}, min, max);
    CHECK(TEST);
    CHECK(min == 77);
    CHECK(max == 77);
}

TEST_CASE("void vector") {
    double min = 0;
    double max = 0;
    bool TEST = find_minmax({}, min, max);
    CHECK(!TEST);
    CHECK(min == 0);
    CHECK(max == 0);
}