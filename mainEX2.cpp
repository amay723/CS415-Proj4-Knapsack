#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for sort()
#include <queue>

using namespace std;

void readNums(ifstream &input, vector<int> &nums);
void dynamicOpt(int capacity, vector<int> weights, vector<int> values, ofstream & plots);
void greedyOpt(int capacity, vector<int> weights, vector<int> values, ofstream & plots);

struct Node
{
  Node(int w, int v, int i) { weight = w, value = v; index = i; ratio = (float)value/weight; }
    int weight;
    int value;
    float ratio;

  int index;
};
struct Compare
{
  bool operator() (Node* const & n1, Node* const & n2) { return n1->ratio < n2->ratio; }
};


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


  cout << "\nKnapsack capacity = " << capacity << ". Total number of items = " << values.size() << endl << endl;

  ofstream plots("plots.txt");

  plots << values.size() << endl;

  dynamicOpt(capacity, weights, values, plots);
  cout << endl << endl;
  greedyOpt(capacity, weights, values, plots);


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

void dynamicOpt( int capacity, vector<int> weights, vector<int> values, ofstream & plots ) {

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

  printf("Dynamic Programming Time Taken: %.6fs\n", (double)(finish-start)/CLOCKS_PER_SEC);

  plots << (double)(finish-start)/CLOCKS_PER_SEC << endl;


}


void greedyOpt(int capacity, vector<int> weights, vector<int> values, ofstream & plots) {

  double start = clock();

  priority_queue<Node*, vector<Node*>, Compare> q;

  for( int i = 0; i < values.size(); i++ ) {
    Node * n = new Node(weights[i], values[i], i+1);
    q.push( n );
  }

  
  // Scan through our descending order ratio pairs and perform the greedy approach
  int optvalue = 0;
  priority_queue<int, vector<int>, greater<int>> optSubset;

  while( ! q.empty() ) {

    Node * temp = q.top();
    q.pop();

    // exit case for greedy search
    if( capacity - temp->weight < 0 )
      break;

    optSubset.push( temp->index );
    optvalue += temp->value;
    capacity -= temp->weight;

    delete temp;
    
  }
  

  double finish = clock();

  cout << "Greedy Approach Optimal value: " << optvalue << endl;
  cout << "Greedy Approach Optimal subset: {";
  if( optSubset.size() > 0 ) {
    cout << optSubset.top();
    optSubset.pop();
  }
  while( ! optSubset.empty() ) {
    cout << ", " << optSubset.top();
    optSubset.pop();
  }
  cout << '}' << endl;
  
  printf("Greedy Approach Time Taken: %.6fs\n", (double)(finish-start)/CLOCKS_PER_SEC);

  plots << (double)(finish-start)/CLOCKS_PER_SEC << endl;
  
}
