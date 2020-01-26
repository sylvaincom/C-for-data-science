## Making a Neural Net Simulator in C++ and applying it on the XOR data

The codes are taken from [David Miller's tutorial](http://www.millermattson.com/dave/?p=54) from 2011. Congrats to his work!

We execute the `cpp` files with the `g++` compiler in a Terminal. We move into the correct folder.

## 1) Generating our training data: XOR

First, we generate our training data to predict the values of [XOR](https://en.wikipedia.org/wiki/Exclusive_or), which will be the input of our neural network:
```
g++ makeTrainingSamples.cpp -o makeTrainingSamples
./makeTrainingSamples > trainingData.txt
```

We open our training data with:
```
vim trainingData.txt
```
(Enter `:q` to quit the file.)

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
The first line is the topology we want for our neural network. Here, the architecture of our neural network consists of three layers with respectively 2, 4 and 1 nodes. (Indeed, the input is of size 2 and the ouput is of size 1.) Then, we give the corresponding inputs and outputs we wish our neural network to predict.

## 2) Training our neural network (on the previous training data)

Once we have our training data, we train our neural network on it. The training data we choose has to be stated at line 361 of the file `neural-net-tutorial.cpp`:
```
    TrainingData trainData("trainingData.txt");
```
Here, the training data is stated as being `trainingData.txt`. The command for training our neural network is:
```
g++ neural-net-tutorial.cpp -o neural-net-tutorial
./neural-net-tutorial > out.txt
```
(Note that the execution is very fast.)

We open the results `out.txt`:
```
vim out.txt
```

The header of our results `out.txt` is:
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
The first lines are debug statements. We have 2000 passes in total, each pass corresponding to a training sample. At each pass, `Outputs` is the value our neural network predicts given the training sample and `Targets` is the correct true value we wish our neural network to predict. For the first pass, there is an error that gets better after each update of the weights. At pass 8, we can see that the prediction is still very bad. However at the last passes, the results are much better:
```
Pass 1999: Inputs: 0 1 
Outputs: 0.970885 
Targets: 1 
Net recent average error: 0.0220707

Pass 2000: Inputs: 1 1 
Outputs: 0.00373252 
Targets: 0 
Net recent average error: 0.0218892

Pass 2001: Inputs: 0 0 
Outputs: 0.00412659 
Targets: 0 
Net recent average error: 0.0217133

Pass 2002
Done
```
We have trained the weights our neural network: given an input, we can predict the XOR value!

## 3) Modifying the model of our neural network

We can modify the topology of our neural network by writing line 11 of `makeTrainingSamples.cpp`:
```
	cout << "topology: 2 5 1" << endl;
```
instead of:
```
	cout << "topology: 2 4 1" << endl;
```
Hence, our hidden layer will have 5 neurons instead of 4.  We ran the simulations and we appear to have better results (meaning that the error gets smaller faster with respect to the index of pass).

Being able to modidy the architecture of our model is very important. Note that the topology (for example the number of neurons of the hidden-layer) is a hyper-parameter.
> In machine learning, a **hyperparameter** is a parameter whose value is set before the learning process begins. The values of other parameters are obtained via training.

We can also modify all the other important hyperparameters :
- the learning rate at line 139 of `neural-net-tutorial.cpp`
- the activation/transfer function at lines 192-202 of `neural-net-tutorial.cpp`
- the loss/error function at lines 262-272 of `neural-net-tutorial.cpp`

We did several simulations to see the impact on the convergence.
