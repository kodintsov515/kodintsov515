#pragma once

class Atom {
public:
    Atom();
    Atom(const double x, const double y, const double z, const int q);
    int getQ() const noexcept;
    double getX() const noexcept;
    double getY() const noexcept;
    double getZ() const noexcept;
    bool operator<(const Atom b) const;
    double x_{0}, y_{0}, z_{0};
    int q_{0};
    Atom* calculate_P(const Atom* B, double* a, double* b) const;
};
