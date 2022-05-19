#include "Parser.h"
#include <stdexcept>

Parser::Parser(const int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        auto key = std::string(argv[i]);

        if ((key == "--geom") or (key == "-g")) {
            if (++i == argc) {
                throw std::runtime_error(
                    "Expected value after key -geom is empty");
            }
            xyzfile = std::string(argv[i]);
            continue;
        }
        if ((key == "--basis") or (key == "-b")) {
            if (++i == argc) {
                throw std::runtime_error(
                    "Expected value after key -basis is empty");
            }
            basisfile = std::string(argv[i]);
            continue;
        }
        if ((key == "--charge") or (key == "-c")) {
            if (++i == argc) {
                throw std::runtime_error(
                    "Expected value after key -charge is empty");
            }
            charge = atoi(argv[i]);
            continue;
        }
        throw std::runtime_error("Unknown key \"" + key + "\"");
    }
    if (xyzfile.empty()) throw std::runtime_error("XYZ file not specified");
    if (basisfile.empty()) throw std::runtime_error("Basis file not specified");
    isLoaded = true;
}

const std::string& Parser::getXyzFile() const {
    if (not isLoaded) throw std::runtime_error("CommLine not yet parsed");
    return xyzfile;
}

const std::string& Parser::getBasisFile() const {
    if (not isLoaded) throw std::runtime_error("CommLine not yet parsed");
    return basisfile;
}

int Parser::getCharge() const {
    if (not isLoaded) throw std::runtime_error("CommLine not yet parsed");
    return charge;
}
