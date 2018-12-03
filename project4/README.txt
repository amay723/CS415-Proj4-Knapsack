Elliot Newman && Adam May

To run the c++ code:
> g++ main.cpp && ./a.out

It will prompt you with a question on which numbered test case to run.
Enter in a value 0-9

To run the python code:
> python3 plotter.py

This will take in all of the different text files generated from the different tests run.

Included is the graph from the test cases 0-7 (we ommited 8 and 9 because it messed up the graph too much)
: OutputChart.png
From the data it shows that while dynamic programming is better and finding the best sollutions, the greedy approach was much faster in computing solutions. 


Extra Credit Attempted:

Dynamic Programming space O(2W) mainEX1.cpp: We were able to construct the optimal value for the dynamic programming algorithm by using a table with only 2 rows. Since in the normal algorithm we only need to use two rows at once while building the table while we are scanning down the table. We used this same idea to calculate optimal value. We were not able to figure out the backtracking to find the optimal subset in this case. In our testing (using the files, lcapacity.txt, largew.txt, largev.txt) we noticed that the original algorithm could use up to almost 4 GB of RAM during runtime, and depending on the hardware specs this could cause the program to fail. In our modified version that uses O(2W) space, we saw that at most the program used 1.4 MB of RAM, and even finished a few seconds quicker than the unaltered version, though that is most likely due to not implimenting backtracking. 

Greedy Algorithm mainEX2.cpp: We implimented a min heap in the greedy algorithm that stores the given weight/value/ratio pairs in order in nlogn time. The use of the heap saves us time from sorting the values after they have all been calculated. The final index values for the subsets were also implimented using a min heap, so that those values did not need to be sorted either before printing them out.
