#include <string>
#include <iostream>
class cubeState{
	public:
		//Constructor
		cubeState(char cells[6][9], std::string moves){
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

		//Accessor for score
		int getScore() {
			return score;
		}

		//Debug Function
		void print() {
			for (int i = 0; i < 6; i++) {
				std::cout << std::endl;
				for (int j = 0; j < 9; j++) {
					if (j % 3 == 0) std::cout << std::endl;
					std::cout << (int)cells[i][j] << " ";
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
			switch(c){
				//Rotate Top Clockwise 
				case 'U': {
					spin(Up, 1);
					break;
				}
				//Rotate Left Clockwise
				case 'L': {
					spin(Left, 1);
					break;
				}
				//Rotate Front Clockwise
				case 'F': {
					spin(Front, 1);
					break;
				}
				//Rotate Right Clockwise
				case 'R': {
					spin(Right, 1);
					break;
				}
				//Rotate Back Clockwise
				case 'B': {
					spin(Back, 1);
					break;
				}
				//Rotate Bottom Clockwise
				case 'D': {
					spin(Down, 1);
					break;
				}
				//Rotate Top CounterClockwise
				case 'u': {
					spin(Up, -1);
					break;
				}
				//Rotate Left CounterClockwise
				case 'l': {
					spin(Left, -1);
					break;
				}
				//Rotate Front CounterClockwise
				case 'f': {
					spin(Front, -1);
					break;
				}
				//Rotate Right Counterclockwise
				case 'r': {
					spin(Right, -1);
					break;
				}
				//Rotate Back CounterClockwise
				case 'b': {
					spin(Back, -1);
					break;
				}
				//Rotate Bottom CounterClockwise
				case 'd': {
					spin(Down, -1);
					break;
				}
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
		//Method to rotate a face clockwise/counterclockwise
		void spin(int face, int direction) {
			char temp;
			rotate(face, direction);
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

		//Method to rotate cells adjacent to a face clockwise/counterclockwise
		void rotate(int face, int direction) {
			char temp;
			//Determine adjacencent faces and specific cells within those faces
			switch (face) {
			case Up: {
				int faces[4] = { Back, Right, Front, Left };
				int cellsToSwap[4][3] = { {2,1,0}, {2,1,0}, {2,1,0}, {2,1,0} };
				swapCells(faces, cellsToSwap, direction);
				break;
			}
			case Left: {
				int faces[4] = { Up, Front, Down, Back};
				int cellsToSwap[4][3] = { {0,3,6}, {0,3,6}, {0,3,6}, {8,5,2} };
				swapCells(faces, cellsToSwap, direction);
				break;
			}
			case Front: {
				int faces[4] = { Up, Right, Down, Left};
				int cellsToSwap[4][3] = { {6,7,8}, {0,3,6}, {2,1,0}, {8,5,2} };
				swapCells(faces, cellsToSwap, direction);
				break;
			}
			case Right: {
				int faces[4] = { Up, Back, Down, Front};
				int cellsToSwap[4][3] = { {8,5,2}, {0,3,6}, {8,5,2}, {8,5,2} };
				swapCells(faces, cellsToSwap, direction);
				break;
			}
			case Back: {
				int faces[4] = { Up, Left, Down, Right};
				int cellsToSwap[4][3] = { {2,1,0}, {0,3,6}, {6,7,8}, {8,5,2} };
				swapCells(faces, cellsToSwap, direction);
				break;
			}
			case Down: {
				int faces[4] = { Front, Right, Back, Left};
				int cellsToSwap[4][3] = { {6,7,8}, {6,7,8}, {6,7,8}, {6,7,8} };
				swapCells(faces, cellsToSwap, direction);
				break;
			}
			}
			
		}

		//Method to swap 12 specified cells from 4 specified faces
		void swapCells(int faces[4], int cellsToSwap[4][3], int direction) {
			char temp;
			//Rotate 4 "groups" of cells
			if (direction == 1) {
				for (int i = 0; i < 3; i++) {
					temp = cells[faces[0]][cellsToSwap[0][i]];
					cells[faces[0]][cellsToSwap[0][i]] = cells[faces[3]][cellsToSwap[3][i]];
					cells[faces[3]][cellsToSwap[3][i]] = cells[faces[2]][cellsToSwap[2][i]];
					cells[faces[2]][cellsToSwap[2][i]] = cells[faces[1]][cellsToSwap[1][i]];
					cells[faces[1]][cellsToSwap[1][i]] = temp;
				}
			}
			else if (direction == -1) {
				for (int i = 0; i < 3; i++) {
					temp = cells[faces[0]][cellsToSwap[0][i]];
					cells[faces[0]][cellsToSwap[0][i]] = cells[faces[1]][cellsToSwap[1][i]];
					cells[faces[1]][cellsToSwap[1][i]] = cells[faces[2]][cellsToSwap[2][i]];
					cells[faces[2]][cellsToSwap[2][i]] = cells[faces[3]][cellsToSwap[3][i]];
					cells[faces[3]][cellsToSwap[3][i]] = temp;
				}
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
		char cells[6][9];
		enum { Up, Left, Front, Right, Back, Down }; //Enum to help identify faces in cells array
		int score;
		std::string moves;
};
