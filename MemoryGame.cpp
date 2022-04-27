#include "MemoryGame.hpp"
#include <cstdlib> //srand, rand
#include <ctime>
#include <iomanip> //setw
#include <iostream> //std
#include <vector>
using namespace std;

int* randomize(int numSpaces); //function to randomize layout
void swap(int* arr, int i, int j);
void displaySeparateLine(int numSpaces);

MemoryGame::MemoryGame() //default constructor, 
{
    srand(time(NULL));
    //different layouts of numbers in different runnings.
    //time(NULL) is the current running time.
    //use the current running time to grow random sequence
    //Since running time differs,
    //the random sequence looks different
    //at different running time.
    srand(1); 

    numPairs=3;
    numSlots=8;


    int* data= new int[numPairs];
    for(int i=0; i<numPairs; i++)
    {
        data[i]=rand() % 1000;
    }


    values= new string[numSlots];
    int* arr= randomize(numSlots);

    for(int i=0; i< numSlots; i++)
    {
        if(i<numPairs*2)
        {
            values[arr[i]]=to_string(data[i/2]);
            values[arr[i+1]]=to_string(data[i/2]);
        }
        else
        {
            values[arr[i]]="";
        }
    }

    delete[] data;
    data=nullptr;
    delete[] arr;
    arr=nullptr;
}

//TODO: implement by students
MemoryGame::~MemoryGame()
{
    //When an object is no longer in need,
    //release dynamically allocated memory by 
    //data members of the current object.
}

//TODO: 
//randomize is not a member function,
//so there is no MemoryGame:: before function name randomize.
//Return an array of randomly allocated 0, 1, .., size-1
//In constructors, randomly assign the data in dataVector 
//to array values
int* randomize(int size)
{
    int *arr = new int[size];
    for(int i = 0;i < size; i++){
        arr[i] = i;
    }
    while(size > 0){
        int index = rand() % size;
        swap(arr,index,size-1);
        size--;
    }

    return arr;
}

//int* arr means int array arr, which implies the address
//of the first element of array arr.
//swap arr[i] and arr[j] in array of ints arr.
void swap(int *arr, int i, int j)
{   
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//Display -----+ for numSlots times.
//Add an extra + when for the first block (when index i is 0).
//So suppose numSlots is 8, we get
//+-----+-----+-----+-----+-----+-----+-----+-----+
//followed by a new line.
void displaySeparateLine(int numSlots)
{
    for (int i = 0; i < numSlots; i++)
    {
        if (i == 0)
           cout << "+";
        cout << "-----+";
    }
    cout << endl;
}


//display the items in values array where bShown is true.
void MemoryGame::display(bool* bShown)
{
    cout << " ";
    for(int i = 0; i < numSlots; i++){
        cout << setw(3) << i;
        cout << setw(3) << " ";
    }
    cout << endl;
    
    displaySeparateLine(numSlots);
    for(int i = 0;i < numSlots; i++){
        if(bShown[i]){
            cout << "|" << setw(5) << values[i];
        }
        else{
            cout << "|" << setw(5) << " ";
        }
    }
    cout << "|";    
    cout << endl;
    displaySeparateLine(numSlots);
}


//rules for a round
//(1) pick a number, flip it
//(2) pick a second number, if the number is the same as
//    previous pick, display the second number,
//    otherwise, unflip the previous pick.
//(3) Finish until every pair are chosen correctly.
void MemoryGame::play()
{   
    bool* bShown = new bool[numSlots];
    for(int i = 0; i < numSlots; i++){
        bShown[i] = false;
    }
    display(bShown);

    int index, first;
    int flips, found = 0;

    while(found < numPairs)
    {
        cout << "Pick a cell to flip: ";
        cin >> index;

        while(index < 0 || index >= numSlots || bShown[index] == true){
            if(index < 0 || index >= numSlots){
                cout << "index needs to be in range [0, " << numSlots << "]." << endl;
            }
            else{
                cout << "The cell indexed at " << index << " is shown." << endl;
            }
            cout << "Re-enter an index: ";
            cin >> index;
        }
        if(flips % 2 == 0){
            bShown[index] = true;
            first = index;
        }
        else{
            if(values[first] == values[index] && values[first] != ""){
                bShown[index] = true;
                found++;
            }
            else{
                bShown[first] = false;
            }
        }
        display(bShown);
        flips++;
    }

    cout << "Congratulations! Take " << flips << " steps to find all matched pairs." << endl;
    
    delete[] bShown;
    bShown = nullptr;
}
