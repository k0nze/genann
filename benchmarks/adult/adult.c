#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "genann.h"

#define DEBUG

/**
 * >50K, <=50K
 *
 * age: continuous.
 * workclass: Private, Self-emp-not-inc, Self-emp-inc, Federal-gov, Local-gov,
 * State-gov, Without-pay, Never-worked.
 * fnlwgt: continuous.
 * education: Bachelors, Some-college, 11th, HS-grad, Prof-school, Assoc-acdm,
 * Assoc-voc, 9th, 7th-8th, 12th, Masters, 1st-4th, 10th, Doctorate, 5th-6th,
 * Preschool.
 * education-num: continuous.
 * marital-status: Married-civ-spouse, Divorced, Never-married, Separated,
 * Widowed, Married-spouse-absent, Married-AF-spouse.
 * occupation: Tech-support, Craft-repair, Other-service, Sales,
 * Exec-managerial, Prof-specialty, Handlers-cleaners, Machine-op-inspct,
 * Adm-clerical, Farming-fishing, Transport-moving, Priv-house-serv,
 * Protective-serv, Armed-Forces.
 * relationship: Wife, Own-child, Husband, Not-in-family, Other-relative,
 * Unmarried.
 * race: White, Asian-Pac-Islander, Amer-Indian-Eskimo, Other, Black.
 * sex: Female, Male.
 * capital-gain: continuous.
 * capital-loss: continuous.
 * hours-per-week: continuous.
 * native-country: United-States, Cambodia, England, Puerto-Rico, Canada,
 * Germany, Outlying-US(Guam-USVI-etc), India, Japan, Greece, South, China,
 * Cuba, Iran, Honduras, Philippines, Italy, Poland, Jamaica, Vietnam, Mexico,
 * Portugal, Ireland, France, Dominican-Republic, Laos, Ecuador, Taiwan, Haiti,
 * Columbia, Hungary, Guatemala, Nicaragua, Scotland, Thailand, Yugoslavia,
 * El-Salvador, Trinadad&Tobago, Peru, Hong, Holand-Netherlands.
 */


datatype convert_workclass(const char *workclass) {
    if(strcmp(workclass, "?") == 0)                     { return 0.0; }
    else if(strcmp(workclass, "Private") == 0)          { return 1.0; }
    else if(strcmp(workclass, "Self-emp-not-inc") == 0) { return 2.0; }
    else if(strcmp(workclass, "Self-emp-inc") == 0)     { return 3.0; }
    else if(strcmp(workclass, "Federal-gov") == 0)      { return 4.0; }
    else if(strcmp(workclass, "Local-gov") == 0)        { return 5.0; }
    else if(strcmp(workclass, "State-gov") == 0)        { return 6.0; }
    else if(strcmp(workclass, "Without-pay") == 0)      { return 7.0; }
    else if(strcmp(workclass, "Never-worked") == 0)     { return 8.0; }
    else {
        fprintf(stderr, "workclass %s not found\n", workclass);
        exit(1);
    }
}

datatype convert_education(const char *education) {
    if(strcmp(education, "?") == 0)                 { return 0.0; }
    else if(strcmp(education, "Bachelors") == 0)    { return 1.0; }
    else if(strcmp(education, "Some-college") == 0) { return 2.0; }
    else if(strcmp(education, "11th") == 0)         { return 3.0; }
    else if(strcmp(education, "HS-grad") == 0)      { return 4.0; }
    else if(strcmp(education, "Prof-school") == 0)  { return 5.0; }
    else if(strcmp(education, "Assoc-acdm") == 0)   { return 6.0; }
    else if(strcmp(education, "Assoc-voc") == 0)    { return 7.0; }
    else if(strcmp(education, "9th") == 0)          { return 8.0; }
    else if(strcmp(education, "7th-8th") == 0)      { return 9.0; }
    else if(strcmp(education, "12th") == 0)         { return 10.0; }
    else if(strcmp(education, "Masters") == 0)      { return 11.0; }
    else if(strcmp(education, "1st-4th") == 0)      { return 12.0; }
    else if(strcmp(education, "10th") == 0)         { return 13.0; }
    else if(strcmp(education, "Doctorate") == 0)    { return 14.0; }
    else if(strcmp(education, "5th-6th") == 0)      { return 15.0; }
    else if(strcmp(education, "Preschool") == 0)    { return 16.0; }
    else {
        fprintf(stderr, "education %s not found\n", education);
        exit(1);
    }
}

