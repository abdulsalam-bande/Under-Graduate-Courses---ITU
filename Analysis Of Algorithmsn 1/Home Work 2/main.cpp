//
//  main.cpp
//  Home_work2
//
//  Created by Abdulsalam Yazid on 19.10.2017.
//  Copyright © 2017 Abdulsalam Yazid. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <math.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>



// we first create a data structure using struct
struct Residence{
    
public:
    int Population;
    string minAge;
    string maxAge;
    string gender;
    int zipCode;
    string geo_id;
    
};

// we create a method to compare residences to know which one is should appear first
// first the population of two addresses is compare, if the address are the same then there geo_id checked
bool ResidenceComparer(Residence* card1,Residence* card2){
    bool holder = false;
    if(card1->Population < card2->Population)
        holder = true;
    if (card1 -> Population == card2 -> Population  ) {
        if(card1->geo_id < card2->geo_id)
            holder = true;
    }
    
    return holder;
    
    
}
int partition (Residence* arr, int low, int high)
{
    
    Residence pivot = arr[high]; //our pivot element
    
    
    int i = (low - 1);  // the first index
    
    for (int j = low; j <= high- 1; j++)
    {
      
        if (ResidenceComparer(&arr[j],&pivot)==true)   // we compare two residence
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

//out recursive quick sort
void quickSort(Residence* arr, int l, int h)
{

    if (l < h)
    {
        
        int pi = partition(arr, l, h);
        quickSort(arr, l, pi - 1);
        quickSort(arr, pi + 1, h);
    }

}

int main(int argc, const char * argv[]) {
    
    string  numberOfResidence1 = argv[1];
    // int numberOfResidence = 1000000;
    int numberOfResidence = atoi(numberOfResidence1.c_str());;
    int N =numberOfResidence+2;
    cout << "Please wait....."<< endl;
  
    
    string  inputFileName = "population_by_zip_2010.csv";  //youtext file
    string  outputFileName = "sortedPopulation.txt";
    int lineNo = 1;
    std::string linee;
    std::ifstream myfile(inputFileName);
    while (std::getline(myfile, linee)) {
        ++lineNo;
        if(lineNo==N){
            break;
        }
    }
    lineNo = lineNo-1;

    
    
    
    
    
    std:: string line;
    
    ifstream myFile(inputFileName);
    
    // an object of my cardManager class
    Residence* my_Residence = new Residence[lineNo];
    
    int numberOfIdexes = (lineNo*6)+1;
    string* arr = new string[numberOfIdexes];
    
    
    
    
    //reading the items from the file, and putting them in an array, then later to my object
    std::stringstream linestream(line);
    char delimeter=(',');
    int index = 1;
    while(getline(myFile,line,delimeter) && !myFile.eof()) {
        
        
        arr[index]=line;
        ++index;
        if(index%6==0)
            delimeter=('\n');
        else
            delimeter=(',');
        if(index==numberOfIdexes){
            break;
        }
    }
    myFile.close();
    
    int i =7;
    index = 1;
    while(i <numberOfIdexes ){
        my_Residence[index].Population =atoi(arr[i].c_str());
        ++i;
        my_Residence[index].minAge =arr[i];
        ++i;
        my_Residence[index].maxAge =arr[i];
        ++i;
        my_Residence[index].gender =arr[i];
        ++i;
        my_Residence[index].zipCode =atoi(arr[i].c_str());
        ++i;
        my_Residence[index].geo_id = arr[i];
        ++index;
        i++;
       
        
    }
    delete[] arr;
    
    
    
    // here we time and call the quicksort
    {
        clock_t start = clock();
        quickSort(my_Residence,1,lineNo-1);
        clock_t end = clock();
        double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
        cout << "Time elapsed: " << elapsed_time << " SECONDS " << endl;
        
    }

    
    // we create an output
    ofstream outfile2(outputFileName);
    
    for (int i = 1; i <lineNo; i++)
    {
        outfile2 << my_Residence[i].Population << "," << my_Residence[i].minAge << "," << my_Residence[i].maxAge << ","<< my_Residence[i].gender << "," << my_Residence[i].zipCode << "," <<my_Residence[i].geo_id <<endl;;
    }
    outfile2.close();
    
    cout<<"Succesful\n";
    
    
    
    

    
    
    
    
    
}

