//
//  main.cpp
//  home work2
//
//  Created by Abdulsalam Yazid on 9.04.2018.
//  Copyright © 2018 Abdulsalam Yazid. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include  <cmath>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;


// A class that defines a point
int numberOfDistances;
class Point {
public:
    int x;
    int y;
    int z;
};

//to sort by X coodidate
bool Xcomparitor(Point a,Point b){
    return (a.x<b.x);
}

//to sort by Y coodidate
bool Ycomparitor(Point a,Point b){
    return (a.y<b.y);
}

//to sort by Z coodidate
bool Zcomparitor(Point a,Point b){
    return (a.z<b.z);
}


//A method to calculate the Euclidien distance between two points
float Euclidean(Point one,Point two){
    numberOfDistances++;
    return  sqrt(pow((one.x-two.x),2) + pow((one.y-two.y),2) + pow((one.z-two.z),2));
};


//when the number of points is 3, this method will be applied
//it calculates all the pairwise distances of the 3 points
float closestPair(Point P[], int n)
{
    float minimumDistance = FLT_MAX;
    
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (Euclidean(P[i], P[j]) < minimumDistance)
                minimumDistance = Euclidean(P[i], P[j]);
        }
    }
    return minimumDistance;
}


//NOTE:the below method is taken from the pseducode in the slides, refer to the slides for more information

float ClosestPairRec(Point Px[],Point  Py[],int n){
    
    if(n<=3){
        return closestPair(Px,n);
        
    }
    
    cout  << " "<<  ""  << " "<<   endl;
    
    
    int Center = n/2;
    Point CenterPoint = Px[Center];
    
    
    //This is the coodinate of the line that will separate the points
    
    
    Point leftSubArray[Center+1];
    Point rightSubArray[n-Center-1];
    
    
    
    int indexOfLeftPoints = 0;
    int indexOfRightPoints = 0;
    
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= CenterPoint.x){
            
            leftSubArray[indexOfLeftPoints].x = Py[i].x;
            leftSubArray[indexOfLeftPoints].y = Py[i].y;
            leftSubArray[indexOfLeftPoints].z = Py[i].z;
            indexOfLeftPoints++;
        }
        else{
            rightSubArray[indexOfRightPoints].x = Py[i].x;
            rightSubArray[indexOfRightPoints].y = Py[i].y;
            rightSubArray[indexOfRightPoints].z = Py[i].z;
            indexOfRightPoints++;
        }
    }
    
    
    
    
    
    float q0q1 =  ClosestPairRec(Px,leftSubArray,Center);
    float r0r1 =  ClosestPairRec(Px+Center,rightSubArray ,n-Center);
    
    float delta;
    if(q0q1<r0r1)
        delta = q0q1;
    else
        delta = r0r1;
    
    // cout << "delta is " << delta <<endl;
    
    Point subArraySeparator[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - CenterPoint.x)< delta){
            subArraySeparator[j] = Py[i];
            j++;
        }
    
    
    
    
    
    // to find a potential small distance which can be between two sub arrays
    float minimum=FLT_MAX;
    for(int s1 = 0;s1<j;s1++){
        for(int s2=s1+1;s2<j && (subArraySeparator[s2].y-subArraySeparator[s1].y<minimum);s2++){
            float s1AndS2Min = Euclidean(subArraySeparator[s1], subArraySeparator[s2]);
            if(s1AndS2Min < minimum){
                minimum = s1AndS2Min;
                
            }
            
        }
    }
    
    // to find the min between the new min and delta
    if(minimum < delta)
        return minimum;
    else if (q0q1<r0r1)
        return q0q1;
    else
        return r0r1;
    
    
    
};


int main(int argc,  char * argv[]) {
    
     string fileName = argv[1];
  // string fileName = "data10000.txt";
    int numberOfPoints;
    ifstream myfile(fileName.c_str());
    myfile >> numberOfPoints;
    
    
    
    Point* P = new  Point[numberOfPoints];
    Point* Px = new  Point[numberOfPoints];
    Point* Py = new  Point[numberOfPoints];
    Point* Pz = new  Point[numberOfPoints];
    
    int index = 0;
    while (!myfile.eof())
    {
        int x;
        int y;
        int z;
        
        int x1;
        int y1;
        int z1;
        
        myfile >> x;
        myfile >> y;
        myfile >> z;
        
        
        
        x1 = P[index].x  = x;
        y1 = P[index].y = y;
        z1 = P[index].z = z;
        
        Px[index].x  = x;
        Px[index].y = y;
        Px[index].z = z;
        
        Py[index].x  = x;
        Py[index].y = y;
        Py[index].z = z;
        
        Pz[index].x  = x;
        Pz[index].y = y;
        Pz[index].z = z;
        
        
        index = index +1;
    }
    
    
    std::sort(Px,Px+numberOfPoints,Xcomparitor);
    std::sort(Py,Py+numberOfPoints,Ycomparitor);
    //std::sort(Pz,Pz+numberOfPoints,Zcomparitor);
    
    
    
    
    clock_t start = clock();
    float minDistance = ClosestPairRec(Px,Py,numberOfPoints);
    clock_t end = clock();
    double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
    cout << "the min is " <<  minDistance << endl;
    cout << "The number of Distances calculated is " << numberOfDistances <<endl;
    cout << "Time elapsed: " << elapsed_time << " SECONDS " << endl;
    return 0;
}

