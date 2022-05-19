#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

#include <cassert>

class Matrix {
public:
    using Indices = std::pair<std::size_t, std::size_t>;

public:
    Matrix(std::size_t m = 0, std::size_t n = 0);

    Indices Dimensions() const;
    double& operator[](const Indices& ij);
    double operator[](const Indices& ij) const;

    double Trace() const;
    Matrix Minor(const Indices& ij) const;
    double Determinant() const;

    //    Matrix Exp() const;
    //    Matrix pow(int power) const;

    Matrix operator+(const Matrix& right) const;
    Matrix& operator+=(const Matrix& right);

    Matrix operator*(const Matrix& right) const;
    //    Matrix& operator*=(const Matrix& right);
    Matrix operator*(double k) const;
    Matrix& operator*=(double k);

    Matrix abs() const;

    bool operator<(double epsilon) const;

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

private:
    std::size_t m_ = 0;
    std::size_t n_ = 0;
    std::vector<double> content_;
};
