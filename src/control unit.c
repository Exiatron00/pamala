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

//synchroniser / clock
int main(){
    
    struct node nodeSet[12] = {node0,node1,node2,node3,node4,node5,node6,node7,node8,node9,node10,node11};
    int activeNode = 0;
start:
    for(;;activeNode++) {
    if (nodeSet[activeNode].waitState = 1 ) {
        goto start;
    } else if(activeNode = 11) {
        activeNode = 0;
    } else if(nodeSet[activeNode].pc == 11) {
        nodeSet[activeNode].pc = 0;
    } else {
        execute(nodeSet[activeNode]);
    }
}           
 