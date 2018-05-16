
//This file is used to generate predictions.
#include <cmath>
#include <iostream>
#include <cstring> 
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <string.h> 
#include <utility>
#include "SVD.cpp"

using namespace std;

int main() {
    string idxLine;
    string trainFile = "train.txt";  //set train data
    string crossFile = "cross.txt";  //set cross validation data
    string testFile = "../../um/qual.dta";  //set test data
    string outFile = "testTwo.txt";  //set output data
    FILE *fp = fopen("../../um/all.dta","r");
    FILE *ft = fopen("train.txt","w");
    FILE *fc = fopen("cross.txt","w");
    srand(time(NULL));
    char s[2048];
    char indChars[15];
    
    ifstream allIdx ("../../um/all.idx");
    if(allIdx.fail()) {
        cout << "all.idx not correctly imported";
        exit(-1);
    }
    int counter = 0;
    int count = 0;
    int index;
    bool cvOnThis;
    while (fscanf(fp,"%s",&s)!=EOF ) {
        if(count % 4 == 0) {
            if(getline(allIdx, idxLine)) {
                memcpy(indChars, idxLine.c_str(), 15);
                index = atoi(indChars);
                counter ++;
                if(rand()%100==0) {
                    cvOnThis = true;
                }
                else
                    cvOnThis = false;
            }
            else
                break;
        }
        
        if(index <= 3){
            if (cvOnThis) {
                           //use 1% random train data for cross validation
                if(count % 4 == 3)
                    fprintf(fc,"%s\n",s);
                else
                    fprintf(fc, "%s,", s);
            }
            else {
                if(count % 4 == 3)
                    fprintf(ft,"%s\n",s);
                else
                    fprintf(ft, "%s,", s);
            }
        }
        if(counter % 10000000 == 1) {cout << s <<" " << counter << endl;}
        count++;
                    
    }
    fclose(fp);
    fclose(ft);
    fclose(fc);
    SVD svd(NULL,NULL,0,NULL,NULL, trainFile, crossFile, testFile, outFile);
    double rmse = svd.MyTrain();     //train
    return 0;
}
