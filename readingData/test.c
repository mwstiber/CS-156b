/* 
*   Matrix Market I/O example program
*
*   Create a small sparse, coordinate matrix and print it out
*   in Matrix Market (v. 2.0) format to standard output.
*
*   (See http://math.nist.gov/MatrixMarket for details.)
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"


#define NUM_USERS 458293
#define NUM_MOVIES 17770

int main()
{
    FILE * fp = fopen("netflixTraining.dta", "w");
    FILE * fp2 = fopen("netflixTest.dta", "w");
    MM_typecode matcode;                        
    

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);

    mm_write_banner(fp, matcode); 
    mm_write_banner(fp2, matcode);
    mm_write_mtx_crd_size(fp, NUM_USERS, NUM_MOVIES, 99666408);
    mm_write_mtx_crd_size(fp2, NUM_USERS, NUM_MOVIES, 2749898);

    /* NOTE: matrix market files use 1-based indices, i.e. first element
      of a vector has index 1, not 0.  */

        

    FILE *finput = fopen("../um/all.dta","r");
    FILE *finds = fopen("../um/all.idx", "r");
    int userId,itemId,rating,t,idx;
    while(fscanf(finput,"%d %d %d %d",&userId, &itemId, &t, &rating)!=EOF){
        fscanf(finds, "%d", &idx);
        if(idx <= 4) {
            fprintf(fp, "%d %d %d\n", userId, itemId, rating);
            if(rating > 5)
                printf("%d\n", rating);
        }
        else {
            fprintf(fp2, "%d %d %d\n", userId, itemId, rating);
            if(itemId > 17770) {
                printf("%d\n", itemId);
            }
        }
        
    }
    fclose(fp);
    fclose(fp2);
    fclose(finput);
    fclose(finds);
    

    return 0;
}
