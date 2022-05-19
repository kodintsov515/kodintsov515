#include "Matrix.h"

namespace {

int factorial(const int& n) {
    if (n == 0) { return 1; }
    return n * factorial(n - 1);
}

}  // namespace

Matrix::Matrix(std::size_t m, std::size_t n) : m_(m), n_(n) {
    content_.resize(m * n);
}

Matrix::Indices Matrix::Dimensions() const { return {m_, n_}; }

Matrix Matrix::Minor(const Matrix::Indices& ij) const {
    assert(m_ == n_);
    assert(ij.first < m_ && ij.second < n_);

    Matrix tmp(m_ - 1, n_ - 1);
    std::size_t i = 0;
    std::size_t q = 0;
    while (i < content_.size()) {
        if ((i / n_ == ij.first) || (i % n_ == ij.second)) {
            i++;
        } else {
            tmp.content_[q] = content_[i];
            i++;
            q++;
        }
    }
    return tmp;
}

double Matrix::Trace() const {
    double tmp = 0;
    for (std::size_t i = 0; i < m_; i++) { tmp += content_[i * (1 + n_)]; }
    return tmp;
}

double Matrix::Determinant() const {
    double tmp = 0;
    if ((m_ == 1) && (n_ == 1)) {
        return content_[0];
    } else {
        for (std::size_t i = 0; i < n_; i++) {
            tmp += std::pow(double(-1), i) * content_[i] *
                   (this->Minor({0, i})).Determinant();
        }
    }
    return tmp;
}

/*
Matrix Matrix::Exp() const {
    constexpr double epsilon = 0.01;
    Matrix tmp(m_, n_);
    tmp = pow(0);
    std::size_t i = 1;
    while (true) {
        Matrix delta(m_, n_);
        delta = pow(i) * (1.0 / factorial(i));
        if (delta.abs() < epsilon) {
            break;
        } else {
            tmp += delta;
            i++;
        }
    }
    return tmp;
}*/

double& Matrix::operator[](const Matrix::Indices& ij) {
    assert(ij.first < m_ && ij.second < n_);
    return content_[ij.first * m_ + ij.second];
}

double Matrix::operator[](const Matrix::Indices& ij) const {
    assert(ij.first < m_ && ij.second < n_);
    return content_[ij.first * m_ + ij.second];
}

Matrix Matrix::operator+(const Matrix& right) const {
    assert(m_ == right.m_ && n_ == right.n_);

    Matrix tmp(m_, n_);
    for (std::size_t i = 0; i < m_ * n_; i++) {
        tmp.content_[i] = content_[i] + right.content_[i];
    }
    return tmp;
}
Matrix& Matrix::operator+=(const Matrix& right) {
    assert(m_ == right.m_ && n_ == right.n_);

    for (std::size_t i = 0; i < content_.size(); i++) {
        content_[i] += right.content_[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(double k) {
    for (std::size_t i = 0; i < content_.size(); i++) { content_[i] *= k; }
    return *this;
}

Matrix Matrix::operator*(double k) const {
    Matrix tmp(m_, n_);
    for (std::size_t i = 0; i < content_.size(); i++) {
        tmp.content_[i] = content_[i] * k;
    }
    return tmp;
}

Matrix Matrix::operator*(const Matrix& right) const {
    assert(n_ == right.m_);

    Matrix tmp(m_, right.n_);
    for (std::size_t i = 0; i < tmp.m_; i++) {
        for (std::size_t k = 0; k < tmp.n_; k++) {
            for (std::size_t q = 0; q < n_; q++) {
                tmp[{i, k}] += (*this)[{i, q}] * right[{q, k}];
            }
        }
    }
    return tmp;
}
/*
Matrix Matrix::pow(int power) const {
    assert(power >= 0);

    Matrix tmp(m_, n_);
    for (std::size_t i = 0; i < tmp.m_; i++) {
        tmp.content_[i * (1 + tmp.n_)] = 1;
    }
    if (power == 0) {
        return tmp;
    } else {
        for (std::size_t i = 0; i < power; i++) { tmp *= (*this); }
    }
    return tmp;
}*/

bool Matrix::operator<(double epsilon) const {
    bool status = true;
    for (std::size_t i = 0; i < content_.size(); i++) {
        status = status && (content_[i] < epsilon);
    }
    return status;
}

Matrix Matrix::abs() const {
    Matrix tmp(m_, n_);
    for (std::size_t i = 0; i < content_.size(); i++) {
        tmp.content_[i] = std::abs(content_[i]);
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (std::size_t i = 0; i < matrix.content_.size(); i++) {
        if (i % matrix.n_ == (matrix.n_ - 1)) {
            out << matrix.content_[i] << std::endl;
        } else {
            out << matrix.content_[i] << " ";
        }
    }
    return out;
}
