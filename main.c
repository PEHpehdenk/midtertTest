#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS_COUNT 20

void command_list() {
    printf("sort\nreverse\nsplit\njoin");
}

void sort_lines(char list[][BUFSIZ], int n) {
    char swap[BUFSIZ];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(list[j], list[j + 1]) > 0) {
                strcpy(swap, list[j]);
                strcpy(list[j], list[j + 1]);
                strcpy(list[j + 1], swap);
            }
        }
    }
}

void reverse_lines(char list[][BUFSIZ], int n) {
    char swap[BUFSIZ];
    for (int i = 0; i < n / 2; i++) {
        strcpy(swap, list[i]);
        strcpy(list[i], list[n - i - 1]);
        strcpy(list[n - i - 1], swap);
    }
}

void sort_f(char sort_type[BUFSIZ], char inputFile[BUFSIZ], char outputFile[BUFSIZ]) {
    FILE *inputFileSort, *outputFileSort;
    char input[BUFSIZ];
    inputFileSort = fopen(inputFile, "r");
    outputFileSort = fopen(outputFile, "w");

    if (inputFileSort == NULL || outputFileSort == NULL) {
        fprintf(outputFileSort, "%s", "sort\nreverse\nsplit\njoin");
        return;
    }

    if (strcmp(sort_type, "words") == 0) {
        char word_to_sort[BUFSIZ];
        while (fgets(input, sizeof(input), inputFileSort) != NULL) {
            for (int i = 0; i < strlen(input); i++) {
                if (input[i] != ' ') {
                    strncat(word_to_sort, &input[i], 1);
                    continue;
                }
                for (int j = 0; j < strlen(word_to_sort); j++) {
                    for (int j2 = 0; j2 < strlen(word_to_sort) - 1; j2++) {
                        if (word_to_sort[j2 + 1] < word_to_sort[j2]) {
                            char swap = word_to_sort[j2];
                            word_to_sort[j2] = word_to_sort[j2 + 1];
                            word_to_sort[j2 + 1] = swap;
                        }
                    }
                }
                fprintf(outputFileSort, "%s ", word_to_sort);
                memset(word_to_sort, 0, BUFSIZ);
            }
        }
        if (strlen(word_to_sort) > 0) {
            for (int j = 0; j < strlen(word_to_sort); j++) {
                for (int j2 = 0; j2 < strlen(word_to_sort) - 1; j2++) {
                    if (word_to_sort[j2 + 1] < word_to_sort[j2]) {
                        char swap = word_to_sort[j2];
                        word_to_sort[j2] = word_to_sort[j2 + 1];
                        word_to_sort[j2 + 1] = swap;
                    }
                }
            }
            fprintf(outputFileSort, "%s", word_to_sort);
        }
        return;
    }
    if (strcmp(sort_type, "lines") == 0) {
        char words[MAX_WORDS_COUNT][BUFSIZ];
        int words_count = 0;
        while (fscanf(inputFileSort, "%s", words[words_count]) == 1) {
            words_count++;
        }
        sort_lines(words, words_count);
        for (int i = 0; i < words_count; i++) {
            fprintf(outputFileSort, "%s ", words[i]);
        }
        return;
    }
    fprintf(outputFileSort, "%s", "sort\nreverse\nsplit\njoin");
}

