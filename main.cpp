#include "cubeState.cpp"
#include <string>
#include <queue>
#include<unordered_set>

std::string solveCube(char[6][9]);

int main(){
	char cells[6][9] = {
		{'y','y','y','y','y','y','y','y','y'},
		{'r','r','r','g','g','g','g','g','g'},
		{'g','g','g','o','o','o','o','o','o'},
		{'o','o','o','b','b','b','b','b','b'},
		{'b','b','b','r','r','r','r','r','r'},
		{'w','w','w','w','w','w','w','w','w'},
	};
	std::cout << solveCube(cells);
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

//A* Algorithm
std::string solveCube(char cells[6][9]) {
	int n = 0;
	//Set up open set & closed set
	char lastMove;
	std::string moves = "UuLlFfRrBbDd";
	std::priority_queue<cubeState> openSet;
	std::unordered_set<cubeState, hasher> closedSet;

	//Set up state variables
	cubeState currentState(cells, "");
	cubeState newState = currentState;
	openSet.push(currentState);

	while (!openSet.empty()) {
		//Get the 'best' new state and remove from open set
		currentState = openSet.top();
		openSet.pop();
		
		//If the current state is the solved state return moves taken
		if (currentState.isSolved()) return currentState.getMoves();

		//If state is not in the closed set
		if (closedSet.find(currentState) == closedSet.end()) {
			closedSet.insert(currentState);
			
			lastMove = currentState.getMoves().length()>0 ? currentState.getMoves().back() : '\0';
			//Loop over all possible moves
			for (int i = 0; i < 12; i++) {
				if (moves[i] != lastMove) {
					newState = currentState;
					newState.move(moves[i]);
					if (closedSet.find(newState) == closedSet.end()) openSet.push(newState);
				}
			}

		}
	}
}

