#include "KnowledgeBase.hpp"
#include <iostream>
#include "Utility.hpp"

using namespace std;
using namespace utility;

void KnowledgeBase::AddFact (string name, vector<string> params)
{
    auto factEntry = facts.find (name);
    
    if ( factEntry == facts.end() )
    {
        facts[name] = vector<vector<string>> {params};
    }
    else
    {
        facts[name].push_back(params);
    }
    //Export(cout);
}

void KnowledgeBase::DropFact (string name)
{
    facts.erase(name);
    //Export(cout);
}

vector<vector<string>> KnowledgeBase::GetResultSet(string name, vector<string> params)
{
    auto result = facts.find(name);
    
    if ( result == facts.end() )
    {
        vector<vector<string>> empty;
        return empty;
    }
    
    auto unfilteredResults =  result->second;
    
    vector<vector<string>> finalResults;

    for (auto i : unfilteredResults)
    {
        if (i.size() != params.size())
            continue;
        
        bool isValid = true;
        unordered_map<string, string> usedParams;
        
        for (int k = 0; k < params.size(); ++k)
        {
            if (IsVariable(params[k]))
            {
                auto entry = usedParams.find(params[k]);
                if (entry == usedParams.end())
                {
                    usedParams[params[k]] = i[k];
                    continue;
                }
                string expectedResult = entry->second;
                
                if (i[k] != expectedResult)
                {
                    isValid = false;
                    break;
                }
                
                continue;
            }
            
            if (params[k] != i[k])
            {
                isValid = false;
                break;
            }
        }
        
        if (isValid)
            finalResults.push_back(i);
    }
    
    return finalResults;
}

void KnowledgeBase::Export(ostream& file)
{
    file << "==== FACTS ====" << endl;
    
    for (auto fact : facts)
    {
        file << fact.first << ": | ";
        
        for (auto entry : fact.second)
        {
            for (auto set : entry)
            {
                file << set << " ";
            }
            file << "| ";
        }
        
        file << endl;
    }
}


