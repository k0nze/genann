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
 */

#include "genann.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#define LOOKUP_SIZE 4096

#if DATATYPE == 2
int fix16_to_int_cast(fix16_t a) {
    uint32_t sign = a & 0x80000000;
    return (int) (a >> 16) | sign;
}
#endif

datatype genann_act_sigmoid(datatype a) {
    #if DATATYPE == 0 || DATATYPE == 1
    if (a < -45.0) return 0;
    if (a > 45.0) return 1;
    return 1.0 / (1 + exp(-a));
    #elif DATATYPE == 2
    if ((int) a < (int) 0xFFD30000) return 0x00000000;
    if ((int) a > (int) 0x002D0000) return 0x00010000;
    return fix16_div(0x00010000, fix16_sadd(0x00010000,fix16_exp(-a)));
    #endif
}

/*
datatype genann_act_sigmoid_cached(datatype a) {
    // If you're optimizing for memory usage, just
    // delete this entire function and replace references
    // of genann_act_sigmoid_cached to genann_act_sigmoid
    #if DATATYPE == 0 || DATATYPE == 1
    const datatype min = -15.0;
    const datatype max = 15.0;
    static int initialized = 0;
    static datatype interval;
    static datatype lookup[LOOKUP_SIZE];

    // Calculate entire lookup table on first run. 
    if (!initialized) {
        interval = (max - min) / LOOKUP_SIZE;
        int i;
        for (i = 0; i < LOOKUP_SIZE; ++i) {
            lookup[i] = genann_act_sigmoid(min + interval * i);
        }
        // This is down here to make this thread safe. 
        initialized = 1;
    }

    int i;
    i = (int)((a-min)/interval+0.5);
    if (i <= 0) return lookup[0];
    if (i >= LOOKUP_SIZE) return lookup[LOOKUP_SIZE-1];
    return lookup[i];

    #elif DATATYPE == 2
    const datatype min = 0xFFF10000;
    const datatype max = 0x000F0000;
    static int initialized = 0;
    static datatype interval;
    static datatype lookup[LOOKUP_SIZE];

    // Calculate entire lookup table on first run. 
    if (!initialized) {
        interval = fix16_div(fix16_sub(max, min), fix16_from_int(LOOKUP_SIZE));
        int i;
        for (i = 0; i < LOOKUP_SIZE; ++i) {
            lookup[i] = genann_act_sigmoid(fix16_add(min, fix16_mul(interval, fix16_from_int(i))));
        }
        // This is down here to make this thread safe. 
        initialized = 1;
    }

    int i;
    i = fix16_to_int_cast(fix16_div(fix16_sub(a, min), interval)+0x00008000);
    if (i <= 0) return lookup[0];
    if (i >= LOOKUP_SIZE) return lookup[LOOKUP_SIZE-1];
    #endif
    return lookup[i];
}
*/

datatype genann_act_threshold(datatype a) {
    #if DATATYPE == 0 || DATATYPE == 1
    return a > 0;
    #elif DATATYPE == 2
    return (a > 0x00000000) ? 0x00010000 : 0x00000000;
    #endif
}


datatype genann_act_linear(datatype a) {
    return a;
}


genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs) {
    if (hidden_layers < 0) return 0;
    if (inputs < 1) return 0;
    if (outputs < 1) return 0;
    if (hidden_layers > 0 && hidden < 1) return 0;


    const int hidden_weights = hidden_layers ? (inputs+1) * hidden + (hidden_layers-1) * (hidden+1) * hidden : 0;
    const int output_weights = (hidden_layers ? (hidden+1) : (inputs+1)) * outputs;
    const int total_weights = (hidden_weights + output_weights);

    const int total_neurons = (inputs + hidden * hidden_layers + outputs);

    /* Allocate extra size for weights, outputs, and deltas. */
    const int size = sizeof(genann) + sizeof(datatype) * (total_weights + total_neurons + (total_neurons - inputs));
    genann *ret = malloc(size);
    if (!ret) return 0;

    ret->inputs = inputs;
    ret->hidden_layers = hidden_layers;
    ret->hidden = hidden;
    ret->outputs = outputs;

    ret->total_weights = total_weights;
    ret->total_neurons = total_neurons;

    /* Set pointers. */
    ret->weight = (datatype*)((char*)ret + sizeof(genann));
    ret->output = ret->weight + ret->total_weights;
    ret->delta = ret->output + ret->total_neurons;

    genann_randomize(ret);

    /*
    ret->activation_hidden = genann_act_sigmoid_cached;
    ret->activation_output = genann_act_sigmoid_cached;
    */
    ret->activation_hidden = genann_act_sigmoid;
    ret->activation_output = genann_act_sigmoid;
    return ret;
}


