#include "evolution.hpp"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <typeinfo>

#include "random.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

EvolutionConfig::EvolutionConfig(){
    maxGenerations = 100;
    populationSize = 50;
    tournamentSize = 5;
    pMutation = 0.05;
    pCrossover = 0.5;
    pInit = 0.5;
    maxSameGenerations = maxGenerations;

    ms = new FlipBitMutation();
    cs = new OnePointCrossover();
}
EvolutionConfig::~EvolutionConfig(){
    delete ms;
    delete cs;
}

void EvolutionConfig::loadArgs(int argc, char const *argv[]){
    char c;
    double f;
    int x;
    for(int i = 0; i < argc; i++){
        if(!argv || argv[i][0] != '-') continue;
        if(strlen(argv[i]) == 2){
            switch(argv[i][1]){
                case 'g':
                    x = atoi(argv[++i]);
                    if(x > 0)
                        maxGenerations = x;
                    if(maxGenerations < tournamentSize)
                        tournamentSize = maxGenerations;
                    break;
                case 'n':
                    x = atoi(argv[++i]);
                    if(x > 0)
                        populationSize = x;
                    break;
                case 'r':
                    x = atoi(argv[++i]);
                    if(x > 0)
                        tournamentSize = x;
                    if(maxGenerations < tournamentSize)
                        maxGenerations = tournamentSize;
                    break;
                case 'c':
                    c = argv[++i][0];
                    delete cs;
                    if(c == '1'){
                        cs = new OnePointCrossover();
                    }else if(c == '2'){
                        cs = new TwoPointCrossover();
                    }else{
                        cs = new UniformCrossover();
                    }
                    break;
                case 'm':
                    c = argv[++i][0];
                    delete ms;
                    if(c == '1'){
                        ms = new FlipBitMutation();
                    }else{
                        ms = new InversionMutation();
                    }
                    break;
            }
        }else if(strlen(argv[i]) == 3 && argv[i][1] == 'p'){
            switch(argv[i][2]){
                case 'i':
                    f = atof(argv[++i]);
                    if(0.0 <= f && f <= 1.0)
                        pInit = f;
                    break;
                case 'c':
                    f = atof(argv[++i]);
                    if(0.0 <= f && f <= 1.0)
                        pCrossover = f;
                    break;
                case 'm':
                    f = atof(argv[++i]);
                    if(0.0 <= f && f <= 1.0)
                        pMutation = f;
                    break;
            }
        }
    }
}

const CrossoverStrategy* EvolutionConfig::getCrossoverStrategy() const{
    return cs;
}
const MutationStrategy* EvolutionConfig::getMutationStrategy() const{
    return ms;
}

void EvolutionConfig::print(std::ostream& os) const{
    os << maxGenerations << ", " << populationSize << ", " << tournamentSize << ", ";
    os << pMutation << ", " << pCrossover << ", " << pInit << ", ";
    os << typeid(*cs).name() << ", " << typeid(*ms).name();
}

std::ostream& operator << (std::ostream& os, const EvolutionConfig& cfg){
    cfg.print(os);
    return os;
}

//==============================================================================

const Individual* Evolution::pickRandom() const{
    return population[Random::randInt(cfg.populationSize, 0)];
}

const Individual* Evolution::pickBest() const{
    int best = 0;
    for(int i = 1; i < cfg.populationSize; i++){
        if(population[i]->getFitness() > population[best]->getFitness()){
            best = i;
        }
    }
    return population[best];
}

void Evolution::selection(){
    Individual** nextPopulation = new Individual*[cfg.populationSize];
    for(int i = 0; i < cfg.populationSize; i++){
        const Individual* winner = pickRandom();
        for(int j = 1; j < cfg.tournamentSize; j++){
            const Individual* challenger = pickRandom();
            if(winner->getFitness() < challenger->getFitness()){
                winner = challenger;
            }
        }
        nextPopulation[i] = new Individual(*winner);
    }
    clearPopulation();
    population = nextPopulation;
}

void Evolution::reproduction(){
    int max = cfg.populationSize-1;
    for(int i = 0; i < max; i+=2){
        if(Random::randProbability() < cfg.pCrossover){
            cs->inPlace(population[i], population[i+1]);
        }
    }
}

void Evolution::mutation(){
    for(int i = 0; i < cfg.populationSize; i++){
        if(Random::randProbability() < cfg.pMutation){
            ms->inPlace(population[i]);
        }
    }
}

bool Evolution::termination() const{
    return generation >= cfg.maxGenerations || sameBest >= cfg.maxSameGenerations;
}

void Evolution::evaluation(){
    int best = 0, worst = 0, sum = 0;
    for(int i = 0; i < cfg.populationSize; i++){
        population[i]->repair();
        if(population[i]->getFitness() > population[best]->getFitness()){
            best = i;
        }else if(population[i]->getFitness() < population[worst]->getFitness()){
            worst = i;
        }
        sum += population[i]->getFitness();
    }
    averageFitness = sum  / (double)cfg.populationSize;
    sameBest = (*bestIndividual == *population[best] ? sameBest + 1 : 0);
    *bestIndividual = *population[best];
    *worstIndividual = *population[worst];
}

void Evolution::clearPopulation(){
    for(int i = 0; i < cfg.populationSize; i++){
        delete population[i];
    }
    delete[] population;
    population = NULL;
}

Evolution::Evolution(const Knapsack* k, const EvolutionConfig& cfg):knapsack(k),cfg(cfg){
    population = new Individual*[cfg.populationSize];
    for(int i = 0; i < cfg.populationSize; i++){
        population[i] = new Individual(true, knapsack);
    }
    bestIndividual = new Individual(*population[0]);
    worstIndividual = new Individual(*population[0]);
    evaluation();
    sameBest = generation = 0;
    ms = cfg.getMutationStrategy();
    cs = cfg.getCrossoverStrategy();
}

Evolution::~Evolution(){
    clearPopulation();
    delete bestIndividual;
    delete worstIndividual;
}

void Evolution::run(){
    while(!termination()){
        step();
    }
}

bool Evolution::isTerminated() const{
    return termination();
}
int Evolution::getBestFitness() const{
    return getBest()->getFitness();
}
int Evolution::getWorstFitness() const{
    return getWorst()->getFitness();
}
double Evolution::getAvgFitness() const{
    return averageFitness;
}
const Individual* Evolution::getBest() const{
    return bestIndividual;
}
const Individual* Evolution::getWorst() const{
    return worstIndividual;
}


void Evolution::run(std::ostream& os){
    while(!termination()){
        step();
        os << *this << std::endl;
    }
}

void Evolution::step(){
    generation++;
    selection();
    reproduction();
    mutation();
    evaluation();
}

void Evolution::print(std::ostream& os) const{
    os << generation << " ";
    os << bestIndividual->getFitness() << " ";
    os << averageFitness << " ";
    os << worstIndividual->getFitness();
}

std::ostream& operator << (std::ostream& os, const Evolution& evo){
    evo.print(os);
    return os;
}
