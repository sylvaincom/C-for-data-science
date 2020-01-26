## Making a Neural Net Simulator in C++ and applying it on the XOR data

The codes are taken from [David Miller's tutorial](http://www.millermattson.com/dave/?p=54) from 2011. Congrats to his work!

We execute the `cpp` files with the `g++` compiler in a Terminal. We move into the correct folder.

### 1) Generating our training data: XOR

First, we generate our training data to predict the values of [XOR](https://en.wikipedia.org/wiki/Exclusive_or), which will be the input of our neural network:
```
g++ makeTrainingSamples.cpp -o makeTrainingSamples
./makeTrainingSamples > trainingData.txt
```

We open our training data with:
```
vim trainingData.txt
```

The header of our training data is:
```
topology: 2 4 1
in: 1.0 0.0 
out: 1.0
in: 1.0 1.0 
out: 0.0
in: 1.0 0.0 
out: 1.0
in: 0.0 1.0 
out: 1.0
in: 0.0 1.0 
out: 1.0
```
The first line is the topology we want for our neural network. Here, the architecture of our neural network consists of three layers with respectively 2, 4 and 1 node. Then, we give the corresponding inputs and outputs we wish our neural network to predict.

### 2) Training our neural network (on the previous training data)

Once we have our training data, we train our neural network on it. The training data we choose has to be stated at line 361 of the file `neural-net-tutorial.cpp`. Here, the training data is stated as being `trainingData.txt`. The command for training our neural network is:
```
g++ neural-net-tutorial.cpp -o neural-net-tutorial
./neural-net-tutorial > out.txt
```
Note that the execution is very fast.

We open the results `out.txt`:
```
vim out.txt
```

The header of our results is:
```
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!
Made a Neuron!

Pass 1: Inputs: 1 0 
Outputs: 0.994386 
Targets: 1 
Net recent average error: 5.55817e-05

Pass 2: Inputs: 1 1 
Outputs: 0.996534 
Targets: 0 
Net recent average error: 0.00992171

Pass 3: Inputs: 1 0 
Outputs: 0.994338 
Targets: 1 
Net recent average error: 0.00987953

Pass 4: Inputs: 0 1 
Outputs: 0.991158 
Targets: 1 
Net recent average error: 0.00986925

Pass 5: Inputs: 0 1 
Outputs: 0.991142 
Targets: 1 
Net recent average error: 0.00985924
```

The first lines are debug statements. We have 2000 pass in total, each pass corresponding to a training sample. At each pass, the `Outputs` is the value our neural network predicts given the training sample and the `Targets` is the correct true value we wish our neural network to predict. For the first pass, there is an error that gets better after each update of the weights.
