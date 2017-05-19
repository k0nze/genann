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

    #if DATATYPE == 0 || DATATYPE == 1
    if(strcmp(workclass, "?") == 0)                     { return 0.0; }
    else if(strcmp(workclass, "Private") == 0)          { return 1.0; }
    else if(strcmp(workclass, "Self-emp-not-inc") == 0) { return 2.0; }
    else if(strcmp(workclass, "Self-emp-inc") == 0)     { return 3.0; }
    else if(strcmp(workclass, "Federal-gov") == 0)      { return 4.0; }
    else if(strcmp(workclass, "Local-gov") == 0)        { return 5.0; }
    else if(strcmp(workclass, "State-gov") == 0)        { return 6.0; }
    else if(strcmp(workclass, "Without-pay") == 0)      { return 7.0; }
    else if(strcmp(workclass, "Never-worked") == 0)     { return 8.0; }
    #elif DATATYPE == 2
    if(strcmp(workclass, "?") == 0)                     { return 0x00000000; }
    else if(strcmp(workclass, "Private") == 0)          { return 0x00010000; }
    else if(strcmp(workclass, "Self-emp-not-inc") == 0) { return 0x00020000; }
    else if(strcmp(workclass, "Self-emp-inc") == 0)     { return 0x00030000; }
    else if(strcmp(workclass, "Federal-gov") == 0)      { return 0x00040000; }
    else if(strcmp(workclass, "Local-gov") == 0)        { return 0x00050000; }
    else if(strcmp(workclass, "State-gov") == 0)        { return 0x00060000; }
    else if(strcmp(workclass, "Without-pay") == 0)      { return 0x00070000; }
    else if(strcmp(workclass, "Never-worked") == 0)     { return 0x00080000; }
    #endif
    else {
        fprintf(stderr, "workclass %s not found\n", workclass);
        exit(1);
    }
}

datatype convert_education(const char *education) {
    #if DATATYPE == 0 || DATATYPE == 1
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
    #elif DATATYPE == 2
    if(strcmp(education, "?") == 0)                 { return 0x00000000; }
    else if(strcmp(education, "Bachelors") == 0)    { return 0x00010000; }
    else if(strcmp(education, "Some-college") == 0) { return 0x00020000; }
    else if(strcmp(education, "11th") == 0)         { return 0x00030000; }
    else if(strcmp(education, "HS-grad") == 0)      { return 0x00040000; }
    else if(strcmp(education, "Prof-school") == 0)  { return 0x00050000; }
    else if(strcmp(education, "Assoc-acdm") == 0)   { return 0x00060000; }
    else if(strcmp(education, "Assoc-voc") == 0)    { return 0x00070000; }
    else if(strcmp(education, "9th") == 0)          { return 0x00080000; }
    else if(strcmp(education, "7th-8th") == 0)      { return 0x00090000; }
    else if(strcmp(education, "12th") == 0)         { return 0x000A0000; }
    else if(strcmp(education, "Masters") == 0)      { return 0x000B0000; }
    else if(strcmp(education, "1st-4th") == 0)      { return 0x000C0000; }
    else if(strcmp(education, "10th") == 0)         { return 0x000D0000; }
    else if(strcmp(education, "Doctorate") == 0)    { return 0x000E0000; }
    else if(strcmp(education, "5th-6th") == 0)      { return 0x000F0000; }
    else if(strcmp(education, "Preschool") == 0)    { return 0x00100000; }
    #endif
    else {
        fprintf(stderr, "education %s not found\n", education);
        exit(1);
    }
}

datatype convert_martial_status(const char *martial_status) {
    #if DATATYPE == 0 || DATATYPE == 1
    if(strcmp(martial_status, "?") == 0)                            { return 0.0; }
    else if(strcmp(martial_status, "Married-civ-spouse") == 0)      { return 1.0; }
    else if(strcmp(martial_status, "Divorced") == 0)                { return 2.0; }
    else if(strcmp(martial_status, "Never-married") == 0)           { return 3.0; }
    else if(strcmp(martial_status, "Separated") == 0)               { return 4.0; }
    else if(strcmp(martial_status, "Widowed") == 0)                 { return 5.0; }
    else if(strcmp(martial_status, "Married-spouse-absent") == 0)   { return 6.0; }
    else if(strcmp(martial_status, "Married-AF-spouse") == 0)       { return 7.0; }
    #elif DATATYPE == 2
    if(strcmp(martial_status, "?") == 0)                            { return 0x00000000; }
    else if(strcmp(martial_status, "Married-civ-spouse") == 0)      { return 0x00010000; }
    else if(strcmp(martial_status, "Divorced") == 0)                { return 0x00020000; }
    else if(strcmp(martial_status, "Never-married") == 0)           { return 0x00030000; }
    else if(strcmp(martial_status, "Separated") == 0)               { return 0x00040000; }
    else if(strcmp(martial_status, "Widowed") == 0)                 { return 0x00050000; }
    else if(strcmp(martial_status, "Married-spouse-absent") == 0)   { return 0x00060000; }
    else if(strcmp(martial_status, "Married-AF-spouse") == 0)       { return 0x00070000; }
    #endif
    else {
        fprintf(stderr, "martial-status %s not found\n", martial_status);
        exit(1);
    }
}

