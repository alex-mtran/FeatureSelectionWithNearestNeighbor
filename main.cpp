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

// Accuracy = Number of correct classifications / Number of instances in our database

// FUNCTION STUBS
double normalize(double n);
double leave_one_out_cross_validation(const vector<vector<double> >& data, const vector<int>& current_set, int feature_to_add);
vector<vector<double> > read_dataset(const string& filename);
double euclidean_distance(const vector<double>& vec1, const vector<double>& vec2);
void feature_search_demo(const vector<vector<double> >& data);
void cs170demo(vector<vector<double> >& data);

// FUNCTION DECLARATIONS
double normalize(double n) { // TODO
    return 0;
}

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

double euclidean_distance(const vector<double>& vec1, const vector<double>& vec2) {
    double sum = 0.0;

    for (int i = 0; i < vec1.size(); ++i) {
        sum += pow(vec1[i] - vec2[i], 2);
    }

    return sqrt(sum);
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
                cout << "\tConsidering adding the " << k << " feature" << endl;
                double accuracy = leave_one_out_cross_validation(data, current_set_of_features, k);

                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
            }
        }

        current_set_of_features.push_back(feature_to_add_at_this_level);
        cout << "On level " << (i + 1) << " I added feature " << feature_to_add_at_this_level << " to current set" << endl << endl;
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

void cs170demo(vector<vector<double> >& data) {
    double number_correctly_classified = 0;
    double nearest_neighbor_distance;
    double nearest_neighbor_location;
    int nearest_neighbor_label;
    double distance;
    double accuracy = 0;

    for (int i = 0; i < data.size(); ++i) {
        double label_object_to_classify = data[i][0]; // first column is the label column
        vector<double> object_to_classify(data[i].begin() + 1, data[i].end()); // feature columns

        nearest_neighbor_distance = numeric_limits<double>::infinity();
        nearest_neighbor_location = -1;
        nearest_neighbor_label = -1;
        distance = 0.0;

        for (int k = 0; k < data.size(); ++k) {
            if (i != k) {
                cout << "Ask if " << (i + 1) << " is nearest neighbor with " << (k + 1) << endl;

                vector<double> object_to_compare(data[k].begin() + 1, data[k].end());

                distance = euclidean_distance(object_to_classify, object_to_compare);

                if (distance < nearest_neighbor_distance) {
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = k + 1;
                    nearest_neighbor_label = data[k][0];
                }
            }
        }

        if (label_object_to_classify == nearest_neighbor_label) {
            number_correctly_classified++;
        }

        cout << "Object " << (i + 1) << " is class " << nearest_neighbor_label << endl;
        cout << "Its nearest_neighbor is " << nearest_neighbor_location << " which is in class " << nearest_neighbor_label << endl;
    }

    accuracy = number_correctly_classified / data.size();
}

int main() {
    string file_name;
    double accuracy = 0.0;
    
    cout << "Welcome to Alexander Tran's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: "; 
    cin >> file_name;
    
    vector<vector<double> > dataset = read_dataset(file_name);

    cout << "This dataset has " << (dataset[0].size() - 1) << " features (not including the class attribute), with " << dataset.size() << " instances." << endl;
    cout << "Running nearest neighbor with all " << (dataset[0].size() - 1) << " features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy << '%' << endl;
    cout << endl << "Beginning search." << endl;
    
    feature_search_demo(dataset);

    cout << endl << "Running cs170demo on the dataset:" << endl;
    cs170demo(dataset);

    return 0;
}
