//
//  main.cpp
//  hw3
//
//  Created by Abdulsalam Yazid on 25.11.2017.
//  Copyright © 2017 Abdulsalam Yazid. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <math.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <iomanip>

//my book classs
class bookCharacter{
    
public:
    int pageNo;
    int lineNo;
    int index;
    string character;
    
    
};

//key generator method
unsigned long keyGenarator(int pageNo,int lineNo,int index) {
    string stringPageNo = std::to_string(pageNo);
    string stringLineNo = std::to_string(lineNo);
    if (lineNo <=9 )
        stringLineNo = "0" + stringLineNo;
    string stringIndex = std::to_string(index);
    if (index <=9 )
        stringIndex = "0"+stringIndex;
    string stringkey = stringPageNo + stringLineNo + stringIndex;
    unsigned long key = (stoi(stringkey));
    return key;
}



//a dictionary class
class dictionary{
public:
    bookCharacter value;
    
};

//a list class
class list{
public:
    bookCharacter value;
    unsigned long  key;
    
};


// hashfunction
unsigned long HashFunc(unsigned long key)
{
    return  131071 * fmod(key*0.61803398875, 1);
}

//probing function
unsigned long probing (unsigned long function,int count){
    return (function + ((7*count) *(3*(count*count))))%131071;
}


//bookcharacter insertion method for dictiony
void  dicInsertion (dictionary* mydictionary, bookCharacter* myobjects,int N){
    
    clock_t start = clock();
    
    int i = 0;
    double c= 0;
    int thousand =0;
    int tenThousand=0;
    
    double hundredThousand = 0.0;
    while(i!=N){
        
        int collition=1;
        string value = myobjects[i].character;
        unsigned long unhashedkey =  keyGenarator(myobjects[i].pageNo,myobjects[i].lineNo,myobjects[i].index);
        unsigned long hashedkey =  HashFunc(unhashedkey);
        
//check if there is a collision and keep on probing till you find an empyt place
        while(mydictionary[hashedkey].value.lineNo != 0 ){
            hashedkey = probing(hashedkey,collition);
            collition++;
            c++;
            
            if(i<=1000)
                thousand++;
            
            if(i<=10000)
                tenThousand++;
            
            if(i<=100000)
                hundredThousand++;
            
        }
        
       
        mydictionary[hashedkey].value = myobjects[i];
        i++;
    }
    
    clock_t end = clock();
    double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    cout << "DICTIONARY"<<endl;
    cout << "Insertion Finished After  " << elapsed_time << " SECONDS " << endl<<endl;
    cout << "Average number of collisions (first 1000)  | " << double(thousand/1000.0) << endl;
    cout << "Average number of collisions (first 10000)  | " << tenThousand/10000.0 << endl;
    cout << "Average number of collisions (first 100000)  | " << hundredThousand/100000.0 << endl;
    cout << "Average number of collisions (overall)  | " << double(c/131071) << endl;
    
}

//dictionary lookup function
void diclookup(dictionary* mydictionary,dictionary* myloopup,int N){
    int c = 0;
    int i = 0;
    while(i!=N){
        int collition=1;
        unsigned long unhashedkey =  keyGenarator( myloopup[i].value.pageNo,myloopup[i].value.lineNo,myloopup[i].value.index);
        unsigned long hashedkey =  HashFunc(unhashedkey);
        


        while(true ){
//calculate an unshekey from the dictionary and keep looking it up
            unsigned long unhashedkey1 =  keyGenarator( mydictionary[hashedkey].value.pageNo,mydictionary[hashedkey].value.lineNo,mydictionary[hashedkey].value.index);
            
            if (unhashedkey == unhashedkey1)
            {
                myloopup[i].value.character = mydictionary[hashedkey].value.character;
                break;
            }
            hashedkey = probing(hashedkey,collition);
            collition++;
            c++;
            
        }
        i++;
        
    }
    
    
}

//a method for inserting objects to a list
void listInsertion(dictionary* myList,bookCharacter* myobjects,int N){
    for(int i =1;i<N;i++){
        myList[i].value= myobjects[i];
        
        
    }
}


//list Lookup for updating characters
void listLookup(dictionary* myLookupList,dictionary* myobjects,int N){
    
    unsigned long myLookupListUnhashedkeys[N];
    for (int x=1; x<=N; x++) {
        myLookupListUnhashedkeys[x] = keyGenarator(myLookupList[x].value.pageNo,myLookupList[x].value.lineNo,myLookupList[x].value.index);
    }
    unsigned long myobjectsUnhashedkeys[N];
    
    for (int y=1; y<=N; y++) {
        myobjectsUnhashedkeys[y] = keyGenarator(myobjects[y].value.pageNo,myobjects[y].value.lineNo,myobjects[y].value.index);
    }
    
    for (int i =1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            if( myLookupListUnhashedkeys[i] ==  myobjectsUnhashedkeys[j]){
                myLookupList[i].value.character = myobjects[j].value.character;
                break;
            }
            
        }
    }
}