datatype convert_martial_status(const char *martial_status) {
    if(strcmp(martial_status, "?") == 0)                            { return 0.0; }
    else if(strcmp(martial_status, "Married-civ-spouse") == 0)      { return 1.0; }
    else if(strcmp(martial_status, "Divorced") == 0)                { return 2.0; }
    else if(strcmp(martial_status, "Never-married") == 0)           { return 3.0; }
    else if(strcmp(martial_status, "Separated") == 0)               { return 4.0; }
    else if(strcmp(martial_status, "Widowed") == 0)                 { return 5.0; }
    else if(strcmp(martial_status, "Married-spouse-absent") == 0)   { return 6.0; }
    else if(strcmp(martial_status, "Married-AF-spouse") == 0)       { return 7.0; }
    else {
        fprintf(stderr, "martial-status %s not found\n", martial_status);
        exit(1);
    }
}

datatype convert_occupation(const char *occupation) {
    if(strcmp(occupation, "?") == 0)                        { return 0.0; }
    else if(strcmp(occupation, "Tech-support") == 0)        { return 1.0; }
    else if(strcmp(occupation, "Craft-repair") == 0)        { return 2.0; }
    else if(strcmp(occupation, "Other-service") == 0)       { return 3.0; }
    else if(strcmp(occupation, "Sales") == 0)               { return 4.0; }
    else if(strcmp(occupation, "Exec-managerial") == 0)     { return 5.0; }
    else if(strcmp(occupation, "Prof-specialty") == 0)      { return 6.0; }
    else if(strcmp(occupation, "Handlers-cleaners") == 0)   { return 7.0; }
    else if(strcmp(occupation, "Machine-op-inspct") == 0)   { return 8.0; }
    else if(strcmp(occupation, "Adm-clerical") == 0)        { return 9.0; }
    else if(strcmp(occupation, "Farming-fishing") == 0)     { return 10.0; }
    else if(strcmp(occupation, "Transport-moving") == 0)    { return 11.0; }
    else if(strcmp(occupation, "Priv-house-serv") == 0)     { return 12.0; }
    else if(strcmp(occupation, "Protective-serv") == 0)     { return 13.0; }
    else if(strcmp(occupation, "Armed-Forces") == 0)        { return 14.0; }
    else {
        fprintf(stderr, "occupation %s not found\n", occupation);
        exit(1);
    }
}

datatype convert_relationship(const char *relationship) {
    if(strcmp(relationship, "?") == 0)                      { return 0.0; }
    else if(strcmp(relationship, "Wife") == 0)              { return 1.0; }
    else if(strcmp(relationship, "Own-child") == 0)         { return 2.0; }
    else if(strcmp(relationship, "Husband") == 0)           { return 3.0; }
    else if(strcmp(relationship, "Not-in-family") == 0)     { return 4.0; }
    else if(strcmp(relationship, "Other-relative") == 0)    { return 5.0; }
    else if(strcmp(relationship, "Unmarried") == 0)         { return 6.0; }
    else {
        fprintf(stderr, "relationship %s not found\n", relationship);
        exit(1);
    }
}

datatype convert_race(const char *race) {
    if(strcmp(race, "?") == 0)                          { return 0.0; }
    else if(strcmp(race, "White") == 0)                 { return 1.0; }
    else if(strcmp(race, "Asian-Pac-Islander") == 0)    { return 2.0; }
    else if(strcmp(race, "Amer-Indian-Eskimo") == 0)    { return 3.0; }
    else if(strcmp(race, "Other") == 0)                 { return 4.0; }
    else if(strcmp(race, "Black") == 0)                 { return 5.0; }
    else {
        fprintf(stderr, "race %s not found\n", race);
        exit(1);
    }
}

datatype convert_sex(const char *sex) {
    if(strcmp(sex, "?") == 0)           { return 0.0; }
    else if(strcmp(sex, "Female") == 0) { return 1.0; }
    else if(strcmp(sex, "Male") == 0)   { return 2.0; }
    else {
        fprintf(stderr, "sex %s not found\n", sex);
        exit(1);
    }
}

