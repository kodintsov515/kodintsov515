#pragma once          //                    Dij  Coulomb2e  Fn(x)
#include "Matrix.h"   //                       \   /  \    /
#include "Molecule.h" //           xij<--eijt<--Eijt  Rtuvn -->rtubn
#include <string>     //                       /   \   /  
#include <vector>     //              Tij-->Sij   Coulomb1e
#include <map>
using std::vector;
using std::pair;
//using eijt = vector<vector<vector<double>>>;

class index
{
public:
    size_t i,j,t;
};

class eijt
{
public:
    vector<vector<vector<double>>> e;
};

class Eijt : public Molecule
{
private:
    double A_, B_, P_;
    size_t BasisSize_;
protected:
    Eijt(size_t BasisSize) {BasisSize_=BasisSize;}; 
    double calculate_next_element(const Atom* P, const Atom* A, double* a, double* b, double* lower, const index low_i, double* upper, const index up_i,
double* middle, const index mid_i, char direction) ;
    double calculate_zero_element(const Atom* A, const Atom* B, double* a, double* b, char direction);
    eijt E;
public:
    Eijt() {};
    void calculate(const Atom* A, const Atom* B, char direction, int shell, int subshell, int orbital, size_t i_max, size_t j_max);
    
};

class Sij : public Eijt
{
protected:
    
public:
    void calculate(Matrix S, size_t nBF);
};

class Tij : public Sij, public Matrix
{
protected:
    Matrix T;
public:
    void calculate();
};

class Dij : public Eijt
{
protected:
    Matrix D;
public:
    void calculate();
};

class AOIntegrals : public Tij, public Dij
{
public:
    AOIntegrals(const Molecule& mol);
    AOIntegrals(const std::string& filename);
    void saveToFile(const std::string& filename) const;

private:
    Matrix S, V, Te;
};