#include <iostream>
#include <math.h>

#include <fstream>
#include <sstream>

#include <vector>

#include <string>

#include <string.h>

#include <sstream>

#include <stdio.h>

#include <cstdlib>

#include <time.h>
using namespace std;

#define NUM_USERS 458293
#define NUM_MOVIES 17770
#define MAX_CHARS 15




std::vector<std::vector<int> > loadFile() {
    // Makes it a vector [num_users], [num_movies]. Use the actual assigned num.
    std::vector<std::vector<int> > outputArray (NUM_USERS + 1, std::vector<int>(NUM_MOVIES + 1, 0)) ;
    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    //char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;

    ifstream allDta ("../um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported";
        exit(-1);
    }
    
    ifstream allIdx ("../um/all.idx");
    if(allIdx.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }
    cout << "Is it gonna go?\n";
    while (getline(allDta, dtaLine)) {
        if(getline(allIdx, idxLine)){
                memcpy(indChars, idxLine.c_str(), MAX_CHARS);
                index = atoi(indChars);
                counter ++;
                
        
                if(index == 1) {
                    istringstream iss(dtaLine);
                    iss >> userId >> movieId >> dateNum >> rating;
                    outputArray[userId][movieId] = rating;
                    if(counter % 10000000 == 0) {cout << counter << endl;}
                    }

            

        }
        
        
    }
    allIdx.close();
    allDta.close();

    return outputArray;
}

int findAverageReview() {
        // Makes it a vector [num_users], [num_movies]. Use the actual assigned num.
    
    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    //char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;
    int currTot = 0;

    ifstream allDta ("../um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported";
        exit(-1);
    }
    
    ifstream allIdx ("../um/all.idx");
    if(allIdx.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }
    cout << "Is it gonna go?\n";
    while (getline(allDta, dtaLine)) {
        if(getline(allIdx, idxLine)){
                memcpy(indChars, idxLine.c_str(), MAX_CHARS);
                index = atoi(indChars);
                
                
        
                if(index < 3) {
                    istringstream iss(dtaLine);
                    iss >> userId >> movieId >> dateNum >> rating;
                    currTot += rating;
                    counter ++;
                    if(counter % 10000000 == 1) {cout << counter << endl;}

                    }

            

        }
        
        
    }
    allIdx.close();
    allDta.close();

    return printf("The average is %f \n", (double)currTot / (double)counter);


}


void createNewFile(string outFileName, string outFileName2) {


    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    //char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;



    int numTraining = 0;
    int numValidation = 0;


    
    ifstream allIdx2 ("../um/all.idx");
    if(allIdx2.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }




    while(getline(allIdx2, idxLine)) {
        memcpy(indChars, idxLine.c_str(), MAX_CHARS);
        index = atoi(indChars);
        if(index != 2 && index != 5){
            numTraining += 1;
        }
        else {
            numValidation += 1;
        }
    }

    ofstream fout(outFileName.c_str());
    ofstream fout2(outFileName2.c_str());
    fout << "%%MatrixMarket matrix coordinate real"  << endl;
    fout2 << "%%MatrixMarket matrix coordinate real"  << endl;
    fout << NUM_USERS << " " << NUM_MOVIES << " " << numTraining << endl;
    fout2 << NUM_USERS << " " << NUM_MOVIES << " " << numValidation << endl;
    allIdx2.close();

    ifstream allDta ("../um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported";
        exit(-1);
    }
    
    ifstream allIdx ("../um/all.idx");
    if(allIdx.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }
    cout << "Is it gonna go?\n";
    while (getline(allDta, dtaLine)) {
        if(getline(allIdx, idxLine)){
            memcpy(indChars, idxLine.c_str(), MAX_CHARS);
            index = atoi(indChars);
            counter ++;
            
    
            if(index != 2 && index != 5) {
                istringstream iss(dtaLine);
                iss >> userId >> movieId >> dateNum >> rating;
                fout << userId << " " << movieId << " " << rating << endl;
                if(counter % 10000000 == 0) {cout << counter << endl;}
            }
            else if(index == 2) {
                istringstream iss(dtaLine);
                iss >> userId >> movieId >> dateNum >> rating;
                fout2 << userId << " " << movieId << " " << rating << endl;
                if(counter % 10000000 == 0) {cout << counter << endl;}
            }
        }
        
        
    }
    allIdx.close();
    allDta.close();
    
    

               
    
                

            

    
        
        
}

void createNewFilewTest(string outFileName, string outFileName2) {


    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    //char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;



    int numTraining = 0;
    int numValidation = 0;


    
    ifstream allIdx2 ("../um/all.idx");
    if(allIdx2.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }




    while(getline(allIdx2, idxLine)) {
        memcpy(indChars, idxLine.c_str(), MAX_CHARS);
        index = atoi(indChars);
        if(index <= 4){
            numTraining += 1;
        }
        else {
            numValidation += 1;
        }
    }
    string a = "%%MatrixMarket matrix coordinate real";
    ofstream fout(outFileName.c_str());
    ofstream fout2(outFileName2.c_str());
    fout << a  << endl;
    fout2 << a  << endl;
    fout << NUM_USERS << " " << NUM_MOVIES << " " << numTraining << endl;
    fout2 << NUM_USERS << " " << NUM_MOVIES << " " << numValidation << endl;
    allIdx2.close();

    ifstream allDta ("../um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported";
        exit(-1);
    }
    
    ifstream allIdx ("../um/all.idx");
    if(allIdx.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }
    cout << "Is it gonna go?\n";
    while (getline(allDta, dtaLine)) {
        if(getline(allIdx, idxLine)){
            memcpy(indChars, idxLine.c_str(), MAX_CHARS);
            index = atoi(indChars);
            counter ++;
            
    
            if(index <= 4) {
                istringstream iss(dtaLine);
                iss >> userId >> movieId >> dateNum >> rating;
                fout << userId << " " << movieId << " " << rating << endl;
                if(counter % 10000000 == 0) {cout << counter << endl;}
            }
            else if(index == 5) {
                istringstream iss(dtaLine);
                iss >> userId >> movieId >> dateNum >> rating;
                fout2 << userId << " " << movieId << " " << rating << endl;
                if(counter % 10000000 == 0) {cout << counter << endl;}
            }
        }
        
        
    }
    allIdx.close();
    allDta.close();
        
}

int main(int argc, char const *argv[])
{
    cout << "it started." << endl;
    
    // createNewFile("../um/netflixTraining.dta", "../um/netflixValidation.dta");
    // createNewFilewTest("../um/netflixTrainingAll.dta", "../um/netflixTest.dta");
    
    ifstream ifs ("../um/netflixTrainingAll.dta");
    string lin;
    for(int i = 0; i < 15; i++) {
        if(getline(ifs, lin))
            cout << lin << endl;
    }
    cout << "#2" << endl;
    ifstream ifs2 ("../um/netflixTrainingtest.dta");
    string lin2;
    for(int i = 0; i < 15; i++) {
        if(getline(ifs2, lin2))
            cout << lin2 << endl;
    }
    return 0;
}