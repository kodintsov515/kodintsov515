#include <iostream>
#include "Molecule.h"
#include "BasisLib.h"
#include "Parser.h"
#include "MolecularOrbitals.h"
#include "AOIntegrals.h"
#include "QCM.h"

void readData(const Parser &vars, Molecule &mol, BasisLib &basisLib) {
    mol.loadFromXyz(vars.getXyzFile());
    basisLib.loadFromGamessUS(vars.getBasisFile());
}

void preprocessing(const Parser &vars, Molecule &mol,
                   const BasisLib &basisLib) {}

void calcIntegrals(const Parser &vars) {}

void makeBasis(Molecule &mol, const BasisLib &basisLib) {}

int main(int argc, char *argv[]) {
    try {
        Parser vars(argc, argv);  // (1)
        Molecule mol;
        BasisLib basisLib;
        readData(vars, mol, basisLib);  // (2)
        makeBasis(mol, basisLib);       // (3)
        AOIntegrals aoints(mol);        // (4)
        MolecularOrbitals mo(mol);
        QCM::HCoreCalc(aoints, mol, mo);  // (5)
        QCM::UHF(vars, aoints, mol, mo);  // (6)
    } catch (std::exception &exception) {
        std::cerr << "ERROR: " << exception.what() << '\n';
        return 0;
    }
    return 0;
}
