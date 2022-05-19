#include "BasisLib.h"
#include "Molecule.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

int BasisLib::getT(const std::string& name) {
    std::string upperName(name);
    for (auto& c : upperName) c = toupper(c);
    if (dict.find(upperName) == dict.end()) return dict["UNDEF"];
    return dict[upperName];
}

void BasisLib::loadFromGamessUS(const std::string& filename) {
    std::ifstream inp(filename);
    if (not inp) throw std::runtime_error("Problem with *.basis file");
    std::string tStr;
    int order;
    while (std::getline(inp, tStr)) {
        int atom_charge = Molecule::getQ(tStr);
        if (atom_charge != -1) {
            // тут будет жить весь базисный набор для одного атома
            std::vector<std::vector<radial_t>> shells(L_MAX);
            while (std::getline(inp, tStr)) {
                if (tStr == "") {
                    break;
                } else {
                    std::stringstream type_and_num(tStr);
                    std::string type = "";
                    type_and_num >> type;
                    std::size_t num = 0;
                    type_and_num >> num;
                    if (type != "L") {
                        radial_t one_type_group;
                        oneTerm_t l;
                        for (std::size_t q = 0; q < num; q++) {
                            inp >> order >> l.a >> l.c;
                            one_type_group.push_back(l);
                        }
                        shells[getT(type)].push_back(one_type_group);
                    } else {
                        radial_t radialS;
                        radial_t radialP;
                        oneTerm_t s, p;
                        for (std::size_t q = 0; q < num; q++) {
                            inp >> order >> s.a >> s.c >> p.c;
                            radialS.push_back(s);
                            radialP.push_back(p);
                        }
                        shells[0].push_back(radialS);
                        shells[1].push_back(radialP);
                    }
                }
            }
            content[atom_charge] = shells;
        }
    }
    inp.close();
}
