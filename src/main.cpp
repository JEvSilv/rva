#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>
#include "ap_rv.h"

void print_mem(uint8_t *m, int len) {
    int i;
    for (int i = 0; i < len; i++) {
        printf("%d ", m[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    FILE *input;
    double t;

    if (argc < 2) {
        printf("Error: missing path to input file\n");
        return EXIT_FAILURE;
    }

    if ((input = fopen(argv[1], "r")) == NULL) {
        printf("Error: could not open file\n");
        return EXIT_FAILURE;
    }

    int len, op;
    fscanf(input, "%d", &len);
    fscanf(input, "%d", &op);

    uint8_t str[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint8_t* m = (uint8_t*) malloc(len * sizeof(uint8_t));
    srand(len);
    size_t i = len;
    printf("%d %d\n", len, op);

    while(i--)
        m[i] = str[rand() % 10];

    print_mem(m, len);

    APrv * ap = new APrv();
    ap->reset();
    ap->mem_size = len;
    ap->register_op("OP");
    
    t = omp_get_wtime();
    switch(op) {
        case 1:
            ap->__and<uint8_t>(m);
            break;
        case 2:
            ap->__or<uint8_t>(m);
            break;
        case 3:
            ap->__xor<uint8_t>(m);
            break;
        case 4:
            ap->__not<uint8_t>(m);
            break;
        case 5:
            ap->mult<uint8_t>(m);
            break;
        case 6:
            ap->add<uint8_t>(m);
            break;
        default:
            break;
    }
    t = omp_get_wtime() - t;

    print_mem(m, len);
    printf("%lf\n", t);

    return 0;
}
