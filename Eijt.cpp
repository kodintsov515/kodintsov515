#include "Eijt.h"
#include <cassert>
#include <cmath>

Eijt::Eijt(size_t i_max, size_t j_max, double xA, double xB, double alpha,
           double beta) {
    const auto size = (i_max + 1) * (j_max + 1) * (i_max + 1 * j_max);
    e_ = new double[size];
    const auto xP = (alpha * xA + beta * xB) / (alpha + beta);
    const auto xPA = xP - xA;

    for (size_t i = 0; i < size; i++) e_[i] = 0;
    e_[0] = exp(-alpha * beta / (alpha + beta) * (xA - xB) * (xA - xB));
    //    правильно заполнено все для i=j=0;
    for (size_t j = 0; j < j_max_; j++) {
        e_[(j + 1) * (i_max_ + 1)] =
            e_[j * (i_max_ + 1) + 1] + xPA * e_[j * (i_max_ + 1)];
        for (size_t t = 1; t < j + 2; t++) {
            //            e_[t + (j+1) * (i_max_ + 1)] =  ...;
        }
    }
    //    правильно заполнено все для i=0;
    for (size_t j = 0; j <= j_max_; j++)
        for (size_t i = 0; i < i_max; i++) {
            // здесь мы сначала заполняем E_j(i+1)0

            // а затем мы заполняем элементы от E_j(i+1)1 до E_j(i+1)(j+i+1(или +2)
        }
}

double Eijt::getEijt(size_t i, size_t j, size_t t) const {
    assert(i <= i_max_);
    assert(j <= j_max_);
    assert(t <= i_max_ + j_max_);
    return e_[t + j * (i_max_ + 1) + i * (i_max_ + 1) * (j_max_ + 1)];
}
