#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genann.h"

/* This example is to illustrate how to use GENANN.
 * It is NOT an example of good machine learning techniques.
 */

#if DATATYPE == 0 || DATATYPE == 1
const char *iris_data = "example/iris.data";
#elif DATATYPE == 2
const char *iris_data = "example/iris.fix16.data";
#elif DATATYPE == 2
#endif 

datatype *input, *class;
int samples;
const char *class_names[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

void load_data() {
    /* Load the iris data-set. */
    FILE *in = fopen(iris_data, "r");
    if (!in) {
        printf("Could not open file: %s\n", iris_data);
        exit(1);
    }

    /* Loop through the data to get a count. */
    char line[1024];
    while (!feof(in) && fgets(line, 1024, in)) {
        ++samples;
    }
    fseek(in, 0, SEEK_SET);

    printf("Loading %d data points from %s\n", samples, iris_data);

    /* Allocate memory for input and output data. */
    input = malloc(sizeof(datatype) * samples * 4);
    class = malloc(sizeof(datatype) * samples * 3);

    /* Read the file into our arrays. */
    int i, j;
    for (i = 0; i < samples; ++i) {
        datatype *p = input + i * 4;
        datatype *c = class + i * 3;
        c[0] = c[1] = c[2] = 0.0;

        fgets(line, 1024, in);

        char *split = strtok(line, ",");
        for (j = 0; j < 4; ++j) {
            #if DATATYPE == 0 || DATATYPE == 1
            p[j] = atof(split);
            #elif DATATYPE == 2
            p[j] = (uint32_t) atoi(split);
            #endif
            split = strtok(0, ",");
        }

        split[strlen(split)-1] = 0;
        #if DATATYPE == 0 || DATATYPE == 1
        if (strcmp(split, class_names[0]) == 0) {c[0] = 1.0;}
        else if (strcmp(split, class_names[1]) == 0) {c[1] = 1.0;}
        else if (strcmp(split, class_names[2]) == 0) {c[2] = 1.0;}
        #elif DATATYPE == 2
        if (strcmp(split, class_names[0]) == 0) {c[0] = 0x00010000;}
        else if (strcmp(split, class_names[1]) == 0) {c[1] = 0x00010000;}
        else if (strcmp(split, class_names[2]) == 0) {c[2] = 0x00010000;}
        #endif
        else {
            printf("Unknown class %s.\n", split);
            exit(1);
        }

        #if DATATYPE == 0 || DATATYPE == 1
        //printf("Data point %d is %f %f %f %f  ->   %f %f %f\n", i, p[0], p[1], p[2], p[3], c[0], c[1], c[2]);
        #elif DATATYPE == 2
        //printf("Data point %d is %f %f %f %f  ->   %f %f %f\n", i, fix16_to_float(p[0]), fix16_to_float(p[1]), fix16_to_float(p[2]), fix16_to_float(p[3]), fix16_to_float(c[0]), fix16_to_float(c[1]), fix16_to_float(c[2]));
        #endif
    }

    fclose(in);
}


int main(int argc, char *argv[])
{
    printf("GENANN example 4.\n");
    printf("Train an ANN on the IRIS dataset using backpropagation.\n");

    /* Load the data from file. */
    load_data();

    /* 4 inputs.
     * 1 hidden layer(s) of 4 neurons.
     * 3 outputs (1 per class)
     */
    genann *ann = genann_init(4, 1, 4, 3);

    int i, j;
    int loops = 5000;

    /* Train the network with backpropagation. */
    printf("Training for %d loops over data.\n", loops);
    for (i = 0; i < loops; ++i) {
        for (j = 0; j < samples; ++j) {
            #if DATATYPE == 0 || DATATYPE == 1
            genann_train(ann, input + j*4, class + j*3, .01);
            #elif DATATYPE == 2
            genann_train(ann, input + j*4, class + j*3, 0x0000028F);
            #endif
        }
        /* printf("%1.2f ", xor_score(ann)); */
    }

    int correct = 0;
    for (j = 0; j < samples; ++j) {
        const datatype *guess = genann_run(ann, input + j*4);
        #if DATATYPE == 0 || DATATYPE == 1
        if (class[j*3+0] == 1.0) {if (guess[0] > guess[1] && guess[0] > guess[2]) ++correct;}
        else if (class[j*3+1] == 1.0) {if (guess[1] > guess[0] && guess[1] > guess[2]) ++correct;}
        else if (class[j*3+2] == 1.0) {if (guess[2] > guess[0] && guess[2] > guess[1]) ++correct;}
        #elif DATATYPE == 2
        if (class[j*3+0] == 0x00010000) {if (guess[0] > guess[1] && guess[0] > guess[2]) ++correct;}
        else if (class[j*3+1] == 0x00010000) {if (guess[1] > guess[0] && guess[1] > guess[2]) ++correct;}
        else if (class[j*3+2] == 0x00010000) {if (guess[2] > guess[0] && guess[2] > guess[1]) ++correct;}
        #endif
        else {printf("Logic error.\n"); exit(1);}
    }

    printf("%d/%d correct (%0.1f%%).\n", correct, samples, (float)correct / samples * 100.0);

    genann_free(ann);

    return 0;
}
