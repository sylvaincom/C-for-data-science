## Making a Neural Net Simulator in C++

The codes are taken from [Dave Miller's tutorial](http://www.millermattson.com/dave/?p=54).

To run them, once we are in the correct directory, execute in a Terminal:
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
