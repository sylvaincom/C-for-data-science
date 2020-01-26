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
in: 4.7 3.2 1.3 0.2
out: 0.0
in: 4.6 3.1 1.5 0.2
out: 0.0
in: 5.0 3.6 1.4 0.2
out: 0.0
```
It is important to have our data in this specific format because lines 15 to 110 of `neural-network-tutorial.cpp` are designed to read the training data in this specific format.
Note that in the first line, we changed the number of neurons in the input layer, as our training data is of size 4 (plus the label).

However, our data set `iris.txt` is ordered because we first have 50 samples with label 0 then 50 samples with label 1 then 50 samples with label 2. We need to shuffle it.
