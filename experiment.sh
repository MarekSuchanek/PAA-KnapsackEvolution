#!/bin/bash

INSTANCE_FILE="problems/knap_200.dat"
SOLUTION_FILE="problems/knap_200.sol.dat"

make clean
make

for i in $(seq 50 50 1000)
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -g $i  | tee -a experiment.generations.txt
done

for i in $(seq 50 50 1000)
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -n $i 2> /dev/null | tee -a experiment.generations.txt
done

for i in 1 $(seq 5 5 100)
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -r $i 2> /dev/null | tee -a experiment.tournament.txt
done

for i in $(seq 0.00 0.05 1.00)
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -pi $i 2> /dev/null | tee -a experiment.pinit.txt
done

for i in $(seq 0.00 0.05 1.00)
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -pc $i 2> /dev/null | tee -a experiment.pcrossover.txt
done

for i in $(seq 0.00 0.05 1.00)
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -pm $i 2> /dev/null | tee -a experiment.pmutate.txt
done

for i in 1 2 U
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -c $i 2> /dev/null | tee -a experiment.crossover.txt
done

for i in 1 I
do
    ./bin/knapevo $INSTANCE_FILE $SOLUTION_FILE -m $i 2> /dev/null | tee -a experiment.mutation.txt
done