datatype convert_native_country(const char *native_country) {
    if(strcmp(native_country, "?") == 0)                        { return 0.0; }
    else if(strcmp(native_country, "United-States") == 0)       { return 1.0; }
    else if(strcmp(native_country, "Cambodia") == 0)            { return 2.0; }
    else if(strcmp(native_country, "England") == 0)             { return 3.0; }
    else if(strcmp(native_country, "Puerto-Rico") == 0)         { return 4.0; }
    else if(strcmp(native_country, "Canada") == 0)              { return 5.0; }
    else if(strcmp(native_country, "Germany") == 0)             { return 6.0; }
    else if(strcmp(native_country, "Outlying-US(Guam-USVI-etc)") == 0)   { return 7.0; }
    else if(strcmp(native_country, "India") == 0)               { return 8.0; }
    else if(strcmp(native_country, "Japan") == 0)               { return 9.0; }
    else if(strcmp(native_country, "Greece") == 0)              { return 10.0; }
    else if(strcmp(native_country, "South") == 0)               { return 11.0; }
    else if(strcmp(native_country, "China") == 0)               { return 12.0; }
    else if(strcmp(native_country, "Cuba") == 0)                { return 13.0; }
    else if(strcmp(native_country, "Iran") == 0)                { return 14.0; }
    else if(strcmp(native_country, "Honduras") == 0)            { return 15.0; }
    else if(strcmp(native_country, "Philippines") == 0)         { return 16.0; }
    else if(strcmp(native_country, "Italy") == 0)               { return 17.0; }
    else if(strcmp(native_country, "Poland") == 0)              { return 18.0; }
    else if(strcmp(native_country, "Jamaica") == 0)             { return 19.0; }
    else if(strcmp(native_country, "Vietnam") == 0)             { return 20.0; }
    else if(strcmp(native_country, "Mexico") == 0)              { return 21.0; }
    else if(strcmp(native_country, "Portugal") == 0)            { return 22.0; }
    else if(strcmp(native_country, "Ireland") == 0)             { return 23.0; }
    else if(strcmp(native_country, "France") == 0)              { return 24.0; }
    else if(strcmp(native_country, "Dominican-Republic") == 0)  { return 25.0; }
    else if(strcmp(native_country, "Laos") == 0)                { return 26.0; }
    else if(strcmp(native_country, "Ecuador") == 0)             { return 27.0; }
    else if(strcmp(native_country, "Taiwan") == 0)              { return 28.0; }
    else if(strcmp(native_country, "Haiti") == 0)               { return 29.0; }
    else if(strcmp(native_country, "Columbia") == 0)            { return 30.0; }
    else if(strcmp(native_country, "Hungary") == 0)             { return 31.0; }
    else if(strcmp(native_country, "Guatemala") == 0)           { return 32.0; }
    else if(strcmp(native_country, "Nicaragua") == 0)           { return 33.0; }
    else if(strcmp(native_country, "Scotland") == 0)            { return 34.0; }
    else if(strcmp(native_country, "Thailand") == 0)            { return 35.0; }
    else if(strcmp(native_country, "Yugoslavia") == 0)          { return 36.0; }
    else if(strcmp(native_country, "El-Salvador") == 0)         { return 37.0; }
    else if(strcmp(native_country, "Trinadad&Tobago") == 0)     { return 38.0; }
    else if(strcmp(native_country, "Peru") == 0)                { return 39.0; }
    else if(strcmp(native_country, "Hong") == 0)                { return 40.0; }
    else if(strcmp(native_country, "Holand-Netherlands") == 0)  { return 41.0; }
    else {
        fprintf(stderr, "native-country %s not found\n", native_country);
        exit(1);
    }
}

