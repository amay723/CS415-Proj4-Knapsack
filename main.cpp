#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for sort()

using namespace std;

void readNums(ifstream &input, vector<int> &nums);
void dynamicOpt(int capacity, vector<int> weights, vector<int> values);
void greedyOpt(int capacity, vector<int> weights, vector<int> values);

int main() {

  // Get capacity file
  cout << "Enter file containing the capacity: ";
  string filename;
  cin >> filename;

  ifstream capinput(filename);

  while( ! capinput.is_open() ) {
    cout << "Error, invalid filename. Enter a valid capacity file: ";
    cin >> filename;
    capinput.open(filename);
  }

  // Get weights file
  cout << "Enter file containing the weights: ";
  cin >> filename;

  ifstream weightinput(filename);

  while( ! weightinput.is_open() ) {
    cout << "Error, invalid filename. Enter a valid weight file: ";
    cin >> filename;
    weightinput.open(filename);
  }

  // Get values file
  cout << "Enter file containing the values: ";
  cin >> filename;

  ifstream valinput(filename);

  while( ! valinput.is_open() ) {
    cout << "Error, invalid filename. Enter a valid value file: ";
    cin >> filename;
    valinput.open(filename);
  }


  // Read capacity from file and store in variable
  string temp;
  getline(capinput, temp);
  int capacity = stoi(temp);


  // Read values and weights & store them
  vector<int> weights;
  readNums(weightinput, weights);
  vector<int> values;
  readNums(valinput, values);


  cout << "\nKnapsack capacity = " << capacity << ". Total number of items = " << values.size() << endl << endl;;

  dynamicOpt(capacity, weights, values);
  cout << endl << endl;
  greedyOpt(capacity, weights, values);


  return 0;
}

void readNums(ifstream &input, vector<int> & nums) {

  string temp;

  getline(input, temp);

  while( ! input.eof() ) {
    nums.push_back( stoi(temp) );
    getline(input, temp);
  }


}

void dynamicOpt( int capacity, vector<int> weights, vector<int> values ) {

  double start = clock();

  int valueSize = values.size()+1;
  int capSize = capacity + 1;

  // Initialize table
  int ** table = new int*[valueSize];

  for( int i = 0; i < valueSize; i++ ) {
    table[i] = new int[capSize];
  }

  // Fill table with optimal values
  for( int i = 1; i < valueSize; i++ ) {
    for( int j = 1; j < capSize; j++) {
      if( j - weights[i-1] >= 0 )
	table[i][j] = max(table[i-1][j], values[i-1] + table[i-1][j-weights[i-1]]);
      else
	table[i][j] = table[i-1][j];
    }
  }


  // backtrace
  vector<int> optSubset;
  int i = valueSize -1;
  int j = capacity;
  while( i > 0 ) {
    if( table[i][j] > table[i-1][j] ) { // if value i is used in the optimal subset
      optSubset.push_back(i);
      j -= weights[i-1];
      i--;		   
    }
    else
      i--;    
  }

  double finish = clock();
  
  cout << "Dynamic Programming Optimal value: " << table[valueSize-1][capacity] << endl;
  cout << "Dynamic Programming Optimal subset: {";
  if( optSubset.size() > 0 )
    cout << optSubset[optSubset.size()-1];
  for( int i = optSubset.size()-2; i >= 0; i--)
    cout << ", " << optSubset[i];
  cout << '}' << endl;
  cout << "Dynamic Programming Time Taken: " << (double)(finish-start)/CLOCKS_PER_SEC << endl;


}


void greedyOpt(int capacity, vector<int> weights, vector<int> values) {

  double start = clock();

  // Used index vector will mark which pairs have already been used when finding the best ratio
  vector<bool> usedIndex;
  usedIndex.resize(weights.size());

  // This will store the index of the best ratios we find in their descending order
  vector<int> optIndex;

  float maxratio = -1;
  int index = 0;

  // Build descending order ratio list
  while( optIndex.size() < values.size() ) { // While we have not looked through all the pairs

    // Find best current max ratio
    for( int i = 0; i < values.size(); i++ ) {

      if( usedIndex[i] == false ) { // if we have not already used this pair 
	float tmpratio = (float)values[i]/weights[i];
	if( tmpratio > maxratio ) {
	  maxratio = tmpratio;
	  index = i;
	}
      }
      // else, skip
      
    }

    optIndex.push_back( index );
    usedIndex[index] = true;

    maxratio = -1; // reset maxratio
    index = 0;     // reset index
    

  }


  // Scan through our descending order ratio pairs and perform the greedy approach
  int optvalue;
  vector<int> optSubset;

  for( int i = 0; i < optIndex.size(); i++ ) {

    if( capacity - weights[ optIndex[i] ] >= 0 ) {
      optSubset.push_back( optIndex[i] +1 );
      optvalue += values[ optIndex[i] ];
      capacity -= weights[ optIndex[i] ];
    }
    else // If we find an item that would take our knapsack over capacity, we quit
      break;
   
  }
  
  sort(optSubset.begin(), optSubset.end());

  double finish = clock();

  cout << "Greedy Approach Optimal value: " << optvalue << endl;
  cout << "Greedy Approach Optimal subset: {";
  if( optSubset.size() > 0 )
    cout << optSubset[0];
  for( int i = 1; i < optSubset.size(); i++)
    cout << ", " << optSubset[i];
  cout << '}' << endl;
  cout << "Greedy Approach Time Taken: " << (double)(finish-start)/CLOCKS_PER_SEC << endl;
  
}
