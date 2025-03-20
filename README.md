# FeatureSelectionWithNearestNeighbor
Winter 2025 CS170 Project 2

Feature selection with nearest neighbor classifier using forward selection and backward elimination with "leaving-one-out" evaluation. Used on datasets that have two classes with continuous features. Algorithm can be used on datasets with multiple classes, but requires continuous features.

Creates an output file that 0's out irrelevant features (features that do not belong to the best_feature_set).

Commands to run program:

g++ -std=c++11 -o main main.cpp
./main