datatype convert_occupation(const char *occupation) {
    #if DATATYPE == 0 || DATATYPE == 1
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
    #elif DATATYPE == 2
    if(strcmp(occupation, "?") == 0)                        { return 0x00000000; }
    else if(strcmp(occupation, "Tech-support") == 0)        { return 0x00010000; }
    else if(strcmp(occupation, "Craft-repair") == 0)        { return 0x00020000; }
    else if(strcmp(occupation, "Other-service") == 0)       { return 0x00030000; }
    else if(strcmp(occupation, "Sales") == 0)               { return 0x00040000; }
    else if(strcmp(occupation, "Exec-managerial") == 0)     { return 0x00050000; }
    else if(strcmp(occupation, "Prof-specialty") == 0)      { return 0x00060000; }
    else if(strcmp(occupation, "Handlers-cleaners") == 0)   { return 0x00070000; }
    else if(strcmp(occupation, "Machine-op-inspct") == 0)   { return 0x00080000; }
    else if(strcmp(occupation, "Adm-clerical") == 0)        { return 0x00090000; }
    else if(strcmp(occupation, "Farming-fishing") == 0)     { return 0x000A0000; }
    else if(strcmp(occupation, "Transport-moving") == 0)    { return 0x000B0000; }
    else if(strcmp(occupation, "Priv-house-serv") == 0)     { return 0x000C0000; }
    else if(strcmp(occupation, "Protective-serv") == 0)     { return 0x000D0000; }
    else if(strcmp(occupation, "Armed-Forces") == 0)        { return 0x000E0000; }
    #endif
    else {
        fprintf(stderr, "occupation %s not found\n", occupation);
        exit(1);
    }
}

datatype convert_relationship(const char *relationship) {
    #if DATATYPE == 0 || DATATYPE == 1
    if(strcmp(relationship, "?") == 0)                      { return 0.0; }
    else if(strcmp(relationship, "Wife") == 0)              { return 1.0; }
    else if(strcmp(relationship, "Own-child") == 0)         { return 2.0; }
    else if(strcmp(relationship, "Husband") == 0)           { return 3.0; }
    else if(strcmp(relationship, "Not-in-family") == 0)     { return 4.0; }
    else if(strcmp(relationship, "Other-relative") == 0)    { return 5.0; }
    else if(strcmp(relationship, "Unmarried") == 0)         { return 6.0; }
    #elif DATATYPE == 2
    if(strcmp(relationship, "?") == 0)                      { return 0x00000000; }
    else if(strcmp(relationship, "Wife") == 0)              { return 0x00010000; }
    else if(strcmp(relationship, "Own-child") == 0)         { return 0x00020000; }
    else if(strcmp(relationship, "Husband") == 0)           { return 0x00030000; }
    else if(strcmp(relationship, "Not-in-family") == 0)     { return 0x00040000; }
    else if(strcmp(relationship, "Other-relative") == 0)    { return 0x00050000; }
    else if(strcmp(relationship, "Unmarried") == 0)         { return 0x00060000; }
    #endif
    else {
        fprintf(stderr, "relationship %s not found\n", relationship);
        exit(1);
    }
}

datatype convert_race(const char *race) {
    #if DATATYPE == 0 || DATATYPE == 1
    if(strcmp(race, "?") == 0)                          { return 0.0; }
    else if(strcmp(race, "White") == 0)                 { return 1.0; }
    else if(strcmp(race, "Asian-Pac-Islander") == 0)    { return 2.0; }
    else if(strcmp(race, "Amer-Indian-Eskimo") == 0)    { return 3.0; }
    else if(strcmp(race, "Other") == 0)                 { return 4.0; }
    else if(strcmp(race, "Black") == 0)                 { return 5.0; }
    #elif DATATYPE == 2
    if(strcmp(race, "?") == 0)                          { return 0x00000000; }
    else if(strcmp(race, "White") == 0)                 { return 0x00010000; }
    else if(strcmp(race, "Asian-Pac-Islander") == 0)    { return 0x00020000; }
    else if(strcmp(race, "Amer-Indian-Eskimo") == 0)    { return 0x00030000; }
    else if(strcmp(race, "Other") == 0)                 { return 0x00040000; }
    else if(strcmp(race, "Black") == 0)                 { return 0x00050000; }
    #endif
    else {
        fprintf(stderr, "race %s not found\n", race);
        exit(1);
    }
}

