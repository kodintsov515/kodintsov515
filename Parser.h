#pragma once

#include <string>

class Parser {
public:
    Parser(const int argc, char* argv[]);
    const std::string& getXyzFile() const;
    const std::string& getBasisFile() const;
    int getCharge() const;

private:
    std::string xyzfile{""};
    std::string basisfile{""};
    int charge{0};
    bool isLoaded{false};
};
