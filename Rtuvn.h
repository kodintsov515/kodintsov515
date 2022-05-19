#pragma once

#include <cassert>
#include <vector>

class Rtuvn {
public:
    Rtuvn(std::size_t nMax, double Xpc, double Ypc, double Zpc, double p);

    double Rtuv0(std::size_t t, std::size_t u, std::size_t v) const {
        std::size_t index = Index(t, u, v, 0);
        assert(index < Rtuvn_.size());
        return Rtuvn_[index];
    }

private:
    std::size_t Index(std::size_t t, std::size_t u, std::size_t v,
                      std::size_t n) const {
        assert(n <= nMax_ && t <= nMax_ && u <= nMax_ && v <= nMax_);
        return n * (nMax_ + 1) * (nMax_ + 1) * (nMax_ + 1) +
               t * (nMax_ + 1) * (nMax_ + 1) + u * (nMax_ + 1) + v;
    }

    double& At(std::size_t t, std::size_t u, std::size_t v, std::size_t n) {
        std::size_t index = Index(t, u, v, n);
        assert(index < Rtuvn_.size());
        return Rtuvn_[index];
    }

    void fillNAxis(){};    // Fills R000{n=0..nMax_}
    void fillPlane_t(){};  // Fills R{t=0..nMax_}00{n=0..nMax_}, t + n <= nMax_
    void fillPlane_tu(
        std::size_t
            t);  // Fills R{t}{u=0..nMax_}0{n=0..nMax_}, t + u + n <= nMax_
    void fillPlane_tuv(
        std::size_t t,
        std::size_t
            u){};  // Fills R{t}{u}{v=0..nMax_}{n=0..nMax_}, t + u + v + n <= nMax_

private:
    std::size_t nMax_ = 0;
    std::vector<double> Rtuvn_;

    double Xpc_ = 0., Ypc_ = 0., Zpc_ = 0.;
    double p_ = 0.;
};
