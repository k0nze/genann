#include <stdio.h>
#include "genann.h"

int main(int argc, char *argv[]) {
    printf("GENANN example 1.\n");
    printf("Train a small ANN to the XOR function using backpropagation.\n");

    genann *ann;

    #if DATATYPE == 0 || DATATYPE == 1
    /* Input and expected out data for the XOR function. */
    const datatype input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const datatype output[4] = {0, 1, 1, 0};
    int i;

    /* New network with 2 inputs,
     * 1 hidden layer of 2 neurons,
     * and 1 output. */
    ann = genann_init(2, 1, 2, 1);

    /* Train on the four labeled data points many times. */
    for (i = 0; i < 300; ++i) {
        genann_train(ann, input[0], output + 0, 3);
        genann_train(ann, input[1], output + 1, 3);
        genann_train(ann, input[2], output + 2, 3);
        genann_train(ann, input[3], output + 3, 3);
    }

    /* Run the network and see what it predicts. */
    printf("Output for [%1.f, %1.f] is %1.f.\n", input[0][0], input[0][1], *genann_run(ann, input[0]));
    printf("Output for [%1.f, %1.f] is %1.f.\n", input[1][0], input[1][1], *genann_run(ann, input[1]));
    printf("Output for [%1.f, %1.f] is %1.f.\n", input[2][0], input[2][1], *genann_run(ann, input[2]));
    printf("Output for [%1.f, %1.f] is %1.f.\n", input[3][0], input[3][1], *genann_run(ann, input[3]));
    #elif DATATYPE == 2
    /* Input and expected out data for the XOR function. */
    const datatype input[4][2] = {
        {0x00000000, 0x00000000}, 
        {0x00000000, 0x00010000}, 
        {0x00010000, 0x00000000}, 
        {0x00010000, 0x00010000}
    };

    const datatype output[4] = {
        0x00000000, 
        0x00010000, 
        0x00010000, 
        0x00000000
    };
    
    int i;

    /* New network with 2 inputs,
     * 1 hidden layer of 2 neurons,
     * and 1 output. */
    ann = genann_init(2, 1, 2, 1);

    /* Train on the four labeled data points many times. */
    for (i = 0; i < 300; ++i) {
        genann_train(ann, input[0], output + 0, 0x00030000);
        genann_train(ann, input[1], output + 1, 0x00030000);
        genann_train(ann, input[2], output + 2, 0x00030000);
        genann_train(ann, input[3], output + 3, 0x00030000);
    }

    /* Run the network and see what it predicts. */
    printf("Output for [%1.f, %1.f] is %1.f.\n", fix16_to_float(input[0][0]), fix16_to_float(input[0][1]), fix16_to_float(*genann_run(ann, input[0])));
    printf("Output for [%1.f, %1.f] is %1.f.\n", fix16_to_float(input[1][0]), fix16_to_float(input[1][1]), fix16_to_float(*genann_run(ann, input[1])));
    printf("Output for [%1.f, %1.f] is %1.f.\n", fix16_to_float(input[2][0]), fix16_to_float(input[2][1]), fix16_to_float(*genann_run(ann, input[2])));
    printf("Output for [%1.f, %1.f] is %1.f.\n", fix16_to_float(input[3][0]), fix16_to_float(input[3][1]), fix16_to_float(*genann_run(ann, input[3])));
    #endif

    genann_free(ann);
    return 0;
}
