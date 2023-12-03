#include <string>
#include <iostream>
class cubeState{
	public:
		//Constructor
		cubeState(int cells[6][9], std::string moves){
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 9; j++)
					this->cells[i][j] = cells[i][j];
			this->moves = moves;
			score = moves.length() + getDeviation();
		}

		//Accessor for correct path
		std::string getMoves(){
			return moves;
		}

		//Debug Function
		void print() {
			for (int i = 0; i < 6; i++) {
				std::cout << std::endl;
				for (int j = 0; j < 9; j++) {
					if (j % 3 == 0) std::cout << std::endl;
					std::cout << cells[i][j] << " ";
				}
			}
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
			//TODO : Implement moves
			switch(c){
				//Rotate Front Clockwise
				case 'F': {
					spin(2, 1);
					break;
				}
				//Rotate Back Clockwise
				case 'B': {
					spin(5, 1);
					break;
				}
				//Rotate Top Clockwise 
				case 'U': {
					spin(0, 1);
					break;
				}
				//Rotate Bottom Clockwise
				case 'D': {
					spin(4, 1);
					break;
				}
				//Rotate Left Clockwise
				case 'L': {
					spin(1, 1);
					break;
				}
				//Rotate Right Clockwise
				case 'R': {
					spin(2, 1);
					break;
				}
				//Rotate Front CounterClockwise
				case 'f': {
					spin(2, -1);
					break;
				}
				//Rotate Back CounterClockwise
				case 'b': {
					spin(5, -1);
					break;
				}
				//Rotate Top CounterClockwise
				case 'u': {
					spin(0, -1);
					break;
				}
				//Rotate Bottom CounterClockwise
				case 'd': {
					spin(4, -1);
					break;
				}
				//Rotate Left CounterClockwise
				case 'l': {
					spin(1, -1);
					break;
				}
				//Rotate Right Counterclockwise
				case 'r': {
					spin(2, -1);
					break;
				}
			
			}
		}

		//Method to rotate cells on the 4 adjacent faces
		void rotate();

		

		//Equality operator
		bool operator==(const cubeState& other){
			for(int i=0; i<6; i++)
				for(int j=0; j<9; j++)
					if(this->cells[i][j] != other.cells[i][j]) return false;
			return true;
		}

	
	private:
		//Method to rotate a face clocwise/counterclockwise
		void spin(int face, int direction) {
			int temp;
			if (direction == 1) { //Clockwise
				//Rotate Corner cells
				temp = cells[face][0];
				cells[face][0] = cells[face][6];
				cells[face][6] = cells[face][8];
				cells[face][8] = cells[face][2];
				cells[face][2] = temp;

				//Rotate Side cells
				temp = cells[face][1];
				cells[face][1] = cells[face][3];
				cells[face][3] = cells[face][7];
				cells[face][7] = cells[face][5];
				cells[face][5] = temp;
			}
			else if (direction == -1) { //Counterclockwise
				//Rotate Corner cells
				temp = cells[face][0];
				cells[face][0] = cells[face][2];
				cells[face][2] = cells[face][8];
				cells[face][8] = cells[face][6];
				cells[face][6] = temp;

				//Rotate Side cells
				temp = cells[face][1];
				cells[face][1] = cells[face][5];
				cells[face][5] = cells[face][7];
				cells[face][7] = cells[face][3];
				cells[face][3] = temp;
			}
		}

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
};
