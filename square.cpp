#include <cmath>

double sqrt_d(const double a) {
    double b = sqrt(a);
    if (b != b)
        return -1.0;
    else
        return b;
}