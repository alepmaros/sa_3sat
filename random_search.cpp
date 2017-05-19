/*
 * RANDOM SEARCH 3-SAT
 *
 */

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
#include <ctime>

struct clause {
    int v1;
    int v2;
    int v3;
};

int disturb(bool *variables, int nVariables)
{
    int percentage = 50;
    for (int i = 0; i < nVariables; i++)
    {
        int p = (std::rand() % 100) + 1;
        if (p <= percentage)
        {
            variables[i] = !variables[i];
        }
    }
}

// Returns how many clauses are true
int energy(bool *variables, std::vector<clause> &clauses)
{
    int n = 0;
    std::vector<clause>::iterator it;
    for (it = clauses.begin(); it != clauses.end(); it++)
    {
        bool x, y, z;
        if ( it->v1 < 0 )
            x = !variables[(-it->v1) - 1];
        else
            x = variables[it->v1 - 1];

        if ( it->v2 < 0 )
            y = !variables[(-it->v2) - 1];
        else
            y = variables[it->v2 - 1];

        if ( it->v3 < 0 )
            z = !variables[(-it->v3) - 1];
        else
            z = variables[it->v3 - 1];

        if( x || y || z )
        {
            n++;
        }
    }
    return n;
}

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
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

    bool *candidate, *next_cand, *best_cand;
    candidate = (bool*) malloc(sizeof(bool) * nVariables);
    next_cand = (bool*) malloc(sizeof(bool) * nVariables);
    best_cand = (bool*) malloc(sizeof(bool) * nVariables);
    memset(candidate, 0, sizeof(bool) * nVariables);
    memset(next_cand, 0, sizeof(bool) * nVariables);
    memset(best_cand, 0, sizeof(bool) * nVariables);

    for(int i = 0; i < nClauses; i++)
    {
        getline(infile, line);
        clause c;
        sscanf(line.c_str(), "%d %d %d %*d", &c.v1, &c.v2, &c.v3);
        clauses.push_back(c);
    }

    // Generating Random Initial "solution"
    for (int i = 0; i < nVariables; i++)
    {
        candidate[i] = std::rand() % 2;
        best_cand[i] = candidate[i];
    }

    int nIterations = 500000;
    double init_temp = 8;
    double final_temp = 0;
    double temperature = init_temp;

    int energy_best = energy(best_cand, clauses);
    for (int iteration = 0; iteration < nIterations; iteration++)
    {
        memcpy(next_cand, candidate, sizeof(bool) * nVariables);
        disturb(next_cand, nVariables);
        int energy_next = energy(next_cand, clauses);
        int energy_cand = energy(candidate, clauses);
        if (energy_next - energy_cand > 0)
        {
            memcpy(candidate, next_cand, sizeof(bool) * nVariables);
            if (energy_cand - energy_best > 0)
            {
                energy_best = energy_cand;
                memcpy(best_cand, next_cand, sizeof(bool) * nVariables);
            }
        }
        printf("%d %d\n",iteration, energy_best);
    }
}
