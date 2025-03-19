#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

// datasets: small 98, big 91

// Z-normalized: X = (X - mean(X)) / std(x)
// Z-normalization is used to normalize features' units to pure numbers
// Has a mean of zero and a standard deviation of one

// Default rate = size(most common class) / size(dataset)
// Default rate is the accuracy if we use no features

// Forward selection
// Given a set of n features, there are 2^n feature subsets we can test
// Greedy algorithm with:
// Initial state: no features
// Operators: add one feature
// Evaluation function: K-fold cross validation

// FUNCTION STUBS
double normalize(double n);
double leave_one_out_cross_validation(const vector<vector<double> >& data, const vector<int>& current_set, int feature_to_add);
vector<vector<double> > readDataset(const string& filename);
double euclideanDistance();
void feature_search_demo(const vector<vector<double> >& data);


// FUNCTION DECLARATIONS
double normalize(double n) { // TODO
    return 0;
}

vector<vector<double> > readDataset(const string& filename) {
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

double euclideanDistance() { // TODO;
    return 0;
}

void feature_search_demo(const vector<vector<double> >& data) {
    vector<int> current_set_of_features;
    int num_features = data[0].size() - 1;
    int feature_to_add_at_this_level;
    double best_so_far_accuracy;

    for (int i = 0; i < num_features; ++i) {
        cout << "On the " << (i + 1) << "th level of the search tree" << endl;
        feature_to_add_at_this_level = -1;
        best_so_far_accuracy = 0.0;

        for (int k = 1; k <= num_features; ++k) {
            if (find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end()) { // if feature k is not in current_set_of_features
                cout << "--Considering adding the " << k << " feature" << endl;
                double accuracy = leave_one_out_cross_validation(data, current_set_of_features, k);

                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
            }
        }

        current_set_of_features.push_back(feature_to_add_at_this_level);
        cout << "On level " << (i + 1) << " I added feature " << feature_to_add_at_this_level << " to current set" << endl;
    }
    
    cout << endl << "Final set of selected features: ";
    for (int feature : current_set_of_features) {
        cout << feature << ' ';
    }
    cout << endl;
}

double leave_one_out_cross_validation(const vector<vector<double> >& data, const vector<int>& current_set, int feature_to_add) {
    return static_cast<double>(rand()) / RAND_MAX;
}

int main() {
    string file_name;
    string file_choice;
    
    cout << "Which dataset would you like to use: ('small' or 'large') ";
    cin >> file_choice;
    if (file_choice == "small") {
        file_name = "CS170_Small_Data__98.txt";
    }
    else if (file_choice == "large") {
        file_name = "CS170_Large_Data__91.txt";
    }
    else {
        cout << "Invalid choice. Expected 'small' or 'large'." << endl;
        exit(-1);
    }

    vector<vector<double> > dataset = readDataset(file_name);

    cout << endl << "Starting Feature Search Demo..." << endl;
    feature_search_demo(dataset);

    return 0;
}
