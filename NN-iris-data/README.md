# Applying our Neural Net Simulator in C++ to the Iris data set

The [Iris flower data set](https://en.wikipedia.org/wiki/Iris_flower_data_set) is a very popular and basic data set in machine learning. We obtained it using Python's library scikit-learn and it is described in the [documentation](https://scikit-learn.org/stable/modules/generated/sklearn.datasets.load_iris.html#sklearn-datasets-load-iris).

Our training data has 3 classes (labels 0, 1 and 2), with 50 samples per class and 150 samples total. The dimension of our data is 4.

# 1) Getting the Iris dataset into the right format

We loaded the Iris data set on Python and exported it into the `txt` format using the Pandas library. The labels are in {0, 1, 2}. Then, we opened a basic text editor to change it so that the header of `iris.txt` is:
```
topology: 4 4 1
in: 5.1 3.5 1.4 0.2
out: 0.0
in: 4.9 3.0 1.4 0.2
out: 0.0
```
It is important to have our data in this specific format because lines 17 to 103 of `neural-net-iris.cpp` are designed to read the training data in this specific format.
Note that in the first line, we changed the number of neurons in the input layer, as our training data is of size 4 (plus the label).

Note that our data set `iris.txt` is ordered because we first have 50 samples with label `0` then 50 samples with label `1` then 50 samples with label `2`.

# 2) Training our neural network on `iris.txt`

The target values are now in {0, 1, 2} so we can no longer use tanh as the activation function because it outputs in [-1, 1]. Hence, we use the [SoftPlus function](https://en.wikipedia.org/wiki/Activation_function) which outputs in all real positive numbers. We change the activation function at lines 197-208 of `neural-net-iris.cpp`. We also change the learning rate line 146 of `neural-net-iris.cpp`.

Once we have our training data, we train our neural network on it. The training data we choose has to be stated at line 369 of the file `neural-net-tutorial.cpp`:
```
    TrainingData trainData("iris.txt");
```
Here, the training data is stated as being `iris.txt`. The command for training our neural network is:
```
g++ neural-net-iris.cpp -o neural-net-iris
./neural-net-iris > out-iris.txt
```

The header of our results `out-iris.txt` is:
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
Made a Neuron!
Made a Neuron!

Pass 1: Inputs: 5.1 3.5 1.4 0.2 
Outputs: 8.97108 
Targets: 0 
Net recent average error: 0.0888225

Pass 2: Inputs: 4.9 3 1.4 0.2 
Outputs: 0 
Targets: 0 
Net recent average error: 0.0879431
```
and some excerpts are the following. When the neural network just finished learning the ouput `0` and starts learning the ouput `1`, we have: 
```
Pass 49: Inputs: 5.3 3.7 1.5 0.2 
Outputs: 0 
Targets: 0 
Net recent average error: 0.0550931

Pass 50: Inputs: 5 3.3 1.4 0.2 
Outputs: 0 
Targets: 0 
Net recent average error: 0.0545476

Pass 51: Inputs: 7 3.2 4.7 1.4 
Outputs: 0 
Targets: 1 
Net recent average error: 0.0639085

Pass 52: Inputs: 6.4 3.2 4.5 1.5 
Outputs: 0.00622988 
Targets: 1 
Net recent average error: 0.0731151
```
When the neural network just finished learning the ouput `1` and starts learning the ouput `2`, we have: 
```
Pass 99: Inputs: 5.1 2.5 3 1.1 
Outputs: 0.999932 
Targets: 1 
Net recent average error: 0.167481

Pass 100: Inputs: 5.7 2.8 4.1 1.3 
Outputs: 0.99994 
Targets: 1 
Net recent average error: 0.165823

Pass 101: Inputs: 6.3 3.3 6 2.5 
Outputs: 0.999953 
Targets: 2 
Net recent average error: 0.174083

Pass 102: Inputs: 5.8 2.7 5.1 1.9 
Outputs: 1.14407 
Targets: 2 
Net recent average error: 0.180834
```
When the neural network just finished learning the last ouput `2`, we have: 
```
Pass 149: Inputs: 6.2 3.4 5.4 2.3 
Outputs: 2 
Targets: 2 
Net recent average error: 0.123637

Pass 150: Inputs: 5.9 3 5.1 1.8 
Outputs: 2 
Targets: 2 
Net recent average error: 0.122413

Pass 151
Done
```

Thus, we have trained (thw weights of) our neural network on another data set: the Iris data set!
