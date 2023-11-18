#include <string>
class cubeState{
	public:
		//Constructor
		cubeState(int cells[6][9], std::string moves){
			for(int i=0; i<6; i++)
				for(int j=0; j<9; j++)
					this->cells[i][j]=cells[i][j]
			this->moves = moves;
			score = moves.Length() + getDeviation();
		}

		//Accessor for correct path
		std::string getPath(){
			return path;
		}
		
		//Method to determine if cube has been solved
		bool isSolved(){
			for(int i=0; i<6; i++)
				for(int j=0; j<9; j++)
					if(cells[i][j]!=cells[i][4]) return false;
			return true;
		}

		//Method to perform move based on input
		void move(char c){
			moves += c;
			switch(c){
				//TODO: implement moves
				case 'F':
				case 'f':
				case 'B':
				case 'b':
				case 'U':
				case 'u':
				case 'D':
				case 'd':
				case 'L':
				case 'l':
				case 'R':
				case 'r':
			}
		}

		//Equality operator
		bool operator==(const cubeState& other){
			for(int i=0; i<6; i++)
				for(int j=0; j<9; j++)
					if(this->cells[i][j] != other.cells[i][j]) return false;
			return true;
		}

	
	private:
		//Distance Heuristic function
		int getDeviation(){
			int deviation =0;
			for(int i=0; i<6; i++)
				for(int j=0; j<9; j++)
					if(cells[i][j]!=cells[i][4]) deviation++;
			return deviation;
		}

		//Private Data Members
		int cells[6][9];
		int score;
		std::string moves;
}
