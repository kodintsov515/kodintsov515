#include "Atom.h"

Atom::Atom(const double x, const double y, const double z, const int q)
    : x_(x), y_(y), z_(z), q_(q) {}

int Atom::getQ() const noexcept { return q_; }

double Atom::getX() const noexcept { return x_; }

double Atom::getY() const noexcept { return y_; }

double Atom::getZ() const noexcept { return z_; }

bool Atom::operator<(const Atom b) const
{
    Atom x=*this;
    Atom y=b;
    return x.q_<y.q_; 
}

Atom::Atom()
{
    this->q_=0;
    this->x_=this->y_=this->z_=0;
}

Atom* Atom::calculate_P(const Atom* B, double* a, double* b) const
{
     Atom* P;
    P->x_=((*a) * (this->x_) + (*b) * (B->x_) )/ (*a+*b) ;
    P->y_=((*a) * (this->y_) + (*b) * (B->y_) )/ (*a+*b) ;
    P->z_=((*a) * (this->z_) + (*b) * (B->z_) )/ (*a+*b);
    return P;
}
