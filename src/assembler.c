#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int nth, j, x;

int Z = -1;
int Y = -1;
int X = -1;
struct node {
    int waitState;
    int acc;
    int sec;
    int pc;
    char * memPool[12][3];
}
node0, node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11;

char* savePath;
int nth, j, x;

int Z  = -1; int Y = -1; int X = -1;

char* tokenize(char * instruction) {
    struct node nodeSet[12] = {
        node0,
        node1,
        node2,
        node3,
        node4,
        node5,
        node6,
        node7,
        node8,
        node9,
        node10,
        node11
    };
    char * zDelim[60];
    char * xDelim[60];
    int a = 0, b = 0;
    zDelim[a] = strtok(instruction, "\n");
    while (zDelim[a] != NULL) {
        if (strcmp(zDelim[a], "@") == 0) {
            Z++;
            Y = -1;
        } else {
            Y++;
            X = -1;
            xDelim[b] = strtok(zDelim[a], " ");
            while (xDelim[b] != NULL) {
                if (X == 3) {
                    X = -1;
                } else {
                    X++;
                    return xDelim[b];
                    xDelim[b] = strtok(NULL, " ");

                }
            }
        }
        zDelim[++a] = strtok(NULL, "\n");
    }
}

void clean(char * stream, int lineCount) {
    for (nth = 0; stream[nth] == ' ' || stream[nth] == '\t'; nth++);
    for (j = 0; stream[nth]; nth++) {
        stream[j++] = stream[nth];
    }
    stream[j] = '\0';
    for (nth = 0; stream[nth] != '\0'; nth++) {
        if (stream[nth] != ' ' && stream[nth] != '\t')
            j = nth;
    }
    stream[j + 1] = '\0';
    char * instruction[lineCount];
    instruction[x] = stream;

    tokenize(instruction[x]);
    x++;

}

int fetch() {

    int lineCount;
    FILE * saveFile = fopen(savePath, "r");
    if (saveFile == NULL) {
        perror("Savefile missing!"); //sdl needs to handle this.
        return 1;
    }
    char lineBuffer[128];
    while (fgets(lineBuffer, sizeof(lineBuffer), saveFile) != NULL) {
        lineCount++;
        clean(lineBuffer, lineCount);
    }
}

int main() {
    fetch();
}  