datatype convert_sex(const char *sex) {
    #if DATATYPE == 0 || DATATYPE == 1
    if(strcmp(sex, "?") == 0)           { return 0.0; }
    else if(strcmp(sex, "Female") == 0) { return 1.0; }
    else if(strcmp(sex, "Male") == 0)   { return 2.0; }
    #elif DATATYPE == 2
    if(strcmp(sex, "?") == 0)           { return 0x00000000; }
    else if(strcmp(sex, "Female") == 0) { return 0x0001000; }
    else if(strcmp(sex, "Male") == 0)   { return 0x0002000; }
    #endif
    else {
        fprintf(stderr, "sex %s not found\n", sex);
        exit(1);
    }
}

datatype convert_native_country(const char *native_country) {
    #if DATATYPE == 0 || DATATYPE == 1
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
    #elif DATATYPE == 2
    if(strcmp(native_country, "?") == 0)                        { return 0x00000000; }
    else if(strcmp(native_country, "United-States") == 0)       { return 0x00010000; }
    else if(strcmp(native_country, "Cambodia") == 0)            { return 0x00020000; }
    else if(strcmp(native_country, "England") == 0)             { return 0x00030000; }
    else if(strcmp(native_country, "Puerto-Rico") == 0)         { return 0x00040000; }
    else if(strcmp(native_country, "Canada") == 0)              { return 0x00050000; }
    else if(strcmp(native_country, "Germany") == 0)             { return 0x00060000; }
    else if(strcmp(native_country, "Outlying-US(Guam-USVI-etc)") == 0)   { return 0x00070000; }
    else if(strcmp(native_country, "India") == 0)               { return 0x00080000; }
    else if(strcmp(native_country, "Japan") == 0)               { return 0x00090000; }
    else if(strcmp(native_country, "Greece") == 0)              { return 0x000A0000; }
    else if(strcmp(native_country, "South") == 0)               { return 0x000B0000; }
    else if(strcmp(native_country, "China") == 0)               { return 0x000C0000; }
    else if(strcmp(native_country, "Cuba") == 0)                { return 0x000D0000; }
    else if(strcmp(native_country, "Iran") == 0)                { return 0x000E0000; }
    else if(strcmp(native_country, "Honduras") == 0)            { return 0x000F0000; }
    else if(strcmp(native_country, "Philippines") == 0)         { return 0x00100000; }
    else if(strcmp(native_country, "Italy") == 0)               { return 0x00110000; }
    else if(strcmp(native_country, "Poland") == 0)              { return 0x00120000; }
    else if(strcmp(native_country, "Jamaica") == 0)             { return 0x00130000; }
    else if(strcmp(native_country, "Vietnam") == 0)             { return 0x00140000; }
    else if(strcmp(native_country, "Mexico") == 0)              { return 0x00150000; }
    else if(strcmp(native_country, "Portugal") == 0)            { return 0x00160000; }
    else if(strcmp(native_country, "Ireland") == 0)             { return 0x00170000; }
    else if(strcmp(native_country, "France") == 0)              { return 0x00180000; }
    else if(strcmp(native_country, "Dominican-Republic") == 0)  { return 0x00190000; }
    else if(strcmp(native_country, "Laos") == 0)                { return 0x001A0000; }
    else if(strcmp(native_country, "Ecuador") == 0)             { return 0x001B0000; }
    else if(strcmp(native_country, "Taiwan") == 0)              { return 0x001C0000; }
    else if(strcmp(native_country, "Haiti") == 0)               { return 0x001D0000; }
    else if(strcmp(native_country, "Columbia") == 0)            { return 0x001E0000; }
    else if(strcmp(native_country, "Hungary") == 0)             { return 0x001F0000; }
    else if(strcmp(native_country, "Guatemala") == 0)           { return 0x00200000; }
    else if(strcmp(native_country, "Nicaragua") == 0)           { return 0x00210000; }
    else if(strcmp(native_country, "Scotland") == 0)            { return 0x00220000; }
    else if(strcmp(native_country, "Thailand") == 0)            { return 0x00230000; }
    else if(strcmp(native_country, "Yugoslavia") == 0)          { return 0x00240000; }
    else if(strcmp(native_country, "El-Salvador") == 0)         { return 0x00250000; }
    else if(strcmp(native_country, "Trinadad&Tobago") == 0)     { return 0x00260000; }
    else if(strcmp(native_country, "Peru") == 0)                { return 0x00270000; }
    else if(strcmp(native_country, "Hong") == 0)                { return 0x00280000; }
    else if(strcmp(native_country, "Holand-Netherlands") == 0)  { return 0x00290000; }
    #endif
    else {
        fprintf(stderr, "native-country %s not found\n", native_country);
        exit(1);
    }
}

