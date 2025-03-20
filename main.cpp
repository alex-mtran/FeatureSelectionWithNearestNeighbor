#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

// datasets: small 98, big 91

// Default rate = size(most common class) / size(dataset)
// Default rate is the accuracy if we use no features

// Forward selection
// Given a set of n features, there are 2^n feature subsets we can test
// Greedy algorithm with:
// Initial state: no features
// Operators: add one feature
// Evaluation function: K-fold cross validation

// Backward Elimination
// Same as forward selection but with:
// Initial state: all features
// Operators: remove one feature
// Evaluation function: K-fold cross validation

// Accuracy = Number of correct classifications / Number of instances in our database

// FUNCTION STUBS
double compute_accuracy(const vector<vector<double> >& data, const vector<int>& candidate_set);
vector<vector<double> > read_dataset(const string& filename);
void forward_selection(const vector<vector<double> >& data);
void backward_elimination(const vector<vector<double> >& data);
void print_vector(const vector<int>& vec);

// FUNCTION DECLARATIONS
vector<vector<double> > read_dataset(const string& filename) {
    vector<vector<double> > dataset;
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(-1);
    }

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        vector<double> row;
        double value;

        while (stream >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            dataset.push_back(row);
        }
    }

    file.close();
    return dataset;
}

void forward_selection(const vector<vector<double> >& data) {
    vector<int> current_set_of_features;
    vector<int> best_feature_set;
    int num_features = data[0].size() - 1; // exclude the classification column
    int feature_to_add_at_this_level;
    double best_so_far_accuracy = 0.0;
    double global_best_accuracy = 0.0;

    for (int i = 0; i < num_features; ++i) {
        feature_to_add_at_this_level = -1;
        best_so_far_accuracy = 0.0;

        for (int k = 1; k <= num_features; ++k) {
            if (find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end()) { // if feature i != feature k
                vector<int> test_set = current_set_of_features;
                test_set.push_back(k);

                double accuracy = compute_accuracy(data, test_set);
                cout << "\tUsing feature(s) {" << k << "} accuracy is " << (accuracy * 100) << '%' << endl;

                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
            }
        }

        current_set_of_features.push_back(feature_to_add_at_this_level);

        cout << "Feature set ";
        print_vector(current_set_of_features);
        cout << " was best, accuracy is " << (best_so_far_accuracy * 100) << '%' << endl;

        if (best_so_far_accuracy > global_best_accuracy) {
            global_best_accuracy = best_so_far_accuracy;
            best_feature_set = current_set_of_features;
        }
    }

    cout << endl << "Finished search!! The best feature subset is ";
    print_vector(best_feature_set);
    cout << ", which has an accuracy of " << (global_best_accuracy * 100) << '%' << endl;
}

void backward_elimination(const vector<vector<double> >& data) {
    cout << "TODO" << endl;
}

double compute_accuracy(const vector<vector<double> >& data, const vector<int>& candidate_set) {
    double number_correctly_classified = 0;
    double nearest_neighbor_distance;
    int nearest_neighbor_label;
    double distance;
    double accuracy = 0;

    for (int i = 0; i < data.size(); ++i) {
        double label_object_to_classify = data[i][0]; // first column is the label column

        nearest_neighbor_distance = numeric_limits<double>::infinity();
        nearest_neighbor_label = -1;

        for (int k = 0; k < data.size(); ++k) {
            if (i != k) {
                distance = 0.0;

                for (int f : candidate_set) {
                    double diff = data[i][f] - data[k][f];
                    distance += diff * diff;
                }
                
                distance = sqrt(distance);

                if (distance < nearest_neighbor_distance || (distance == nearest_neighbor_distance && nearest_neighbor_label == -1)) {
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_label = data[k][0];
                }
            }
        }

        if (label_object_to_classify == nearest_neighbor_label) {
            number_correctly_classified++;
        }
    }

    accuracy = number_correctly_classified / data.size();

    return accuracy;
}

void print_vector(const vector<int>& vec) {
    cout << '{';
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << '}';
}

int main() {
    string file_name;
    string search_function;
    
    cout << "Welcome to Alexander Tran's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: "; 
    cin >> file_name;
    
    vector<vector<double> > dataset = read_dataset(file_name);

    cout << "This dataset has " << (dataset[0].size() - 1) << " features (not including the class attribute), with " << dataset.size() << " instances." << endl;
    cout << "Type in the name of the search function ('forward_selection' or 'backward_elimination'): ";
    cin >> search_function;
    cout << "Beginning search." << endl;
    
    if (search_function == "forward_selection") {
        forward_selection(dataset);
    }
    else {
        backward_elimination(dataset);
    }

    return 0;
}
