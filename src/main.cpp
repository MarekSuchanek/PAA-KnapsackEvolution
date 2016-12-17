// MI-PAA ZS 2016/17, HW 4
// FIT CTU in Prague
// Marek Suchanek (suchama4@fit.cvut.cz)
// Knapsack problem solving via Genetic Algorithm

/**
 * Usage: knapevo instance_file solution_file [opts]
 * opts:
 *  -g  <integer> (>0)     = Max generations
 *  -n  <integer> (>0)     = Population size
 *  -r  <integer> (1 to g) = Tournament size
 *  -pi <float>   (0 to 1) = Probability init
 *  -pc <float>   (0 to 1) = Probability crossover
 *  -pm <float>   (0 to 1) = Probability mutate
 *  -c  (1|2|U)            = Crossover strategy (1point, 2point, uniform)
 *  -m  (1|I)              = Mutation strategy (1 bit flip, inversion)
 */
#include <iostream>
#include <fstream>
#include <ctime>

#include "knapsack.hpp"
#include "evolution.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

using namespace std;


int mainAverage(int argc, char const *argv[]){
    Knapsack knapsack;
    EvolutionConfig cfg = EvolutionConfig();

    if(argc < 3){
        cerr << argv[0] << "<instance_file> <solution_file> [opts]" << endl;
        return 1;
    }
    cfg.loadArgs(argc, argv);
    cerr << cfg << endl;

    ifstream ifs_ins(argv[1]);
    ifstream ifs_sol(argv[2]);
    clock_t timeStart, timeEnd;
    double totalRelErr, maxErr = 0, totalTime, relErr, timeEvo;
    int n = 0;

    while(!ifs_ins.eof()) {
        knapsack.loadInstance(ifs_ins);
        knapsack.loadSolution(ifs_sol);
        if(ifs_ins.fail() || ifs_sol.fail()) break;
        Evolution evo(&knapsack, cfg);
        timeStart = clock();
        evo.run();
        timeEnd = clock();
        totalTime += timeEvo = (timeEnd-timeStart)/(long double)CLOCKS_PER_SEC;
        totalRelErr += relErr = knapsack.relativeError(evo.getBestFitness());
        //cerr << fixed << knapsack.getOptimum() << " " << evo.getBestFitness() << " " << relErr << " " << timeEvo << endl;
        n++;
        if(relErr > maxErr) maxErr = relErr;
    }
    cout << totalRelErr/n << " " << maxErr << " " << totalTime/n << endl;
    ifs_ins.close();
    ifs_sol.close();
    return 0;
}

int mainOne(int argc, char const *argv[]){
    Knapsack knapsack;
    EvolutionConfig cfg = EvolutionConfig();

    if(argc < 3){
        cerr << argv[0] << "<instance_file> <solution_file> [opts]" << endl;
        return 1;
    }
    cfg.loadArgs(argc, argv);
    cerr << cfg << endl;

    ifstream ifs_ins(argv[1]);
    ifstream ifs_sol(argv[2]);
    clock_t timeStart, timeEnd;
    double totalRelErr, maxErr = 0, totalTime, relErr, timeEvo;
    int n = 0;

    while(!ifs_ins.eof()) {
        knapsack.loadInstance(ifs_ins);
        knapsack.loadSolution(ifs_sol);
        if(ifs_ins.fail() || ifs_sol.fail()) break;
        Evolution evo(&knapsack, cfg);
        timeStart = clock();
        while(!evo.isTerminated()){
            evo.step();
            cout << evo.getGeneration() << " " << evo.getBestFitness() << " " << evo.getAvgFitness() << endl;
        }
        timeEnd = clock();
        totalTime += timeEvo = (timeEnd-timeStart)/(long double)CLOCKS_PER_SEC;
        totalRelErr += relErr = knapsack.relativeError(evo.getBestFitness());
        cout << "-----------------------------------" << endl;
        cout << fixed << knapsack.getOptimum() << " " << evo.getBestFitness() << " " << relErr << " " << timeEvo << endl;
        cout << "-----------------------------------" << endl;
        n++;
        if(relErr > maxErr) maxErr = relErr;
    }
    cout << "===========================================" << endl;
    cout << "Summary: " << totalRelErr/n << " " << maxErr << " " << " " << totalTime/n << endl;
    cout << "===========================================" << endl;
    ifs_ins.close();
    ifs_sol.close();
    return 0;
}

int main(int argc, char const *argv[]) {
    return mainOne(argc, argv);
}