//This method is used for getting the things In a file and putting them to an array for futher processing
void arrayfiller(string arr[],string fileName ,int lineNoo){
    //number of lines
    lineNoo = lineNoo+1;
    int dividor ;
    int numberOfIdexes=1;
    if(fileName=="ds-set-lookup.txt"){
        numberOfIdexes = (3*lineNoo);
        dividor =3;
        
    }
    
    else
    {
        numberOfIdexes = 4*lineNoo;
        dividor =4;
    }
    
    arr[numberOfIdexes];
    
    
    
    std:: string line;
    int index = 1;
    ifstream myFile(fileName);
    
    //reading the elements from the file, and putting them in an array, then later to my object
    std::stringstream linestream(line);
    char delimeter=('\t');
    while(getline(myFile,line,delimeter) && !myFile.eof()) {
        arr[index]=line;
        ++index;
        if(index%dividor==0)
            delimeter=('\n');
        else
            delimeter=('\t');
        if(index==numberOfIdexes){
            break;
        }
        
    }
    
    myFile.close();
    
    
}



int main(int argc, const char * argv[]) {
    
    string  input = "ds-set-input.txt";
    string  lookup = "ds-set-lookup.txt";
    string dictionaryOutput = "dictionaryOutput.txt";
     string outputForinput = "Listoutput.txt";
      //find the number of lines in a file to know the size of elements
    int lineNoo = 1;
    std::string myline;
    std::ifstream myfile(input);
    while (std::getline(myfile, myline)){
        lineNoo++;

    }
    
    // an object of my cardManager class
    bookCharacter* my_Characters = new bookCharacter[lineNoo];
    dictionary* my_Dictionary = new dictionary[lineNoo];
    dictionary* my_dictionaryLookUp = new dictionary[lineNoo];
    dictionary* my_List = new dictionary[lineNoo];
    dictionary* my_ListLookUp = new dictionary[lineNoo];
    
  
    //calcalue the number of elements in the files to be used in a method
    int numberOfIdexesForMyChar = 4*lineNoo;
    int numberOfIdexesForLookup = 3*lineNoo;
    
    //this array will used when all the data from in the input file comes from the arrafiller method
    string* arrforMychar = new string[numberOfIdexesForMyChar];
    arrayfiller(arrforMychar,"ds-set-input.txt",lineNoo);
    
     //this array will used when all the data from in the lookup file comes from the arrafiller method
    string* arrForLookup = new string[numberOfIdexesForLookup];
    arrayfiller(arrForLookup,"ds-set-lookup.txt",lineNoo);
    
    
    
    
    //The elements in the array "arrforMychar" are put to the charcters object
    int i =1;
    int index = 1;
    while(i <=numberOfIdexesForMyChar){
        my_Characters[index].pageNo =atoi(arrforMychar[i].c_str());
        ++i;
        my_Characters[index].lineNo=atoi(arrforMychar[i].c_str());
        ++i;
        my_Characters[index].index =atoi(arrforMychar[i].c_str());
        ++i;
        my_Characters[index].character =arrforMychar[i];
        ++index;
        i++;
    }
    
    
    delete[] arrforMychar;
    
     //The elements in the array "arrForLookup" are put to the charcters object
    int ii =1;
    int indexx = 2;
    while(ii <= numberOfIdexesForLookup){
        my_dictionaryLookUp[indexx].value.pageNo =atoi(arrForLookup[ii].c_str());
        ++ii;
        my_dictionaryLookUp[indexx].value.lineNo=atoi(arrForLookup[ii].c_str());
        ++ii;
        my_dictionaryLookUp[indexx].value.index =atoi(arrForLookup[ii].c_str());
        my_dictionaryLookUp[indexx].value.character ="a";
        ++indexx;
        ii++;
    }
    my_ListLookUp =my_dictionaryLookUp;
    delete[] arrForLookup;
    
    
    
    //calling the dictionary Insertion method
    //the insertion time is called in the method itsel
    {
        dicInsertion (my_Dictionary, my_Characters,lineNoo);
    }
    
    //calling the dictionary loopup function
    //and calcalating the lookup time
    {
        clock_t start = clock();
        diclookup(my_Dictionary,my_dictionaryLookUp,lineNoo);
        clock_t end = clock();
        double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
        cout <<endl;
        cout << "Lookup finished after " << elapsed_time << " SECONDS " << endl;
        cout <<endl;
        
    }
    
    //calling listInsertion
    cout <<"LIST"<<endl;
    {
        clock_t start = clock();
        listInsertion(my_List,my_Characters,lineNoo);
        clock_t end = clock();
        double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
        cout << "Insertion finished after " << elapsed_time << " SECONDS " << endl;
    }
    
    //looking up List
    {
        clock_t start = clock();
        listLookup(my_ListLookUp,my_List,lineNoo);
        clock_t end = clock();
        double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
        cout << "Lookup finished after " << elapsed_time << " SECONDS " << endl;
    }
    
    
    //printing output of dictionary to an output file
    
    ofstream outfile3(dictionaryOutput);
    for (int i = 2; i <=lineNoo; i++)
    {
        outfile3 << my_dictionaryLookUp[i].value.pageNo << "\t" <<my_dictionaryLookUp[i].value.lineNo << "\t" << my_dictionaryLookUp[i].value.index << "\t"<<my_dictionaryLookUp[i].value.character
        <<endl;
    }
    outfile3.close();
    
    
    //printing the  listlookup to an outfull file
    ofstream outfile2(outputForinput);
    for (int i = 2; i <=lineNoo; i++)
    {
        outfile2 << my_ListLookUp[i].value.pageNo << "\t" <<my_ListLookUp[i].value.lineNo << "\t" << my_ListLookUp[i].value.index << "\t"<<my_ListLookUp[i].value.character
        <<endl;
    }
    outfile2.close();
    
    cout<<"Succesful\n";
    
    
    
    
    
}

