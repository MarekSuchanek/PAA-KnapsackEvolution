#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "individual.hpp"

class MutationStrategy{
public:
    virtual Individual* mutant(const Individual* original) const;
    virtual void inPlace(Individual* ind) const = 0;
    virtual ~MutationStrategy();
};

class FlipBitMutation : public MutationStrategy{
public:
    void inPlace(Individual* ind) const;
};

class InversionMutation : public MutationStrategy{
public:
    void inPlace(Individual* ind) const;
};

#endif /* MUTATION_HPP */
