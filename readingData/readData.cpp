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
    char c_line[MAX_CHARS];
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

int main(int argc, char const *argv[])
{
    cout << "it started.";
    std::vector<std::vector<int> > test = loadFile();
    for(int i = 1; i < 17772; i++) {
        if (test[1][i] > 0)
        {
            cout << i << endl;
            cout << test[1][i] << endl;

            break;
        }
    }
    return 0;
}