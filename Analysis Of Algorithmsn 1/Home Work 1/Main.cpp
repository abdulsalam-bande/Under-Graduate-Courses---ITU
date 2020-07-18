//
//  main.cpp
//  Home2a
//string name ;

//  Created by Abdulsalam Yazid on 23/08/2017.
//  Copyright © 2017 Abdulsalam Yazid. All rights reserved.
//

//
//  main.cpp
//  merge,insertion sorts
//
//  Created by Abdulsalam Yazid on 12/12/16.
//  Copyright © 2016 Abdulsalam Yazid. All rights reserved.
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


//my class
//the class has six public attributes
class CardManager{
    
public:
    string name;
    string classy;
    string rarity;
    string set;
    string type;
    int cost;

};

// a method for comparing Cardmanager Objects
// it returns true if  the the first argument is less than the second
bool CardComparer(CardManager* card1,CardManager* card2){
    bool holder = false;
    if(card1->classy < card2->classy)
        holder = true;
    if (card1 -> classy == card2 -> classy  ) {
        if(card1->cost < card2->cost)
             holder = true;
        if(card1 -> cost == card2 -> cost){
            if(card1->name < card2->name)
                holder = true;

        }
    }
        
    return holder;
    
        
}


//NOTE: 1.The merge and merge_Sort methods where created with the help of the Pseudo codes from the class
//      2.The merge and mergesort below are only full sort
//my merge sort of merge_sort1 methods for a full sort
//
void merge1(CardManager* arr,int p,int q,int r){
        int i,j,k;
   
//lets calculate the number of elements we will put in A left and Right cardmanager Objects
    int n1 = q - p + 1;
    int n2 =  r - q;
    
  // we create two objects of cardmanger to help in out operations.
    CardManager* L = new CardManager[n1];
    CardManager* R = new CardManager[n2];
    
//lets fill out left and right objects with elements
    for (i = 0; i < n1; i++)
         L[i]= arr[p + i];
    for (j = 0; j < n2; j++)
         R[j] = arr[q + 1+ j];
    i = 0;
    j = 0;
    k = p;
    
// the below while-loop is the heart of merge sort, it compares elements in the left and Right Cardmanger objects
    while (i < n1 && j < n2)
    {
        if (CardComparer(&L[i],&R[j]) == true)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
//after we finish with our operations ,we will take the ramaaining elements in L and R to arr
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
 //after we finish with our operations ,we will take the ramaaining elements in L and R to arr
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    
  
}

//NOTE: the merge_sort below was inpired by the psedocode in the class
void merge_sort1(CardManager* arr, int p, int r)
{
    if (p < r)
    {
        int m = p+(r-p)/2;
        
        merge_sort1(arr, p, m);
        merge_sort1(arr, m+1, r);
        
        merge1(arr, p, m, r);
    }
}

// Now lets look at merge-sort for filter-sort
//we start by creating a function that compares manager card objects

bool CardComparer2(CardManager* card1,CardManager* card2){
    bool holder = false;
    if(card1->type <= card2->type)
        holder = true;
    
    
    return holder;
    
    
}
//NOTE: 1.The merge2 and merge_Sort2 methods where created with the help of the Pseudo codes from the class
//      2.The merge2 and mergesort2 below are only filter sort
//my merge sort of merge_sort1 method for a filter sort
void merge2(CardManager* arr,int p,int q,int r){
    int i,j,k;
    
    //lets calculate the number of elements we will put in A left and Right cardmanager Objects
    int n1 = q - p + 1;
    int n2 =  r - q;
    
    
     // we create two objects of cardmanger to help in out operations.
    CardManager* L = new CardManager[n1];
    CardManager* R = new CardManager[n2];
    
    for (i = 0; i < n1; i++)
        L[i]= arr[p + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[q + 1+ j];
    i = 0;
    j = 0;
    k = p;
    
    // the below while-loop is the heart of merge sort, it compares elements in the left and Right Cardmanger objects
    while (i < n1 && j < n2)
    {
        if (CardComparer2(&L[i],&R[j]) == true)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    
}
//NOTE: the merge_sort below was inpired by the psedocode in the class
void merge_sort2(CardManager* arr, int p, int r)
{
    if (p < r)
    {
        int m = p+(r-p)/2;
        
        
        merge_sort2(arr, p, m);
        merge_sort2(arr, m+1, r);
        
        merge2(arr, p, m, r);
    }
}


// the insertion-sort1 below is for full sort .By the way insertion sort is a slow algo
// :(

void insertion_sort1 (CardManager* arr, int length){
    //code for classy
     int t;
    
    for (int i = 1; i <= length; i++){
        t = i;
        
        while (t > 1 ){
// in this while loop, we first check for class of two objects, if card "a" is less than b we swap them or else we check their cose and so on
            if(arr[t].classy < arr[t-1].classy)
                std::swap(arr[t],arr[t-1]);
                if(arr[t].classy == arr[t-1].classy){
                    if (arr[t].cost < arr[t-1].cost)
                         std::swap(arr[t],arr[t-1]);
                        if(arr[t].cost == arr[t-1].cost){
                            if(arr[t].name < arr[t-1].name)
                                 std::swap(arr[t],arr[t-1]);
                            
                        }
                            
                    
                }
            
            t--;
        }
    }

}


// the insertion-sort2 below is for filter sort

void insertion_sort2 (CardManager* arr, int length){
  
    int j;
    
    for (int i = 0; i < length; i++){
        j = i;
        
        while (j > 0 && arr[j].type < arr[j-1].type){
                std::swap(arr[j],arr[j-1]);
         j--;
                    
                }
        
        
        
    }
    
}

// the methods below help me select any type of algorigthm I want ,whether full or filter, the methods also print elapsed times


 void  full(CardManager* my_CardManager,int lines ,string whichSort ){
     if(whichSort == "-i"){
          clock_t start = clock();
        insertion_sort1(my_CardManager, lines );
         clock_t end = clock();
         double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
         cout << "Time elapsed: " << elapsed_time << " SECONDS " << endl;
     }
     if(whichSort == "-m"){
          clock_t start = clock();
        merge_sort1(my_CardManager,0, lines );
         clock_t end = clock();
         double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
         cout << "Time elapsed: " << elapsed_time << " SECONDS " << endl;

     }
}

void  filter(CardManager* my_CardManager,int lines,string whichSort ){
    if(whichSort == "-i"){
        clock_t start = clock();
       insertion_sort2(my_CardManager,lines);
        clock_t end = clock();
        double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
        cout << "Time elapsed: " << elapsed_time << " SECONDS " << endl;
    }
    if(whichSort == "-m"){
        clock_t start = clock();
        merge_sort2(my_CardManager,1, lines );
        clock_t end = clock();
        double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
        cout << "Time elapsed: " << elapsed_time << " SECONDS " << endl;
    }
}


int main(int argc,const char* argv[])
{
    
//command line arguments
   string fullOrfilter = argv[1];  // -full or filter
    string whichSort =   argv[2];   // -m or -i
   string  inputFileName = argv[3];  //youtext file
    string  outputFileName = argv[4];   //your output file

    
     //IMPORTANT NOTE: ,uncomment the argumets below then comment the upper command line arguments if you want to run the program here.After that ,select the desired kind of sort with the input and ouput files.
    
  //  string fullOrfilter = "-filter";  // -full or filter
  //  string whichSort =   "-i" ;  // -m or -i
  //  string  inputFileName = "hs-set-10k.txt";  //youtext file
   // string  outputFileName = "output.txt";

    
//finding number of lines a  file
    int lineNo = 0;
    std::string linee;
    std::ifstream myfile(inputFileName);
    while (std::getline(myfile, linee))
        ++lineNo;
 
    
    
    std:: string line;
    int index = 1;
    ifstream myFile(inputFileName);
 
// an object of my cardManager class
    CardManager* my_CardManager = new CardManager[lineNo];
    
    int numberOfIdexes = 6*lineNo;
    string* arr = new string[numberOfIdexes];
    

    
 //reading the items from the file, and putting them in an array, then later to my object
    std::stringstream linestream(line);
    char delimeter=('\t');
    while(getline(myFile,line,delimeter) && !myFile.eof()) {
        arr[index]=line;
        ++index;
        if(index%6==0)
            delimeter=('\n');
        
        else
            delimeter=('\t');
        if(index==numberOfIdexes){
            break;
        }
        
    }
    
    
    myFile.close();
    
   
    
    int i =1;
    index = 1;
    while(i < numberOfIdexes){
        my_CardManager[index].name =arr[i];
        ++i;
        my_CardManager[index].classy =arr[i];
        ++i;
        my_CardManager[index].rarity =arr[i];
        ++i;
        my_CardManager[index].set =arr[i];
        ++i;
        my_CardManager[index].type =arr[i];
        ++i;
        my_CardManager[index].cost = atoi(arr[i].c_str());
        ++index;
        i++;
    }
    
    delete[] arr;
    
  
    
// depending on you parameter , full or filter sort is selected
 if (fullOrfilter == "-full"){
    full(my_CardManager,lineNo,whichSort);
 }
    
     if (fullOrfilter == "-filter"){
     filter(my_CardManager,lineNo,whichSort);
      
    }


      
//here I print to another file
    ofstream outfile2(outputFileName);
    
    for (int i = 1; i <=lineNo; i++)
    {
        outfile2 << my_CardManager[i].name << "\t" << my_CardManager[i].classy << "\t" << my_CardManager[i].rarity << "\t"<< my_CardManager[i].set << "\t" << my_CardManager[i].type  << "\t" <<my_CardManager[i].cost <<endl;;
    }
    outfile2.close();
    
    cout<<"Succesful\n";
   
    
    return 0;
}












