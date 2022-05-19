#include "Molecule.h"
#include <fstream>
#include <iostream>

void Molecule::loadFromXyz(std::string filename) {
    std::ifstream inp(filename.c_str());
    if (not inp) throw std::runtime_error("Problem with *.xyz file");
    std::string tStr{""};
    double x{0}, y{0}, z{0};
    int q{0};
    std::getline(inp, tStr);
    std::getline(inp, tStr);
    while (inp >> tStr >> x >> y >> z) {
        q = getQ(tStr);
        if (q > 0) {
            addAtom(Atom(x, y, z, q));
        } else {
            throw std::runtime_error("Unknown atom name " + tStr);
        }
    }
    inp.close();
#ifdef DEBUG_INFO
    printInfo(std::cout);
#endif
}

void Molecule::addAtom(const Atom& atom) noexcept { atoms.push_back(atom); }

int Molecule::getQ(const std::string name) noexcept {
    std::string upperName(name);
    for (auto& c : upperName) c = toupper(c);
    if (dict.find(upperName) == dict.end()) return -1;
    return dict[upperName];
}

void Molecule::printInfo(std::ostream& out) const noexcept {
    out << atoms.size() << " atoms were read.\n";
    int totalQ{0};
    for (const auto& a : atoms) totalQ += a.getQ();
    out << "Total nuclear charge is equal: " << totalQ << std::endl;
}

void Molecule::AddBasisToMol()
{
       molecule.emplace(atoms,content); 
}