#include "cubeState.cpp"
#include <string>
#include <queue>
#include<unordered_set>
#include <iostream>

std::string solveCube(cubeState,bool(cubeState::*)());

int main(){
	//Storage for inputs
	char cells[6][9];
	char row[4];
	char faceNames[6][7] = { "top", "left", "front", "right", "back", "bottom"};
	char rowNames[3][7] = { "top", "middle", "bottom" };

	//Loop to gather user input
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			printf("Enter %-7s face %-7s row :", faceNames[i], rowNames[j]);
			std::cin >> row;
			cells[i][3*j] = row[0];
			cells[i][3 * j + 1] = row[1];
			cells[i][3 * j + 2] = row[2];
		}
	}
	cubeState initCube = cubeState(cells, "");
	//Solve cross
	std::string crossSln = solveCube(initCube, &cubeState::cross);
	printf(crossSln.c_str());
	return 0;
}


//Hashing struct so states can be inserted into unordered_set
struct hasher {
	size_t operator()(const cubeState& c) const {
		std::string cells = "";
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 9; j++){
				cells += c.cells[i][j];
			}
		}
		return std::hash<std::string>()(cells);
	}
};

//Overloading less than operator so states can be inserted into priority_queue
bool operator<(const cubeState& a, const cubeState& b) {
	return a.getScore() > b.getScore();
}

/// <summary>
/// A* function
/// </summary>
/// <param name="begin"> Initial State of the cube </param>
/// <param name="goal"> pointer to cubeState member function that indicates the desired state </param>
/// <returns></returns>
std::string solveCube(cubeState begin, bool(cubeState::*goal)()) {
	int n = 0;
	//Set up open set & closed set
	char lastMove;
	std::string moves = "UuLlFfRrBbDd";
	std::priority_queue<cubeState> openSet;
	std::unordered_set<cubeState, hasher> closedSet;

	//Set up state variables
	cubeState currentState = begin;
	cubeState newState = currentState;
	openSet.push(currentState);

	while (!openSet.empty()) {
		//Get the 'best' new state and remove from open set
		currentState = openSet.top();
		openSet.pop();
		
		//If the current state is the solved state return moves taken
		if ((currentState.*goal)()) return currentState.getMoves();

		//If state is not in the closed set
		if (closedSet.find(currentState) == closedSet.end()) {
			closedSet.insert(currentState);
			
			lastMove = currentState.getMoves().length()>0 ? currentState.getMoves().back() : '\0';
			//Loop over all possible moves
			for (int i = 0; i < 12; i++) {
				//If new move does not undo previous move (Same letter upper & lowercase)
				if (abs(moves[i]-lastMove)!=32) {
					newState = currentState;
					newState.move(moves[i]);
					if (closedSet.find(newState) == closedSet.end()) openSet.push(newState);
				}
			}

		}
	}
}

