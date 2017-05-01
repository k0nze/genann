#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libfixmath/fix16.h" 

void syntax_msg() {
    printf("DESCRIPTION:\n");
    printf("\tConvertes floating point numbers in a CSV file into the unsigned integer\n");
    printf("\trepresentation for fix16_t.\n\n");
    printf("SYNTAX:\n");
    printf("\tfloat_to_fixed_csv INPUT_CSV OUTPUT_CSV\n\n");
    printf("INPUT_CSV:\n");
    printf("\tFile from which the floating point numbers should be converted to fixed point.\n\n");
    printf("OUTPUT_CSV:\n");
    printf("\tFile in which the converted fixed point number should be written.\n\n");
    printf("OPITONS:\n");
    printf("\t-h | --help : displays this text\n");
}

// TODO it works, however it needs improvement
int is_number(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        if((isdigit(str[i]) == 0) && (str[i] != '-') && (str[i] != '.')) {
            return 0;
        }
        i++;
    }
    if(i == 0) {
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc == 2) {
        if(strcmp(argv[1], "-h") == 0 ||strcmp(argv[1], "--help") == 0) {
            syntax_msg();
            return 0;
        }
        fprintf(stderr, "no file paths were given\n");
        return 1;
    }

    if(argc != 3) {
        fprintf(stderr, "no file paths were given\n");
        return 1;
    }


    char* input_file_path = argv[1];
    char* output_file_path = argv[2];

    FILE *input = fopen(input_file_path, "r");
    if (!input) {
        printf("Could not open input file: %s\n", input_file_path);
        return 1;
    }

    FILE *output = fopen(output_file_path, "w+");
    if (!output) {
        fclose(input);
        printf("Could not open output file: %s\n", input_file_path);
        return 1;
    }

    /* get first line and count columns */
    int columns = 1;
    char input_line[1024];
    fgets(input_line, 1024, input);

    int i;
    for(i = 0; i < 1024 && input_line[i] != '\n'; i++) {
        if(input_line[i] == ',') {
            columns++;
        }
    }

    fseek(input, 0, SEEK_SET);

    /* Loop through the input file and write into output file */
    while (!feof(input) && fgets(input_line, 1024, input)) {

        char *split = strtok(input_line, ",");

        for(i = 0; i < columns; i++) {
            if(is_number(split)) {
                double temp = atof(split);
                fprintf(output, "%u", (uint32_t) fix16_from_dbl(temp));
            } else {
                fprintf(output, "%s", split);
            }
            split = strtok(0, ",");

            if(i != columns-1) {
                fprintf(output, ",");
            }
        }
    }

    fclose(input);
    fclose(output);
}
