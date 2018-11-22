#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readNums(ifstream &input, vector<int> &nums);
void dynamicOpt(int capacity, vector<int> weights, vector<int> values);

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


  cout << "\nKnapsack capacity = " << capacity << ". Total number of items = " << values.size() << endl;

  dynamicOpt(capacity, weights, values);


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
