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




std::vector<std::vector<int> > loadFileTrain() {
    // Makes it a vector [num_users], [num_movies]. Use the actual assigned num.
    std::vector<std::vector<int> > outputArray (NUM_USERS + 1, std::vector<int>(NUM_MOVIES + 1, 0)) ;
    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;
    
    ifstream allDta ("./um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported Train";
        //exit(-1);
    }
    
    ifstream allIdx ("./um/all.idx");
    if(allIdx.fail()) {
        cout << "all.idx not correctly imported";
        //exit(-1);
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

std::vector<double> loadFileTest(double totAvg, std::vector<double> user, std::vector<double> movie) {
    // Makes it a vector [num_users], [num_movies]. Use the actual assigned num.
    std::vector<double> test;
    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;
    double uTend;
    double mTend;
    
    ifstream allDta ("./um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported Test";
        exit(-1);
    }
    
    ifstream allIdx ("./um/all.idx");
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
            
            if(index == 5) {
                istringstream iss(dtaLine);
                iss >> userId >> movieId >> dateNum >> rating;
                uTend = user[userId - 1] - totAvg;
                mTend = movie[movieId - 1] - totAvg;
                test.push_back(totAvg + (0.7 * uTend) + (0.5 * mTend));
                if(counter % 10000000 == 2) {cout << counter << endl;}
            }
            
        }
        
    }
    allIdx.close();
    allDta.close();
    
    return test;
}

double findAverageReview() {
    // Makes it a vector [num_users], [num_movies]. Use the actual assigned num.
    
    string dtaLine;
    string idxLine;
    int index;
    int userId, movieId, dateNum, rating;
    char c_line[MAX_CHARS];
    char indChars[MAX_CHARS];
    int counter = 0;
    int currTot = 0;
    
    ifstream allDta ("./um/all.dta");
    if(allDta.fail()) {
        cout << "all.dta not correctly imported";
        exit(-1);
    }
    
    ifstream allIdx ("./um/all.idx");
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
    
    return (double)currTot / (double)counter;
}

double findAvgPer (std::vector<int> data) {
    int avg = 0;
    int count = 0;

    for (int i = 0; i < data.size(); i++) {
        if (data[i] != 0) {
            avg += data[i];
            count += 1;
        }
    }

    if (count != 0) {
        
        return (double) avg / (double) count;
    }
    
    return 0;
}

int main(int argc, char const *argv[])
{
    std::vector<double> userAvg;
    std::vector<double> movieAvg;
    std::vector<double> predict;

    std::vector<std::vector<int> > train = loadFileTrain();
    double totAvg = findAverageReview();

    printf("ThisStepDone");
    
    for (int i = 0; i < NUM_USERS; i++) {
        userAvg.push_back(findAvgPer(train[i]));
    }
    
    for (int j = 0; j < NUM_MOVIES; j++) {
        std::vector<int> temp;
        for (int i = 0; i < NUM_USERS; i++) {
            temp.push_back(train[i][j]);
        }
        movieAvg.push_back(findAvgPer(temp));
    }
    
    predict = loadFileTest(totAvg, userAvg, movieAvg);
    
    ofstream outputFile;
    outputFile.open("baselineRTry2.txt");
    
    for (int ind = 0; ind < predict.size(); ind++) {
        outputFile << predict[ind] << endl;
    }
    
    outputFile.close();
    
    return 0;
}