void reverse_f(char reverse_type[BUFSIZ], char inputFile[BUFSIZ], char outputFile[BUFSIZ]) {
    FILE *inputFileReverse, *outputFileReverse;
    char input[BUFSIZ];
    inputFileReverse = fopen(inputFile, "r");
    outputFileReverse = fopen(outputFile, "w");

    if (inputFileReverse == NULL || outputFileReverse == NULL) {
        fprintf(outputFileReverse, "%s", "sort\nreverse\nsplit\njoin");
        return;
    }

    if (strcmp(reverse_type, "words") == 0) {
        char word_to_reverse[BUFSIZ];
        while (fgets(input, sizeof(input), inputFileReverse) != NULL) {
            for (int i = 0; i < strlen(input); i++) {
                if (input[i] != ' ') {
                    strncat(word_to_reverse, &input[i], 1);
                    continue;
                }
                for (int j = 0; j < strlen(word_to_reverse) / 2; j++) {
                    char swap = word_to_reverse[j];
                    word_to_reverse[j] = word_to_reverse[strlen(word_to_reverse) - j - 1];
                    word_to_reverse[strlen(word_to_reverse) - j - 1] = swap;
                }
                fprintf(outputFileReverse, "%s ", word_to_reverse);
                memset(word_to_reverse, 0, BUFSIZ);
            }
        }
        if (strlen(word_to_reverse) > 0) {
            for (int j = 0; j < strlen(word_to_reverse) / 2; j++) {
                char swap = word_to_reverse[j];
                word_to_reverse[j] = word_to_reverse[strlen(word_to_reverse) - j - 1];
                word_to_reverse[strlen(word_to_reverse) - j - 1] = swap;
            }
            fprintf(outputFileReverse, "%s", word_to_reverse);
        }
        return;
    }
    if (strcmp(reverse_type, "lines") == 0) {
        char words[MAX_WORDS_COUNT][BUFSIZ];
        int words_count = 0;
        while (fscanf(inputFileReverse, "%s", words[words_count]) == 1) {
            words_count++;
        }
        reverse_lines(words, words_count);
        for (int i = 0; i < words_count; i++) {
            fprintf(outputFileReverse, "%s ", words[i]);
        }
        return;
    }
    fprintf(outputFileReverse, "%s", "sort\nreverse\nsplit\njoin");
}

void split_f(char inputFile[BUFSIZ], char outputFile[BUFSIZ]) {
    FILE *inputFileSplit, *outputFileSplit;
    inputFileSplit = fopen(inputFile, "r");
    outputFileSplit = fopen(outputFile, "w");
    char words[MAX_WORDS_COUNT][BUFSIZ];
    char wordToAdd[BUFSIZ];
    int words_count = 0;
    while (fscanf(inputFileSplit, "%s", words[words_count]) == 1) {
        words_count++;
    }
    for (int i = 0; i < words_count; i++) {
        char wordToSplit[BUFSIZ];
        strcpy(wordToSplit, words[i]);
        for (int j = 0; j < strlen(wordToSplit); j++) {
            if (wordToSplit[j] != ' ') {
                strncat(wordToAdd, &wordToSplit[j], 1);
                continue;
            }
            fprintf(outputFileSplit, "%s\n", wordToAdd);
            memset(wordToAdd, 0, BUFSIZ);
        }
        if (strlen(wordToAdd) > 0) {
            fprintf(outputFileSplit, "%s\n", wordToAdd);
            memset(wordToAdd, 0, BUFSIZ);
        }
    }
}

void join_f(char inputFile[BUFSIZ], char outputFile[BUFSIZ]) {
    FILE *inputFileJoin, *outputFileJoin;
    inputFileJoin = fopen(inputFile, "r");
    outputFileJoin = fopen(outputFile, "w");
    char words[MAX_WORDS_COUNT][BUFSIZ];
    int words_count = 0;
    while (fscanf(inputFileJoin, "%s", words[words_count]) == 1) {
        words_count++;
    }
    for (int i = 0; i < words_count; i++) {
        fprintf(outputFileJoin, "%s ", words[i]);
    }
}


int main(int arg, char *argv[]) {
    if (arg <= 1) {
        command_list();
    }
    else {
        char type_of_task[BUFSIZ];
        strcpy(type_of_task, argv[1]);
        if (strcmp(type_of_task, "sort") == 0) {
            char type_of_sort[BUFSIZ];
            strcpy(type_of_sort, argv[2]);
            sort_f(type_of_sort, argv[3], argv[4]);
        } else if (strcmp(type_of_task, "reverse") == 0) {
            char type_of_reverse[BUFSIZ];
            strcpy(type_of_reverse, argv[2]);
            reverse_f(type_of_reverse, argv[3], argv[4]);
        } else if (strcmp(type_of_task, "split") == 0) {
            split_f(argv[2], argv[3]);
        } else if (strcmp(type_of_task, "join") == 0) {
            join_f(argv[2], argv[3]);
        }
    }
    return 0;
}
