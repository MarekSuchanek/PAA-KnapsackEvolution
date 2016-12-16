#include "mutation.hpp"

#include "random.hpp"

Individual* MutationStrategy::mutant(const Individual* original) const{
    Individual* mutant = new Individual(*original);
    inPlace(mutant);
    return mutant;
}

void FlipBitMutation::inPlace(Individual* ind) const{
    ind->neg(Random::randInt(ind->size()));
}

void InversionMutation::inPlace(Individual* ind) const{
    for(int i = 0; i < ind->size(); i++){
        ind->neg(i);
    }
}

void ExperimentalMutation::inPlace(Individual* ind) const{
    int point = Random::randInt(ind->size());
    while(ind->get(point % ind->size())){
        point++;
    }
    ind->neg(point % ind->size());
}
