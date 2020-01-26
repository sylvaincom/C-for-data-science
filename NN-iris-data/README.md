# Applying our Neural Net Simulator in C++ to the Iris data set

The [Iris flower data set](https://en.wikipedia.org/wiki/Iris_flower_data_set) is a very popular and basic data set in machine learning. It was obtained for Python's library [scikit-learn](https://scikit-learn.org/stable/modules/generated/sklearn.datasets.load_iris.html#sklearn-datasets-load-iris) and it is described in the doucmentation.

Our training data has 3 classes (labels 0, 1 and 2), with 50 samples per class and 150 samples total. The dimension of our data is 4.

# 1) Getting the Iris dataset in the right format

We loaded the Iris data set on Python and exported in the `txt` format using the Pandas library. Then, we opened a basic text editor to change it so that the header of `iris.txt` is:
```
topology: 4 4 1
in: 5.1 3.5 1.4 0.2
out: 0.0
in: 4.9 3.0 1.4 0.2
out: 0.0
```
It is important to have our data in this specific format because lines 15 to 110 of `neural-network-tutorial.cpp` are designed to read the training data in this specific format.
Note that in the first line, we changed the number of neurons in the input layer, as our training data is of size 4 (plus the label).

Note that our data set `iris.txt` is ordered because we first have 50 samples with label 0 then 50 samples with label 1 then 50 samples with label 2.

# 2) Training our neural network on `iris.txt`

Once we have our training data, we train our neural network on it. The training data we choose has to be stated at line 361 of the file neural-net-tutorial.cpp:
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
Outputs: 0.875738 
Targets: 0 
Net recent average error: 0.00867068

Pass 2: Inputs: 4.9 3 1.4 0.2 
Outputs: 0.834896 
Targets: 0 
Net recent average error: 0.0168511
```
and the last lines are:
```
Pass 99: Inputs: 5.1 2.5 3 1.1 
Outputs: 0.964238 
Targets: 1 
Net recent average error: 0.0457231

Pass 100: Inputs: 5.7 2.8 4.1 1.3 
Outputs: 0.964507 
Targets: 1 
Net recent average error: 0.0456218

Pass 101
Done
```

Thus, we have trained our neural network on another data set!
