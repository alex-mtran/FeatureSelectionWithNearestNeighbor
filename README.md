# FeatureSelectionWithNearestNeighbor
Winter 2025 CS170 Project 2

Feature selection with nearest neighbor classifier using forward selection and backward elimination with "leaving-one-out" evaluation. Used on datasets that have two classes with continuous features. Algorithm can be used on datasets with multiple classes, but requires continuous features.

Creates an output file that 0's out irrelevant features (features that do not belong to the best_feature_set).

Default rate = size(most common class) / size(dataset)

- Default rate is the accuracy if we use no features

Forward selection

- Given a set of n features, there are 2^n feature subsets we can test
- Greedy algorithm
- Initial state: no features
- Operators: add one feature
- Evaluation function: K-fold cross validation

Backward Elimination

- Same as forward selection but with:
- Initial state: all features
- Operators: remove one feature
- Evaluation function: K-fold cross validation

Accuracy = Number of correct classifications / Number of instances in our database

Commands to run program:

g++ -std=c++11 -o main main.cpp
./main
