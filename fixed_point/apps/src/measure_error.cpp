#include "../include/measure_error.hpp"

int main() {
    // Steps are limited to 5000000 for saving processing time
    measureCordicError<16, 16, 32>(5000000);
    // Useful linear data is fractional:
    measureCordicError<2, 30, 32>(5000000);
    // Reduce linear resolution to the limit of having error to the order of 0.001:
    measureCordicError<2, 12, 32>(5000000);
    // Reduce angular resolution to the limit of having error to the order of 0.001:
    measureCordicError<2, 30, 14>();
    // After playing around with values, these compromises seem to be accpetable:
    measureCordicError<2, 13, 15>();
    measureCordicError<2, 14, 14>();
    return 0;
}
