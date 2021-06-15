#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void print_mem(uint8_t *m, int len) {
    int i;
    for (int i = 0; i < len; i++) {
        printf("%d ", m[i]);
    }
    printf("\n");
}

uint8_t op_control(uint8_t *a, uint8_t *b, uint8_t op) {
    uint8_t result;

    switch(op) {
        case 1: result = *a & *b;
            break;
        case 2: result = *a | *b;
            break;
        case 3: result = *a ^ *b;
            break;
        case 4: result = ~(*a);
            break;
        case 5: result = *a * *b;
            break;
        case 6: result = *a + *b;
            break;
        case 7: result = *a - *b;
            break;
        default:
            break;
    }

    return result;
}

void mem_op(uint8_t* m, int len, uint8_t op) {
    int half = len / 2;
    
    if(op != 4) {
        for(int i = 0; i < half; i++) {
            m[i] = op_control(&m[i], &m[i + half], op);   
        }
    } else {
        for(int i = 0; i < len; i++) {
            m[i] = op_control(&m[i], NULL, op);   
        }
    }
}

int main(int argc, char* argv[]) {
    FILE *input;

    if (argc < 2) {
        printf("Error: missing path to input file\n");
        printf("1: &\n2: |\n3: ^\n4: ~\n5: *\n6: +\n7: -\n");
        return EXIT_FAILURE;
    }

    if ((input = fopen(argv[1], "r")) == NULL) {
        printf("Error: could not open file\n");
        return EXIT_FAILURE;
    }

    int len, op;
    fscanf(input, "%d", &len);
    fscanf(input, "%d", &op);

    uint8_t str[] = "0123456789ABCDEF";
    uint8_t* m = (uint8_t*) malloc(len * sizeof(uint8_t));
    srand(len);
    size_t i = len;
    printf("%d %d\n", len, op);

    while(i--)
        m[i] = str[rand() % 16];

    print_mem(m, len);
    mem_op(m, len, op);
    print_mem(m, len);
    return 0;
}
