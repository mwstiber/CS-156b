#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE * fp = fopen("RMBTest.txt", "w");
    FILE * preds = fopen("../NetflixDtaforGC/netflixTest.dta.predict", "r");

    int userId, itemId;
    float rating;
    while(fscanf(preds,"%d %d %f",&userId, &itemId, &rating)!=EOF){

        

        fprintf(fp, "%f\n", rating);
        
        
        
    }
    fclose(fp);
    fclose(preds);

    return 0;
}