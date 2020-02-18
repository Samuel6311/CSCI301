//Samuel Larson
//Project 1
#include <iostream>
#include <fstream>
using namespace std;

const int size = 9; //height and width of a sudoku puzzle

//this function reads in the solution of the sudoku puzzle from the .dat file and puts it in a 2d array
void readin(int arr[][size], ifstream&);

//this function takes in the 2d array prints the sudoku puzzle to the screen
void print(int arr[][size]);

//this function checks if the sudoku puzzle solution is possible
void check(int arr[][size]);

int main()
{
	int solution[size][size]; //creates a 9x9 array

	ifstream infile;
	infile.open("m3.dat");	//opens the file m1.dat to take in information

	readin(solution, infile); //calls the readin function
	print(solution);		  //calls the print function
	check(solution);		  //calls the check function

	 infile.close();

	return 0;
}

void readin(int array[][size], ifstream& infile){
	int countx, county;
	for(int countx=0; countx < size; countx++){
		for(int county=0; county < size; county++){
			infile >> array[countx][county];
		}
	}
	return;
}

void print(int array[][size]){
	int countx, county;
	for(int countx=0; countx < size; countx++){
		for(int county=0; county < size; county++){
			cout << array[countx][county] << " ";
		}
		cout << endl;
	}
	return;
}

void check(int array[][size]){
	int count, countx, county;
	bool possible = true;
	int unique[size];
	//this loop checks if the number is between 1 and 9
	for(int countx=0; countx < size; countx++){
		for(int county=0; county < size; county++){
		if(array[countx][county] > 9 || array[countx][county] < 1)
			possible = false;
		}
	}

//these loops checks if the numbers in the rows are unique
		if(possible == true){
			for(int countx=0; countx < size; countx++){
				for(int count=0; count < size + 1; count++){
					unique[count] = 0;
				}
				for(int county=0; county < size; county++){
					//cout << array[countx][county];
					unique[array[countx][county]]++;

					if(unique[array[countx][county]] > 1)
						possible = false;
				}
			}
		}

//these loops checks if the numbers in the columns are unique
	if(possible == true){
		for(int county=0; county < size; county++){
			for(int count=0; count < size + 1; count++){
				unique[count] = 0;
			}
			for(int countx=0; countx < size; countx++){
				unique[array[countx][county]]++;

				if(unique[array[countx][county]] > 1)
					possible = false;
			}
		}
	}

//these loops checks if the numbers in the regions are unique
	int rsize = 3, startx = 0, starty = 0;

	while(startx < size){
		while(starty < size){
		for(int count=0; count < size + 1; count++){
				unique[count] = 0;
			}
		countx = startx;
			while(countx < startx + 3){
				county = starty;
				while(county < starty + 3){
					unique[array[countx][county]]++;
					if(unique[array[countx][county]] > 1)
						possible = false;
					county++;
				}
				countx++;
			}
			starty = starty + 3;
		}
		startx = startx + 3;
	}
	cout << endl << "is ";

	if(possible == false)
		cout << "NOT ";

	cout << "a Sudoku solution." << endl;

	return;
}