genann *genann_read(FILE *in) {
    int inputs, hidden_layers, hidden, outputs;
    fscanf(in, "%d %d %d %d", &inputs, &hidden_layers, &hidden, &outputs);

    genann *ann = genann_init(inputs, hidden_layers, hidden, outputs);

    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        #if DATATYPE == 0
        fscanf(in, " %le", ann->weight + i);
        #elif DATATYPE == 1
        fscanf(in, " %e", ann->weight + i);
        #elif DATATYPE == 2
        fscanf(in, " %u", ann->weight + i);
        #endif
    }

    return ann;
}


genann *genann_copy(genann const *ann) {
    const int size = sizeof(genann) + sizeof(datatype) * (ann->total_weights + ann->total_neurons + (ann->total_neurons - ann->inputs));
    genann *ret = malloc(size);
    if (!ret) return 0;

    memcpy(ret, ann, size);

    /* Set pointers. */
    ret->weight = (datatype*)((char*)ret + sizeof(genann));
    ret->output = ret->weight + ret->total_weights;
    ret->delta = ret->output + ret->total_neurons;

    return ret;
}

void genann_randomize(genann *ann) {
    #if DATATYPE == 0 || DATATYPE == 1
    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        datatype r = GENANN_RANDOM();
        /* Sets weights from -0.5 to 0.5. */
        ann->weight[i] = r - 0.5;
    }
    #elif DATATYPE == 2 
    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        datatype r = GENANN_RANDOM();
        /* Sets weights from -0.5 to 0.5. */
        ann->weight[i] = r - 0x00008000;
    }
    #endif
}


void genann_free(genann *ann) {
    /* The weight, output, and delta pointers go to the same buffer. */
    free(ann);
}


datatype const *genann_run(genann const *ann, datatype const *inputs) {
    #if DATATYPE == 0 || DATATYPE == 1
    datatype const *w = ann->weight;
    datatype *o = ann->output + ann->inputs;
    datatype const *i = ann->output;

    /* Copy the inputs to the scratch area, where we also store each neuron's
     * output, for consistency. This way the first layer isn't a special case. */
    memcpy(ann->output, inputs, sizeof(datatype) * ann->inputs);

    int h, j, k;

    const genann_actfun act = ann->activation_hidden;
    const genann_actfun acto = ann->activation_output;

    /* Figure hidden layers, if any. */
    for (h = 0; h < ann->hidden_layers; ++h) {
        for (j = 0; j < ann->hidden; ++j) {
            datatype sum = 0;
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    sum += *w * -1.0;
                    w++;
                } else {
                    sum += *w * i[k-1];
                    w++;
                }
            }
            *o = act(sum);
            o++;
        }
        i += (h == 0 ? ann->inputs : ann->hidden);
    }

    datatype const *ret = o;

    /* Figure output layer. */
    for (j = 0; j < ann->outputs; ++j) {
        datatype sum = 0;
        for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
            if (k == 0) {
                sum += *w * -1.0;
                w++;
            } else {
                sum += *w * i[k-1];
                w++;
            }
        }
        *o = acto(sum);
        o++;
    }

    /* Sanity check that we used all weights and wrote all outputs. */
    assert(w - ann->weight == ann->total_weights);
    assert(o - ann->output == ann->total_neurons);

    return ret;
    #elif DATATYPE == 2 
    datatype const *w = ann->weight;
    datatype *o = ann->output + ann->inputs;
    datatype const *i = ann->output;


    /* Copy the inputs to the scratch area, where we also store each neuron's
     * output, for consistency. This way the first layer isn't a special case. */
    memcpy(ann->output, inputs, sizeof(datatype) * ann->inputs);

    int h, j, k;

    const genann_actfun act = ann->activation_hidden;
    const genann_actfun acto = ann->activation_output;

    /* Figure hidden layers, if any. */
    for (h = 0; h < ann->hidden_layers; ++h) {
        for (j = 0; j < ann->hidden; ++j) {
            datatype sum = 0;
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    sum = fix16_add(sum,fix16_mul(*w, 0xFFFF0000));
                    w++;
                } else {
                    sum = fix16_add(sum, fix16_mul(*w, i[k-1]));
                    w++;
                }
            }
            *o = act(sum);
            o++;
        }
        i += (h == 0 ? ann->inputs : ann->hidden);
    }

    datatype const *ret = o;

    /* Figure output layer. */
    for (j = 0; j < ann->outputs; ++j) {
        datatype sum = 0;
        for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
            if (k == 0) {
                sum = fix16_add(sum, fix16_mul(*w, 0xFFFF0000));
                w++;
            } else {
                sum = fix16_add(sum, fix16_mul(*w, i[k-1]));
                w++;
            }
        }
        *o = acto(sum);
        o++;
    }

    /* Sanity check that we used all weights and wrote all outputs. */
    assert(w - ann->weight == ann->total_weights);
    assert(o - ann->output == ann->total_neurons);

    return ret;
    #endif
}


