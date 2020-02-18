//Samuel Larson
//program 2
#include <iostream>
#include <fstream>
using namespace std;

//this constant integer holds the size of the array
const int size = 8;

//this function prints a number entered by the user backwards
void backwards(int num);

//this function reads numbers from a file into an array
void readin(int arr[size], ifstream&);

//this function checks the array for a number entered by the user and returns if it was found or not
bool check(int num, int array[size], int pos, bool found);

//this function finds the prime factorization of a number entered by the user and prints it
void primefact(int num);

int main()
{
    int array[size];
    int num;
    bool found = false; //a boolean value to hold whether the program found the number entered by the user in the array
    ifstream infile;
    infile.open("vals.dat");    //the program opens the data file

    cout << "Please enter a number" << endl;    //the program asks the user to enter a number into the terminal
    cin >> num;
    backwards(num); //the program calls the function backwards

    readin(array, infile);

    cout << endl << "Please enter a number" << endl;    //the program asks the user to enter a number to search for
    cin >> num;
    found = check(num, array, size, found); //the program calls the function check
    if(found == false){ //if the function returns false it displays that the number wasn't found
        cout << num << " was not found in the array" << endl;
    }

    cout << "Please enter a positive integer" << endl;  //the program asks the user to enter a number
    cin >> num;
    cout << "The prime factorization is" << endl;
    if(num == 1)
        cout << num;//if the number is 1 it is printed
	else
        primefact(num); //the function primefact is called
    return 0;
}

void backwards(int num){
    if(num < 10)
        cout << num;    //if the number is 1 digit long it prints it and the function returns
    else{
        cout << num%10; //the last digit in the number is printed
        backwards(num/10);  //the last digit is taken off the number and the function gets called
    }
    return;
}

void readin(int array[size], ifstream& infile){

	for(int count = 0; count < size; count++){
        infile >> array[count]; //the function reads the numbers into the array
	}

	return;
}

bool check( int num, int array[size], int pos, bool found){
    if(array[pos] == num){
        found = true;//the number is marked as found in the array and the position is printed out
        cout << num << " was found in position " << pos << " of the array" << endl;
        }
    else if(pos > 0){//if the number hasn't been found it calls the function again to check the next position
        found = check(num, array, pos - 1, found);
    }
    return found;
}

void primefact(int num){
    if(num == 1)//if the number is 1 function returns
        return;
    int factor = 2;
    while(num%factor != 0){  //the function finds the lowest number that can be divided out of the number
        factor++;
    }
    cout << factor << " ";
    primefact(num/factor);  //the function is called again with the number divided by the factor found

    return;
}
