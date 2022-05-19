#pragma once

#include <string>
#include <vector>
#include <map>
#include "Atom.h"
#include "BasisLib.h"
using std::vector, std::map;
//using BSonMol = map<vector<Atom>, vector<vector<radial_t>>>;
using BSonAtom = map<int, vector<vector<radial_t>>>;

class Molecule : public BasisLib {
public:
    void loadFromXyz(const std::string filename);
    static int getQ(const std::string name) noexcept;
    void addAtom(const Atom& atom) noexcept;
    void printInfo(std::ostream& out) const noexcept;
    void AddBasisToMol();
    
protected:
    map<Atom,BSonAtom> molecule_with_BS{};
    vector<Atom> atoms{};

private:
    static inline std::map<const std::string, int> dict = {
        {"H", 1},         {"HYDROGEN", 1}, {"O", 8},      {"OXYGEN", 8},
        {"N", 7},         {"HYDROGEN", 1}, {"HELIUM", 2}, {"LITHIUM", 3},
        {"BERYLLIUM", 4}, {"BORON", 5},    {"CARBON", 6}, {"NITROGEN", 7},
        {"OXYGEN", 8},    {"FLUORINE", 9}, {"NEON", 10}};
};
