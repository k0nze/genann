/*
 * GENANN - Minimal C Artificial Neural Network
 *
 * Copyright (c) 2015, 2016 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Edited by: 
 * Konstantin Lübeck (University of Tübingen, Chair for Embedded Systems)
 */


#ifndef __GENANN_H__
#define __GENANN_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATATYPE
#define DATATYPE 0
#endif

#if DATATYPE == 0
typedef double datatype;
#elif DATATYPE == 1
typedef float datatype;
#elif DATATYPE == 2
#include "libfixmath/fix16.h"

typedef fix16_t datatype;

int fix16_to_int_cast(fix16_t a);
#endif

#ifndef GENANN_RANDOM
/* We use the following for uniform random numbers between 0 and 1.
 * If you have a better function, redefine this macro. */
#if DATATYPE == 0 || DATATYPE == 1
#define GENANN_RANDOM() (((datatype)rand())/RAND_MAX)
#elif DATATYPE == 2
#define GENANN_RANDOM() fix16_div( (uint32_t) rand(), fix16_maximum)
#endif
#endif

typedef datatype (*genann_actfun)(datatype a);

typedef struct genann {
    /* How many inputs, outputs, and hidden neurons. */
    int inputs, hidden_layers, hidden, outputs;

    /* Which activation function to use for hidden neurons. Default: gennann_act_sigmoid_cached*/
    genann_actfun activation_hidden;

    /* Which activation function to use for output. Default: gennann_act_sigmoid_cached*/
    genann_actfun activation_output;

    /* Total number of weights, and size of weights buffer. */
    int total_weights;

    /* Total number of neurons + inputs and size of output buffer. */
    int total_neurons;

    /* All weights (total_weights long). */
    datatype *weight;

    /* Stores input array and output of each neuron (total_neurons long). */
    datatype *output;

    /* Stores delta of each hidden and output neuron (total_neurons - inputs long). */
    datatype *delta;

} genann;



/* Creates and returns a new ann. */
genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs);

/* Creates ANN from file saved with genann_write. */
genann *genann_read(FILE *in);

/* Sets weights randomly. Called by init. */
void genann_randomize(genann *ann);

/* Returns a new copy of ann. */
genann *genann_copy(genann const *ann);

/* Frees the memory used by an ann. */
void genann_free(genann *ann);

/* Runs the feedforward algorithm to calculate the ann's output. */
datatype const *genann_run(genann const *ann, datatype const *inputs);

/* Does a single backprop update. */
void genann_train(genann const *ann, datatype const *inputs, datatype const *desired_outputs, datatype learning_rate);

/* Saves the ann. */
void genann_write(genann const *ann, FILE *out);


datatype genann_act_sigmoid(datatype a);
//datatype genann_act_sigmoid_cached(datatype a);
datatype genann_act_threshold(datatype a);
datatype genann_act_linear(datatype a);


#ifdef __cplusplus
}
#endif

#endif /*__GENANN_H__*/
