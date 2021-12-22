#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("wrong number of program arguments");
        return 0;
    }
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        printf("incorrect path to the input file");
        return 0;
    }
    FILE* output = fopen(argv[2], "w");
    if (!output) {
        printf("incorrect path to the output file");
        fclose(input);
        return 0;
    }
    int* alphabet = calloc(26, sizeof(int));
    char letter = ' ';
    while (fscanf(input, "%c", &letter) != EOF) {
        if (letter >= 'a' && letter <= 'z')
            alphabet[letter - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (alphabet[i])
            fprintf(output, "%c: %d\n", 'a' + i, alphabet[i]);
    }
    fclose(input);
    fclose(output);
    free(alphabet);
    return 0;
}
