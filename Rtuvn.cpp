#include "Rtuvn.h"

Rtuvn::Rtuvn(std::size_t nMax, double Xpc, double Ypc, double Zpc, double p)
    : nMax_(nMax),
      Rtuvn_((nMax + 1) * (nMax + 1) * (nMax + 1) * (nMax + 1), 0.),
      Xpc_(Xpc),
      Ypc_(Ypc),
      Zpc_(Zpc),
      p_(p) {
    fillNAxis();  // Fills R000n

    fillPlane_t();
    for (std::size_t t = 0; t <= nMax_; t++) {
        fillPlane_tu(t);
        for (std::size_t u = 0; u <= nMax_; u++) { fillPlane_tuv(t, u); }
    }
}

void Rtuvn::fillPlane_tu(std::size_t t) {
    for (std::size_t n = 0; n < nMax_ - t - 1; n++) {
        At(t, 1, 0, n) = Ypc_ * At(t, 0, 0, n + 1);
    }
    for (std::size_t u = 1; u < nMax_; u++) {
        for (std::size_t n = 0; n < nMax_ - t - (u + 1); n++) {
            At(t, u + 1, 0, n) =
                u * At(t, u - 1, 0, n + 1) + Ypc_ * At(t, u, 0, n + 1);
        }
    }
}
