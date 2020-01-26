# C programming for Data Science

Authors:
- [Sylvain Combettes](https://www.linkedin.com/in/sylvain-combettes), MSc candidate at Ecole des Mines de Nancy
- [Julien Muller](https://fr.linkedin.com/in/julien-muller-9b3a77166), MSc candidate at Ecole des Mines de Nancy

## How to compile the neural network?

Once we are in the correct directory, run in a Terminal:
```
g++ makeTrainingSamples.cpp -o makeTrainingSamples
./makeTrainingSamples > trainingData.txt
vim trainingData.txt
:q
g++ neural-net-tutorial.cpp -o neural-net-tutorial
./neural-net-tutorial > out.txt
vim out.txt
:q
```
