#pragma once

// коэффициенты разложения произведения всех двух гауссов по эрмитовым полиномам
// со степеням от 0 до i_max и от 0 до j_max

#include <cstddef>

class Eijt {
public:
    Eijt(size_t i_max, size_t j_max, double xA, double xB, double alpha,
         double beta);
    Eijt(const Eijt&) = delete;
    Eijt& operator=(const Eijt&) = delete;
    double getEijt(size_t i, size_t j, size_t t) const;
    ~Eijt();

private:
    size_t i_max_{0}, j_max_{0};
    double* e_{nullptr};
};
