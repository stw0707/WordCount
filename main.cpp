#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

// 统计文件中的字符数
int count_characters(FILE *file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    rewind(file); // 重置文件指针，以便重新使用
    return count;
}

// 统计文件中的单词数
int count_words(FILE *file) {
    int count = 0;
    char buffer[MAX_BUFFER_SIZE];
    char *word;
    
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        word = strtok(buffer, " ,\t\n");
        while (word != NULL) {
            count++;
            word = strtok(NULL, " ,\t\n");
        }
    }
    rewind(file); // 重置文件指针，以便重新使用
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c or -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *option = argv[1];
    char *filename = argv[2];
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 1;
    }

    if (strcmp(option, "-c") == 0) {
        printf("字符数：%d\n", count_characters(file));
    } else if (strcmp(option, "-w") == 0) {
        printf("单词数：%d\n", count_words(file));
    } else {
        fprintf(stderr, "Error: Invalid option %s. Please use -c or -w\n", option);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

