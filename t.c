#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void transpose(int *dst, int *src , int dim) {
    int i, j;
    for (i=0; i < dim; i++)
        for (j=0; j < dim; j++) {
            /*the goal here is to move the element stored in src[i, j] to dst[j, i]
             access is achieved by multiplying the dimension by the row number */
            dst[j*dim + i] = src[i*dim +j];
        }
}

void opt_transpose(int *dst, int *src, int dim) {
    int k, l, i, j, block;

    block = 25;
       
    for (k = 0; k < dim; k += block)
        for (l = 0; l < dim; l += block) {
            for (i = k; (i < k + block) & (i < dim); ++i)
                for (j = l; (j < l + block) & (j < dim); ++j)
                    dst[j*dim + i] = src[i*dim +j];
        }
}

int main() {
    time_t t;
    int a, b, n;
    long start, finish;
    n = 2000;

    srand(time(NULL));

    int *mtx = (int*)malloc( n*n*sizeof(int) );
    int *mtx_t = (int*)malloc( n*n*sizeof(int) );
    for(int i = 0; i < n*n; i++ ) mtx[i] = lrand48( );

    for (int rn = 0; rn < 10; ++rn) {
        start = clock();
        transpose(mtx, mtx_t, n);
        finish = clock();
        printf("time: %ld\n", finish-start);
    }

    free(mtx);
    free(mtx_t);
}