int main(int argc, char** argv) {

    #ifdef DEBUG
    printf("GENANN ADULT benchmark.\n");
    printf("Train an ANN on the ADULT dataset using backpropagation.\n");
    #endif

    int hidden_layers = 8;
    int neurons_per_hidden_layer = 8;
    int training_loops = 2500;

    if(argc == 4) {
        hidden_layers = atoi(argv[1]);
        neurons_per_hidden_layer = atoi(argv[2]);
        training_loops = atoi(argv[3]);
    }

    #if DATATYPE == 0 | DATATYPE == 1
    const char *adult_data = "adult.data";
    #elif DATATYPE == 2
    const char *adult_data = "adult.fix16.data";
    #endif

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
                    input[13*i+0] = atof(split);
                    break;
                case 1:
                    // workclass
                    input[13*i+1] = convert_workclass(split);
                    break;
                case 2:
                    // fnlwgt
                    input[13*i+2] = atof(split);
                    break;
                case 3:
                    // education skip (take education num instead)
                    break;
                case 4:
                    // education-num
                    input[13*i+3] = atof(split);
                    break;
                case 5:
                    // martial-status
                    input[13*i+4] = convert_martial_status(split);
                    break;
                case 6:
                    // occupation
                    input[13*i+5] = convert_occupation(split);
                    break;
                case 7:
                    // relationship
                    input[13*i+6] = convert_relationship(split);
                    break;
                case 8:
                    // race
                    input[13*i+7] = convert_race(split);
                    break;
                case 9:
                    // sex
                    input[13*i+8] = convert_sex(split);
                    break;
                case 10:
                    // capital-gain
                    input[13*i+9] = atof(split);
                    break;
                case 11:
                    // capital-loss
                    input[13*i+10] = atof(split);
                    break;
                case 12:
                    // hours-per-week
                    input[13*i+11] = atof(split);
                    break;
                case 13:
                    // native-country
                    input[13*i+12] = convert_native_country(split);
                    break;
                case 14:
                    // output: income
                    // class[0] == <=50K
                    // class[1] == >50K
                    #if DATATYPE == 0 || DATATYPE == 1
                    if(strcmp(split, "<=50K\n") == 0 ) { class[2*i+0] = 1.0; class[2*i+1] = 0.0;}
                    else {class[2*i+0] = 0.0; class[2*i+1] = 1.0;}
                    #elif DATATYPE == 2
                    if(strcmp(split, "<=50K\n") == 0 ) { class[2*i+0] = 0x00010000; class[2*i+1] = 0x00000000;}
                    else {class[2*i+0] = 0x00000000; class[2*i+1] = 0x00010000;}
                    #endif
                    break;
            }
            split = strtok(0, ", ");
        }
        i++;
    }

    // init neural network
    genann *ann = genann_init(13, hidden_layers, neurons_per_hidden_layer, 2);

    // train neural network 
    int loops = training_loops;

    #ifdef DEBUG
    printf("Training for %d loops over data.\n", loops);
    printf("With %d hidden layers and %d neurons per hidden layer.\n", hidden_layers, neurons_per_hidden_layer);
    int counter = 0;
    int percent = 0;
    printf("0%%");
    fflush(stdout);
    #endif
    
    for(i = 0; i < loops; i++) {
        for(j = 0; j < samples; j++) {
            #if DATATYPE == 0 || DATATYPE == 1
            genann_train(ann, input+j*13, class+j*2, .5);
            #elif DATATYPE == 2
            genann_train(ann, input+j*13, class+j*2, 0x0000028F);
            #endif
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
        #if DATATYPE == 0 || DATATYPE == 1
        if((class[j*2] == 1.0) && (guess[0] > guess[1])) {
            correct++; 
        } else if ((class[j*2+1] == 1.0) && (guess[0] < guess[1])) {
            correct++;
        }
        #elif DATATYPE == 2
        if((class[j*2] == 0x00010000) && (guess[0] > guess[1])) {
            correct++; 
        } else if ((class[j*2+1] == 0x00010000) && (guess[0] < guess[1])) {
            correct++;
        }
        #endif
    }

    printf("%d/%d error rate: %0.1f%%\n", correct, samples, 100.0 - ((float)correct / samples * 100.0));

    free(input);
    free(class);
    genann_free(ann);

    return 0;
}
