/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>  
#include <string>

using namespace std;

void readNums(ifstream & input, vector<int> & nums);
void dynamicOpt( int capacity, vector<int> weights, vector<int> values );

int main()
{
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
    
    string temp;
    getline(capinput, temp);
    int capacity = stoi(temp);
    
    vector<int> weights;
    readNums(weightinput, weights);
    vector<int> values;
    readNums(valinput, values);
    
    cout << "\nKnapsack capacity = " << capacity << ". Total number of items = " << values.size() << endl << endl;
    
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

    int capSize = capacity + 1;
    
    // Initialize table
    int ** table = new int*[2];
    
    for( int i = 0; i < 2; i++ ) {
      table[i] = new int[capSize];
    }

    
    for( int i = 0; i < values.size(); i++ ) {
      
        for( int j = 1; j < capSize; j++ ) {
            if( j - weights[i] >= 0 )
	      table[1][j] = max(table[0][j], values[i] + table[0][j-weights[i]]);
            else
	      table[1][j] = table[0][j];
        }


	      // Shift rows up/reset
        if( i != values.size() -1 ) {
            for(int i = 0; i < capSize; i++) {
                table[0][i] = table[1][i];
            }
        }
      
  }

  double finish = clock();
  
  cout << "opt value = " << table[1][capSize-1] << endl;

  printf("Dynamic Programming Time Taken: %.6fs\n", (double)(finish-start)/CLOCKS_PER_SEC);
 

}
