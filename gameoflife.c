/* Code written by Alex Westcott for an assignment at the University of Liverpool in 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Declaring global variables that will be altered by multiple functions*/
int rowNo, colNo, stepNo;

/*Arrays that will contain data about whether cells are dead or alive
One will contain information at the current step, the other will contain information for the next step*/
char *cells;
char *tmpCells;


/*Method used to establish how many neighbours a cell has
Takes the position on the board of the cell as arguments*/
int checkNeighbours(int posX, int posY){
	
	/*Number of neighbours a cell has (default 0)*/
	int neighbourNo = 0;
	
	/*Variables which will be used to make sure cells aren't checked against cells that aren't actually their neighbours*/
	int minX = -1, minY = -1, maxX = 1, maxY = 1;
	
	/*Checks if the cell is either in the first or last row (which would mean they have no neighbours at certain sides)*/
	if(posX == 0){
		minX = 0;
	} else if(posX == rowNo - 1){
		maxX = 0;
	}
	
	/*Similarly, checks if the cell is either in the first or last column on the board*/
	if(posY == 0){
		minY = 0;
	} else if(posY == colNo - 1){
		maxY = 0;
	}
	
	/*For each cell on the board, count the number of 'alive' neighbours
	This is done by checking if the character of the cells surrounding the chosen cell is 'X' (indicating alive cells)*/
	for(int i=minX;i<=maxX;i++){
		for(int j=minY;j<=maxY;j++){
			
			/*Neighbours are checked by using variables i and j as an offset from the chosen cell*/
			if(cells[((posX + i)*colNo) + posY + j] == 'X'){
				
				/*This if statement makes sure the cell doesn't count itself as a neighbour, before incrementing the neighbour count*/
				if(i != 0 || j != 0){
					neighbourNo++;
				}
			}
		}
	}
	
	/*Return the total number of alive neighbours the chosen cell has*/
	return neighbourNo;
	
}

int main(void){
	
	/*Informing the user about how to use the program*/
	printf("Enter the number of rows, the number of columns, and the number of steps to simulate, then press enter\n");
	printf("(i.e. '4 4 10' to simulate a 4x4 board for 10 steps)\n");
	
	/*Take three integers as input, which will be the number of rows/columns on a board, and the number of steps to simulate*/
	scanf("%i%i%i", &rowNo, &colNo, &stepNo);
	
	/*Allocate memory for the board (and the temporary board)
	This is equal to the size of one char element, multiplied by the number of cells on a board*/
	cells = (char*)malloc(rowNo*colNo*sizeof(char));
	tmpCells = (char*)malloc(rowNo*colNo*sizeof(char));
	
	int totalNo = rowNo*colNo;
	
	printf("Now enter either 'X' or '.' %i times, which will be used to represent the default state", totalNo);
	printf("\n'X' represents a live cell, while '.' represents a dead cell");
	printf("\nThe final result of the simulation will be printed to the screen\n");
	
	/*These loops fill out the boards with '.' (to indicate a dead cell) or 'X' (to indicate an alive cell)
	The program will ignore any inputs that are not either '.' or 'X'*/
	for(int i=0;i<rowNo;i++){
		for(int j=0;j<colNo;j++){
			char tmpVar;
			scanf("%c", &tmpVar);
			if(tmpVar == '.' || tmpVar == 'X'){
				cells[(i*colNo) + j] = tmpVar;
			} else {
				j--;
			}
		}
	}
	
	/*For loop that runs through the simulation the number of steps chosen by the user*/
	for(int i=0;i<stepNo;i++){
		for(int j=0;j<rowNo;j++){
			for(int k=0;k<colNo;k++){
				
				/*Call to the checkNeighbours() method, using the current row/column of the cell as arguments
				Will assign the number of neighbours the cell has to the 'neighbours' variable*/
				int neighbours = checkNeighbours(j, k);
				
				/*If statement which firstly checks to see if the current cell is alive or dead*/
				if(cells[(j*colNo) + k] == 'X'){
					
					/*If the cell has too many or too few neighbours, 'kill' the cell
					This is done by putting a 'dead' cell in the temporary cells array*/
					if(neighbours < 2 || neighbours > 3){
						tmpCells[(j*colNo) + k] = '.';
					} else {
						
						/*Otherwise, the cell stays alive*/
						tmpCells[(j*colNo) + k] = 'X';
					}
				} else {
					
					/*If a dead cell has 3 neighbours, the cell can come alive
					This is done by putting an 'alive' cell in the temporary cells array*/
					if(neighbours == 3){
						tmpCells[(j*colNo) + k] = 'X';
					} else {
						
						/*Otherwise the cell remains dead*/
						tmpCells[(j*colNo) + k] = '.';
					}
				}
			}
		}
		
		/*At the end of every step, copy the contents of the temporary array into the main array
		The process will repeat for as many times as the user chose at the start of the program*/
		strncpy(cells, tmpCells, (rowNo*colNo));
	}
	
	/*After all steps have been simulated, print out the contents of the 'cells' array, and exit the program*/
	for(int k=0;k<rowNo;k++){
		for(int m=0;m<colNo;m++){
			printf("%c", cells[(k*colNo) + m]);
		}
		printf("\n");
	}
	
	/*Free the memory that was allocated to both arrays*/
	free(cells);
	free(tmpCells);
	
	return 0;
}