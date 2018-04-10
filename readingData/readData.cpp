#include <iostream>
#include <math.h>

#include <fstream>

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




std::vector<std::vector<int> > loadFile() {
    //int outputArray[NUM_USERS + 1][NUM_MOVIES + 1];
    

    string dtaLine;
    string idxLine;

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
    while (getline(allDta, dtaLine) && getline(allIdx, idxLine)) {
        cout << "This is working";
    }

    return std::vector<std::vector<int> >(1, std::vector<int>(2, 0));

    //return outputArray;
}

int main(int argc, char const *argv[])
{
    
    loadFile();
    return 0;
}