#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genann.h"

/* This example is to illustrate how to use GENANN.
 * It is NOT an example of good machine learning techniques.
 *
 * Edited by: 
 * Konstantin Lübeck (University of Tübingen, Chair for Embedded Systems)
 */

//#define DEBUG
//#define MEASURE_TIME

#ifdef MEASURE_TIME
#include <time.h>
#endif

#if DATATYPE == 0 || DATATYPE == 1
const char *iris_data = "bezdekIris.data";
#elif DATATYPE == 2
const char *iris_data = "bezdekIris.fix16.data";
#endif

datatype *input, *class;
int samples;
const char *class_names[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

void load_data() {
    /* Load the iris data-set. */
    FILE *in = fopen(iris_data, "r");
    if (!in) {
        fprintf(stderr, "Could not open file: %s\n", iris_data);
        exit(1);
    }

    /* Loop through the data to get a count. */
    char line[1024];
    while (!feof(in) && fgets(line, 1024, in)) {
        ++samples;
    }
    fseek(in, 0, SEEK_SET);

    #ifdef DEBUG
    printf("Loading %d data points from %s\n", samples, iris_data);
    #endif

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
            #if DATATYPE == 0
            p[j] = atof(split);
            #elif DATATYPE == 1
            p[j] = (float) atof(split);
            #elif DATATYPE == 2
            p[j] = atoi(split);
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
            fprintf(stderr, "Unknown class %s.\n", split);
            exit(1);
        }
    }

    fclose(in);
}


int main(int argc, char *argv[])
{
    #ifdef DEBUG
    printf("GENANN IRIS benchmark.\n");
    printf("Train an ANN on the IRIS dataset using backpropagation.\n");
    #endif

    #ifdef MEASURE_TIME
    clock_t start, end;
    float seconds;
    #endif

    /* Load the data from file. */
    #ifdef MEASURE_TIME
    start = clock();
    #endif
    load_data();
    #ifdef MEASURE_TIME
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("loading data took: %fs\n", seconds);
    #endif

    /* 4 inputs.
     * 1 hidden layer(s) of 4 neurons.
     * 3 outputs (1 per class)
     */

    #ifdef MEASURE_TIME
    start = clock();
    #endif

    genann *ann = genann_init(4, 1, 4, 3);

    int i, j;
    int loops = 5000;

    /* Train the network with backpropagation. */
    #ifdef DEBUG
    printf("Training for %d loops over data.\n", loops);
    #endif

    for (i = 0; i < loops; ++i) {
        for (j = 0; j < samples; ++j) {
            #if DATATYPE == 0 || DATATYPE == 1
            genann_train(ann, input + j*4, class + j*3, .01);
            #elif DATATYPE == 2
            genann_train(ann, input + j*4, class + j*3, 0x0000028F);
            #endif
        }
    }

    #ifdef MEASURE_TIME
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("training took: %fs\n", seconds);
    #endif

    #ifdef MEASURE_TIME
    start = clock();
    #endif

    int correct = 0;
    for (j = 0; j < samples; ++j) {
        const datatype *guess = genann_run(ann, input + j*4);
        #if DATATYPE == 0 || DATATYPE == 1
        if (class[j*3+0] == 1.0) {if (guess[0] > guess[1] && guess[0] > guess[2]) ++correct;}
        else if (class[j*3+1] == 1.0) {if (guess[1] > guess[0] && guess[1] > guess[2]) ++correct;}
        else if (class[j*3+2] == 1.0) {if (guess[2] > guess[0] && guess[2] > guess[1]) ++correct;}
        else {fprintf(stderr, "Logic error.\n"); exit(1);}
        #elif DATATYPE == 2
        if (class[j*3+0] == 0x00010000) {if (guess[0] > guess[1] && guess[0] > guess[2]) ++correct;}
        else if (class[j*3+1] == 0x00010000) {if (guess[1] > guess[0] && guess[1] > guess[2]) ++correct;}
        else if (class[j*3+2] == 0x00010000) {if (guess[2] > guess[0] && guess[2] > guess[1]) ++correct;}
        else {fprintf(stderr, "Logic error.\n"); exit(1);}
        #endif
    }

    #ifdef MEASURE_TIME
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("classification took: %fs\n", seconds);
    #endif

    printf("%d/%d error rate: %0.1f%%\n", correct, samples, 100.0 - ((float)correct / samples * 100.0));

    genann_free(ann);

    return 0;
}