int main() {

    #ifdef DEBUG
    printf("GENANN ADULT benchmark.\n");
    printf("Train an ANN on the ADULT dataset using backpropagation.\n");
    #endif


    const char *adult_data = "adult.data";
    FILE *in = fopen(adult_data, "r");
    if (!in) {
        fprintf(stderr, "Could not open file: %s\n", adult_data);
        exit(1);
    }

    // loop through data to count rows
    char line[1024];
    int samples = 0;
    while (!feof(in) && fgets(line, 1024, in)) {
        samples++;
    }

    fseek(in, 0, SEEK_SET);

    datatype *input = malloc(sizeof(datatype)*13*samples);
    datatype *class = malloc(sizeof(datatype)*2*samples);

    // loop through data
    int i,j;
    i = 0;
    while (!feof(in) && fgets(line, 1024, in)) {
        char *split = strtok(line, ", ");
        for (j = 0; j < 15; j++) {
            switch(j) {
                case 0:
                    // age
                    //printf("%s, ", split); 
                    input[13*i+0] = atof(split);
                    break;
                case 1:
                    // workclass
                    input[13*i+1] = convert_workclass(split);
                    //printf("%s %f, ", split, input[1]);
                    break;
                case 2:
                    // fnlwgt
                    //printf("%s, ", split); 
                    input[13*i+2] = atof(split);
                    break;
                case 3:
                    // education skip (take education num instead)
                    break;
                case 4:
                    // education-num
                    input[13*i+3] = atof(split);
                    //printf("%f, ", input[3]);
                    break;
                case 5:
                    // martial-status
                    input[13*i+4] = convert_martial_status(split);
                    //printf("%s %f, ", split, input[4]);
                    break;
                case 6:
                    // occupation
                    input[13*i+5] = convert_occupation(split);
                    //printf("%s %f, ", split, input[5]);
                    break;
                case 7:
                    // relationship
                    input[13*i+6] = convert_relationship(split);
                    //printf("%s %f, ", split, input[6]);
                    break;
                case 8:
                    // race
                    input[13*i+7] = convert_race(split);
                    //printf("%s %f, ", split, input[7]);
                    break;
                case 9:
                    // sex
                    input[13*i+8] = convert_sex(split);
                    //printf("%s %f, ", split, input[8]);
                    break;
                case 10:
                    // capital-gain
                    input[13*i+9] = atof(split);
                    //printf("%f, ", input[9]);
                    break;
                case 11:
                    // capital-loss
                    input[13*i+10] = atof(split);
                    //printf("%f, ", input[10]);
                    break;
                case 12:
                    // hours-per-week
                    input[13*i+11] = atof(split);
                    //printf("%f, ", input[11]);
                    break;
                case 13:
                    // native-country
                    input[13*i+12] = convert_native_country(split);
                    //printf("%s %f, ", split, input[12]);
                    break;
                case 14:
                    // output: income
                    // class[0] == <=50K
                    // class[1] == >50K
                    if(strcmp(split, "<=50K\n") == 0 ) { class[i+0] = 1.0; class[i+1] = 0.0;}
                    else {class[i+0] = 0.0; class[i+1] = 1.0;}
                    break;
            }
            split = strtok(0, ", ");
        }
        i++;
        //printf("\n");
    }

    // init neural network
    genann *ann = genann_init(13, 4, 13, 2);

    // train neural network 
    int loops = 5000;

    #ifdef DEBUG
    printf("Training for %d loops over data.\n", loops);
    int counter = 0;
    int percent = 0;
    printf("0%%");
    fflush(stdout);
    #endif
    
    for(i = 0; i < loops; i++) {
        for(j = 0; j < samples; j++) {
            genann_train(ann, input+j*13, class+j*2, .01);
        }

        #ifdef DEBUG
        if(counter > loops/10) {
            counter = 0;
            percent += 10;
            printf("...%d%%", percent);
            fflush(stdout);
        }
        counter++;
        #endif
    }
    #ifdef DEBUG
    printf("...100%%\n");
    #endif

    // classify
    int correct = 0;

    for (j = 0; j < samples; j++) {
        const datatype *guess = genann_run(ann, input+j*13);
        if((class[j*2] == 1.0) && (guess[0] > guess[1])) {
            correct++; 
        } else if ((class[j*2+1] == 1.0) && (guess[0] < guess[1])) {
            correct++;
        }
    }

    printf("%d/%d error rate: %0.1f%%\n", correct, samples, 100.0 - ((float)correct / samples * 100.0));

    free(input);
    free(class);
    genann_free(ann);

    return 0;
}
