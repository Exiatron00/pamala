#include <stdio.h>

#include <stdlib.h>

#include <string.h>


struct node {
    int waitState; 
    int acc;
    int sec;
    int pc;
    char* memPool [12][3];
} node0,node1,node2,node3,node4,node5,node6,node7,node8,node9,node10,node11;
struct node nodeSet[12];
int nth, j,x; 

int activeNode = 0;

void decode(){

}
int assemble(char* token) {
    
    int d = 0; int e = 0; int f=0;
    for(; d<=  11; d++){
        for(; e <= 9; e++) {
            for(; f<= 2; f++){
                nodeSet[d].memPool[e][f] = token;
            }
        }
    }
}

void tokenize(char * instruction) {


    int z = 0; int tokenCount = 0; 
    char * tokenArray[60];
    tokenArray[z] = strtok(instruction, " \n");
    while (tokenArray[z] != NULL) {

        assemble(tokenArray[z]);
        tokenArray[++z] = strtok(NULL, " \n");
        tokenCount ++;
        if(tokenCount > 3) {
            perror("Illegal token count!");
        }
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
    int lineCount; int currentSave;
    for (currentSave = 0; currentSave <= 11; currentSave++) {
       char* fileList[12] = {"save/1.txt","save/2.txt","save/3.txt","save/4.txt","save/5.txt","save/6.txt","save/7.txt","save/8.txt","save/9.txt","save/10.txt","save/11.txt","save/12.txt"};
        FILE * saveFile = fopen(fileList[currentSave], "r");
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
}


//synchroniser / clock
int main(){
    
    struct node nodeSet[12] = {node0,node1,node2,node3,node4,node5,node6,node7,node8,node9,node10,node11};
    
start:
    for(;;activeNode++) {
    if (nodeSet[activeNode].waitState = 1 ) {
            goto start;
        } else if(activeNode = 11) {
            activeNode = 0;
        } else if(nodeSet[activeNode].pc = 11) {
            nodeSet[activeNode].pc = 0;
        } else {
            decode(nodeSet[activeNode]);
        }
    }
}

