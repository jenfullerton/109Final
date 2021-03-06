#ifndef Utility_hpp
#define Utility_hpp

#include "RuleBase.hpp"
#include <string>
#include <vector>

namespace utility
{
    void MakeValid (std::string& input);
    std::vector<std::string> StringToVector(std::string input, char delimiter);
    Clause StringToClause(std::string input);
    bool IsVariable (std::string input);
    int FindIndexOf (std::vector<std::string> vector, std::string value);
    std::vector<std::vector<std::string>> PermutateVector (std::vector<std::vector<std::string>> input);
}

#endif
