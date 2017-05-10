#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

struct clause {
    int v1;
    int v2;
    int v3;
};

// Returns how many clauses are tru
int energy(bool *variables, std::vector<clause> &clauses)
{
    int n = 0;
    std::vector<clause>::iterator it;
    for (it = clauses.begin(); it != clauses.end(); it++)
    {
        if( variables[it->v1] || variables[it->v2] || variables[it->v3] )
        {
            n++;
        }
    }
    return n;
}

int disturb(bool *variables, int nVariables)
{
    int percentage = 20;
    for (int i = 0; i < nVariables; i++)
    {
        int p = (std::rand() % 100) + 1;
        if (p <= percentage)
        {
            variables[i] = !variables[i];
        }
    }
}

int main(int argc, char *argv[])
{
    int nVariables, nClauses;
    std::vector<clause> clauses;

    if (argc != 2)
    {
        std::cout << "./sa_3sat input\n";
        return 0;
    }

    std::string inputFile(argv[1]);
    std::string line;
    std::ifstream infile(inputFile);

    if (!infile.is_open())
    {
        std::cout << "File not found.\n";
        return 0;
    }

    // The first 7 lines are useless
    for(int i = 0; i < 7; i++)
        getline(infile, line);

    getline(infile, line);
    sscanf(line.c_str(), "%*s %*s %d %d", &nVariables, &nClauses);

    bool *variables;
    variables = (bool*) malloc(sizeof(bool) * nVariables);
    memset(variables, 0, sizeof(bool) * nVariables);

    printf("a: %d %d\n\n", nVariables, nClauses);
    
    for(int i = 0; i < nClauses; i++)
    {
        getline(infile, line);
        clause c;
        sscanf(line.c_str(), "%d %d %d %*d", &c.v1, &c.v2, &c.v3);
        clauses.push_back(c);
    }

}
