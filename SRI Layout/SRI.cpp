#include "SRI.hpp"
#include <iostream>
#include "Utility.hpp"

using namespace std;
using namespace std::placeholders;
using namespace utility;

void SRI::InterpretLine(string& line)
{
    MakeValid(line);
    vector<string> words = StringToVector(line, ' ');
    
    auto commandFunction = commands.find (words[0]);
    if ( commandFunction == commands.end() )
        return;
    
    words.erase(words.begin());
    
    commandFunction->second(words);
}

SRI::SRI()
{
    commands.insert(make_pair("LOAD", bind (&SRI::Load, this, _1)));
    commands.insert(make_pair("DUMP", bind (&SRI::Save, this, _1)));
    commands.insert(make_pair("FACT", bind (&SRI::Fact, this, _1)));
    commands.insert(make_pair("RULE", bind (&SRI::Rule, this, _1)));
    commands.insert(make_pair("INFERENCE", bind (&SRI::Infer, this, _1)));
    commands.insert(make_pair("DROP", bind (&SRI::Drop, this, _1)));
    
    commands.insert(make_pair("l", bind (&SRI::Load, this, _1)));
    commands.insert(make_pair("s", bind (&SRI::Save, this, _1)));
    commands.insert(make_pair("f", bind (&SRI::Fact, this, _1)));
    commands.insert(make_pair("r", bind (&SRI::Rule, this, _1)));
    commands.insert(make_pair("i", bind (&SRI::Infer, this, _1)));
    commands.insert(make_pair("d", bind (&SRI::Drop, this, _1)));
    
    ruleBase.engine = (this);
}

SRI::~SRI(){}

void SRI::Drop(vector<string> input)
{
    knowledgeBase.DropFact(input[0]);
    ruleBase.DropRule(input[0]);
}

void SRI::Fact(vector<string> input)
{
    Clause fact= StringToClause(input[0]);
    knowledgeBase.AddFact(fact.name, fact.parameters);
}

void SRI::Rule(vector<string> input)
{
    Subrule entry;

    Clause firstClause = StringToClause(input[0]);
    
    entry.parameters = firstClause.parameters;
    
    // =========================
    
    if (input[1] == "AND")
    {
        entry.isAnd = true;
    }
    else if (input[1] == "OR")
    {
        entry.isAnd = false;
    }
    else return;
    
    input.erase(input.begin() + 1);
    
    // =========================

    for (int i = 1; i < input.size(); ++i)
    {
        entry.clauses.push_back( StringToClause(input[i]) );
    }
    
    ruleBase.AddRule(firstClause.name, entry);
}

void SRI::Save(vector<string> input)
{
    string filePath = input[0];
}

void SRI::Load(vector<string> input)
{
    string filePath = input[0];
}

void SRI::Infer(vector<string> input)
{
    Clause inference = StringToClause(input[0]);
    string outputFact = (input.size() > 1) ? input[1] : "";
    
    vector<vector<string>> results = GetSet(inference.name, inference.parameters);
    
    if (outputFact != "")
    {
        for (auto i : results)
        {
            knowledgeBase.AddFact(outputFact, i);
        }
    }
}

vector<vector<string>> SRI::GetSet (string name, vector<string> params)
{
    vector<vector<string>> factResults = knowledgeBase.GetResultSet(name, params);
    vector<vector<string>> ruleResults = ruleBase.GetResultSet(name, params);
    vector<vector<string>> output;
    
    output.reserve( factResults.size() + ruleResults.size() );
    output.insert( output.end(), factResults.begin(), factResults.end() );
    output.insert( output.end(), ruleResults.begin(), ruleResults.end() );
    
    return output;
}
