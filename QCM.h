#pragma once

#include "Molecule.h"
#include "Parser.h"
#include "MolecularOrbitals.h"
#include "AOIntegrals.h"

namespace QCM {
void HCoreCalc(const AOIntegrals &aoints, const Molecule &mol,
               MolecularOrbitals &mo) {}

void UHF(const Parser &vars, const AOIntegrals &aoints, const Molecule &mol,
         MolecularOrbitals &mo) {}
}  // namespace QCM
