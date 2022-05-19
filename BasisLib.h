#pragma once

#include <string>
#include <map>
#include <vector>

struct oneTerm_t {
    double a{0};
    double c{0};
};

using radial_t = std::vector<oneTerm_t>;

class BasisLib {
public:
    void loadFromGamessUS(const std::string& filename);
    static int getT(const std::string& name);

protected:
    std::map<int, std::vector<std::vector<radial_t>>> content{};  // номер оболочки это индекс в векторе
private:
    const int L_MAX{5};
    static inline std::map<std::string, int> dict = {
        {"UNDEF", -2}, {"L", -1}, {"S", 0}, {"P", 1},
        {"D", 2},      {"F", 3},  {"G", 4}, {"H", 5}};
};
