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

// Returns how many clauses are true
int energy(bool *variables, std::vector<clause> &clauses)
{
    int n = 0;
    std::vector<clause>::iterator it;
    for (it = clauses.begin(); it != clauses.end(); it++)
    {
        bool x, y, z;
        if ( it->v1 < 0 )
            x = ! variables[(-it->v1) - 1];
        else
            x = variables[it->v1 - 1];

        if ( it->v2 < 0 )
            y = ! variables[(-it->v2) - 1];
        else
            y = variables[it->v2 - 1];

        if ( it->v3 < 0 )
            z = ! variables[(-it->v3) - 1];
        else
            z = variables[(it->v3) - 1];

        if( x || y || z )
        {
            n++;
        }
    }
    return n;
}

int disturb2(bool *variables, int nVariables, std::vector<clause> &clauses)
{
    std::vector<clause>::iterator it;
    for (it = clauses.begin(); it != clauses.end(); it++)
    {
        bool x, y, z;
        if ( it->v1 < 0 )
            x = ! variables[(-it->v1) - 1];
        else
            x = variables[it->v1 - 1];

        if ( it->v2 < 0 )
            y = ! variables[(-it->v2) - 1];
        else
            y = variables[it->v2 - 1];

        if ( it->v3 < 0 )
            z = ! variables[(-it->v3) - 1];
        else
            z = variables[(it->v3) - 1];

        if(!( x || y || z))
        {
            if (!x) {
                if (std::rand() % 2)
                {
                    variables[std::abs(it->v1)-1] = !variables[std::abs(it->v1)-1];
                }
            }

            if (!y) {
                if (std::rand() % 2)
                {
                    variables[std::abs(it->v2)-1] = !variables[std::abs(it->v2)-1];
                }
            }

            if (!z) {
                if (std::rand() % 2)
                {
                    variables[std::abs(it->v3)-1] = !variables[std::abs(it->v3)-1];
                }
            }
        }
    }
}

int disturb(bool *variables, int nVariables)
{
    int percentage = 5;
    for (int i = 0; i < nVariables; i++)
    {
        int p = (std::rand() % 100) + 1;
        if (p <= percentage)
        {
            variables[i] = !variables[i];
        }
    }
}

double coolingSchedule0(int iteration, int nIterations, double tInit, double tFinal)
{
    return tInit - ( iteration * ( (tInit - tFinal) / nIterations ) );
}

double coolingSchedule1(int iteration, int nIterations, double tInit, double tFinal)
{
    return tInit * std::pow((tFinal / tInit), (double) iteration / nIterations);
}

double coolingSchedule7(int iteration, int nIterations, double tInit, double tFinal)
{
    return  ((tInit - tFinal) / std::cosh( (10*iteration) / nIterations )) + tFinal;
}

double coolingSchedule5(int iteration, int nIterations, double tInit, double tFinal)
{
    return (0.5 * (tInit - tFinal)) * (1 + cos( (iteration * M_PI) / nIterations)) + tFinal;
}

double coolingSchedule8(int iteration, int nIterations, double tInit, double tFinal)
{
    double a = ( 1.0 / nIterations ) * std::log( tInit / tFinal);
    return tInit * std::exp( (-a) * iteration);

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

    bool *candidate, *next_cand;
    candidate = (bool*) malloc(sizeof(bool) * nVariables);
    next_cand = (bool*) malloc(sizeof(bool) * nVariables);
    memset(candidate, 0, sizeof(bool) * nVariables);
    memset(next_cand, 0, sizeof(bool) * nVariables);

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
    }

    int nIterations = 500000;
    double init_temp = 5;
    double final_temp = 0;
    double temperature = init_temp;

    for (int iteration = 0; iteration < nIterations; iteration++)
    {
        memcpy(next_cand, candidate, sizeof(bool) * nVariables);
        disturb(next_cand, nVariables);
        //disturb2(next_cand, nVariables, clauses);
        int energy_next = energy(next_cand, clauses);
        int energy_cand = energy(candidate, clauses);
        printf("%d %d\n", iteration, energy_cand);
        int deltaE =  energy_next - energy_cand;
        if (deltaE > 0)
        {
            memcpy(candidate, next_cand, sizeof(bool) * nVariables);
        }
        else
        {
            double probability = std::exp( deltaE / temperature );
            probability *= 1000;
            //printf("Probability: %lf Delta: %d Temperature: %lf\n", probability, deltaE, temperature);
            // do stuff
            int r = std::rand() % 1000;
            if ( r < probability )
            {
                memcpy(candidate, next_cand, sizeof(bool) * nVariables);
            }
        }
        
        temperature = coolingSchedule5(iteration, nIterations, init_temp, final_temp);
    }
}