void genann_train(genann const *ann, datatype const *inputs, datatype const *desired_outputs, datatype learning_rate) {
    #if DATATYPE == 0 || DATATYPE == 1
   	/* To begin with, we must run the network forward. */
    genann_run(ann, inputs);

    int h, j, k;

    /* First set the output layer deltas. */
    {
        datatype const *o = ann->output + ann->inputs + ann->hidden * ann->hidden_layers; /* First output. */
        datatype *d = ann->delta + ann->hidden * ann->hidden_layers; /* First delta. */
        datatype const *t = desired_outputs; /* First desired output. */


        /* Set output layer deltas. */
        if (ann->activation_output == genann_act_linear) {
            for (j = 0; j < ann->outputs; ++j) {
                *d++ = *t++ - *o++;
            }
        } else {
            for (j = 0; j < ann->outputs; ++j) {
                *d++ = (*t - *o) * *o * (1.0 - *o);
                ++o; ++t;
            }
        }
    }


    /* Set hidden layer deltas, start on last layer and work backwards. */
    /* Note that loop is skipped in the case of hidden_layers == 0. */
    for (h = ann->hidden_layers - 1; h >= 0; --h) {

        /* Find first output and delta in this layer. */
        datatype const *o = ann->output + ann->inputs + (h * ann->hidden);
        datatype *d = ann->delta + (h * ann->hidden);

        /* Find first delta in following layer (which may be hidden or output). */
        datatype const * const dd = ann->delta + ((h+1) * ann->hidden);

        /* Find first weight in following layer (which may be hidden or output). */
        datatype const * const ww = ann->weight + ((ann->inputs+1) * ann->hidden) + ((ann->hidden+1) * ann->hidden * (h));

        for (j = 0; j < ann->hidden; ++j) {

            datatype delta = 0;

            for (k = 0; k < (h == ann->hidden_layers-1 ? ann->outputs : ann->hidden); ++k) {
                const datatype forward_delta = dd[k];
                const int windex = k * (ann->hidden + 1) + (j + 1);
                const datatype forward_weight = ww[windex];
                delta += forward_delta * forward_weight;
            }

            *d = *o * (1.0-*o) * delta;
            ++d; ++o;
        }
    }


    /* Train the outputs. */
    {
        /* Find first output delta. */
        datatype const *d = ann->delta + ann->hidden * ann->hidden_layers; /* First output delta. */

        /* Find first weight to first output delta. */
        datatype *w = ann->weight + (ann->hidden_layers
                ? ((ann->inputs+1) * ann->hidden + (ann->hidden+1) * ann->hidden * (ann->hidden_layers-1))
                : (0));

        /* Find first output in previous layer. */
        datatype const * const i = ann->output + (ann->hidden_layers
                ? (ann->inputs + (ann->hidden) * (ann->hidden_layers-1))
                : 0);

        /* Set output layer weights. */
        for (j = 0; j < ann->outputs; ++j) {
            for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
                if (k == 0) {
                    *w++ += *d * learning_rate * -1.0;
                } else {
                    *w++ += *d * learning_rate * i[k-1];
                }
            }

            ++d;
        }

        assert(w - ann->weight == ann->total_weights);
    }


    /* Train the hidden layers. */
    for (h = ann->hidden_layers - 1; h >= 0; --h) {

        /* Find first delta in this layer. */
        datatype const *d = ann->delta + (h * ann->hidden);

        /* Find first input to this layer. */
        datatype const *i = ann->output + (h
                ? (ann->inputs + ann->hidden * (h-1))
                : 0);

        /* Find first weight to this layer. */
        datatype *w = ann->weight + (h
                ? ((ann->inputs+1) * ann->hidden + (ann->hidden+1) * (ann->hidden) * (h-1))
                : 0);


        for (j = 0; j < ann->hidden; ++j) {
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    *w++ += *d * learning_rate * -1.0;
                } else {
                    *w++ += *d * learning_rate * i[k-1];
                }
            }
            ++d;
        }

    } 

    #elif DATATYPE == 2 
    /* To begin with, we must run the network forward. */
    genann_run(ann, inputs);

    int h, j, k;

    /* First set the output layer deltas. */
    {
        datatype const *o = ann->output + ann->inputs + ann->hidden * ann->hidden_layers; /* First output. */
        datatype *d = ann->delta + ann->hidden * ann->hidden_layers; /* First delta. */
        datatype const *t = desired_outputs; /* First desired output. */


        /* Set output layer deltas. */
        if (ann->activation_output == genann_act_linear) {
            for (j = 0; j < ann->outputs; ++j) {
                *d++ = *t++ - *o++;
            }
        } else {
            for (j = 0; j < ann->outputs; ++j) {
                *d++ = fix16_mul(fix16_mul(fix16_sub(*t,*o), *o), fix16_sub(0x00010000, *o));
                ++o; ++t;
            }
        }
    }


    /* Set hidden layer deltas, start on last layer and work backwards. */
    /* Note that loop is skipped in the case of hidden_layers == 0. */
    for (h = ann->hidden_layers - 1; h >= 0; --h) {

        /* Find first output and delta in this layer. */
        datatype const *o = ann->output + ann->inputs + (h * ann->hidden);
        datatype *d = ann->delta + (h * ann->hidden);

        /* Find first delta in following layer (which may be hidden or output). */
        datatype const * const dd = ann->delta + ((h+1) * ann->hidden);

        /* Find first weight in following layer (which may be hidden or output). */
        datatype const * const ww = ann->weight + ((ann->inputs+1) * ann->hidden) + ((ann->hidden+1) * ann->hidden * (h));

        for (j = 0; j < ann->hidden; ++j) {

            datatype delta = 0;

            for (k = 0; k < (h == ann->hidden_layers-1 ? ann->outputs : ann->hidden); ++k) {
                const datatype forward_delta = dd[k];
                const int windex = k * (ann->hidden + 1) + (j + 1);
                const datatype forward_weight = ww[windex];
                delta = fix16_add(delta,fix16_mul(forward_delta,forward_weight));
            }

            *d = fix16_mul(*o, fix16_mul(fix16_sub(0x00010000, *o), delta));
            ++d; ++o;
        }
    }


    /* Train the outputs. */
    {
        /* Find first output delta. */
        datatype const *d = ann->delta + ann->hidden * ann->hidden_layers; /* First output delta. */

        /* Find first weight to first output delta. */
        datatype *w = ann->weight + (ann->hidden_layers
                ? ((ann->inputs+1) * ann->hidden + (ann->hidden+1) * ann->hidden * (ann->hidden_layers-1))
                : (0));

        /* Find first output in previous layer. */
        datatype const * const i = ann->output + (ann->hidden_layers
                ? (ann->inputs + (ann->hidden) * (ann->hidden_layers-1))
                : 0);

        /* Set output layer weights. */
        for (j = 0; j < ann->outputs; ++j) {
            for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
                if (k == 0) {
                    *w = fix16_add(*w, fix16_mul(*d, fix16_mul(learning_rate, 0xFFFF0000)));
					w++;
                } else {
                    *w = fix16_add(*w, fix16_mul(*d, fix16_mul(learning_rate, i[k-1])));
					w++;
                }
            }
            ++d;
        }

        assert(w - ann->weight == ann->total_weights);
    }


    /* Train the hidden layers. */
    for (h = ann->hidden_layers - 1; h >= 0; --h) {

        /* Find first delta in this layer. */
        datatype const *d = ann->delta + (h * ann->hidden);

        /* Find first input to this layer. */
        datatype const *i = ann->output + (h
                ? (ann->inputs + ann->hidden * (h-1))
                : 0);

        /* Find first weight to this layer. */
        datatype *w = ann->weight + (h
                ? ((ann->inputs+1) * ann->hidden + (ann->hidden+1) * (ann->hidden) * (h-1))
                : 0);


        for (j = 0; j < ann->hidden; ++j) {
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    *w = fix16_add(*w, fix16_mul(*d, fix16_mul(learning_rate, 0xFFFF0000)));
					w++;
                } else {
                    *w = fix16_add(*w, fix16_mul(*d, fix16_mul(learning_rate, i[k-1])));
					w++;
                }
            }
            ++d;
        }

    }
    #endif
}

void genann_write(genann const *ann, FILE *out) {
    fprintf(out, "%d %d %d %d", ann->inputs, ann->hidden_layers, ann->hidden, ann->outputs);

    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        #if DATATYPE == 0 || DATATYPE == 1
        fprintf(out, " %.20e", ann->weight[i]);
        #elif DATATYPE == 2
        fprintf(out, " %u", ann->weight[i]);
        #endif
    }
}


