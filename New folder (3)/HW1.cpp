#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>  // for printing the Sudoku in nice format 
// using setw
using namespace std;


typedef vector<vector<int> > State;
typedef vector<State> Path;
Path goals;
Path start;
Path path;


void build_Graph() {
	start.push_back({ { { 6, -1, -1, -1,  3, -1, -1,  2, -1}, 	
                		{-1,  4, -1, -1, -1,  8, -1, -1, -1}, 	
                		{ 8,  5, -1,  2,  7, -1,  1, -1, -1}, 	
                	  	{ 3, -1, -1, -1, -1, -1,  6,  7, -1},
                	  	{-1, -1, -1, -1,  2, -1, -1, -1, -1},
                	  	{-1,  6,  1, -1, -1, -1, -1, -1,  5},
                	  	{-1, -1,  4, -1,  1,  9, -1,  8,  3},
                	  	{-1, -1, -1,  4, -1, -1, -1,  1, -1},
					{-1,  8, -1, -1,  5, -1, -1, -1,  6}
			} }); 
}

bool isGoal(State s) {
     // Two for loops to compare every element in the matrix  
     // parameter s with -1
	 for(unsigned int i=0; i<9; i++)
		 for(unsigned int j=0; j<9; j++)
			 if (s[i][j] == -1)
				 return false; 
	return true;
}

bool exist (int n, vector<vector<int> > v, int r, int c) {
	// one for loop to search the number n in the row r of v
     // and the column c of v
	 for(unsigned int i=0 ;i<9; i++){
		 if (v[r][i] == n)
			 return true;
		 if(v[i][c] == n)
			 return true;
	 }
		
     // search inside the corresponding 3x3 square matrix:
     int x = r / 3 * 3;
     int y = c / 3 * 3;
     // two for loops to search for repeated number n in the
     // 3x3 square matrix.
	for(int i=x;i<x+2;i++)
		for(int j=y;j<y+2;j++)
		if(v[i][j] ==n)	
			return true;

     return false;
}


Path getNeighbors(State s) {
    // Two for loops, one for row and one for column
    // to search for empty square (that is -1 in 
    // matrix s.b). 
    // if you find a square with -1 then
    // use for loop to choose numbers from 1-9 digit such that
    // no number exist in the same row and column and
    // corresponding 3x3 matrix. 
    // skeleton of the code is as follows:

    Path neighbors;
    for (int r=0; r<9; r++)
       for (int c=0; c<9; c++) // These two loops for searching 
          if (s[r][c] == -1) {// for -1 square
            	for (int i=1; i<10; i++) {
                	if (exist(i, s, r, c)) continue;
                	s[r][c] = i;
                	neighbors.push_back(s);
                    s[r][c] = -1;
            	}
   			if (neighbors.size() > 0) return neighbors;
   			else return {};
   		}
   return {};
}

void displayState(State s) {
     // use two for loops to display s.b, that would be the 
            // solution.
for (int i=0; i<9; i++) {
	for (int j=0; j<9; j++)
		cout << setw(3) << s[i][j];
     cout << endl;
}
}

void display(Path temp) {
     if (temp.size() == 0) {
         cout << "Goal not found\n";
         return;
     }
	displayState(temp.back());
}

Path search() {
	queue<Path> frontier;
	Path temp;
	State currentState, newState;
	int depth = 0;
	
	frontier.push(start);
	
	while (!frontier.empty()) {
		temp = frontier.front();
		frontier.pop();
		
		currentState = temp[temp.size()-1];
		if (temp.size() - 1 > depth) {
			depth++;
			cout << depth << endl;
		}
		//displayState(currentState);
		//getchar();
		if (isGoal(currentState)) return temp;
		//if (isExplored(currentState)) continue;
		//explored.push_back(currentState);
				
		Path neighbors = getNeighbors(currentState);
		
		for (unsigned int i=0; i<neighbors.size(); i++) {	
			//if (isExplored(neighbors[i])) continue;
			temp.push_back(neighbors[i]);
			frontier.push(temp);
			temp.pop_back();
		}
		
	}
	temp.clear();
	return temp;
}

int main() {
	build_Graph();
	path = search();
	display(path);
	return 0;
}
