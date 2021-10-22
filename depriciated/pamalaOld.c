#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
  char* recv;
  char* send; 
};

struct core  {
    int coreNo;
    int accValue;
    int secValue;
    int pcValue;
} core0, core1, core2, core3,core4,core5,activeCore ;

int info(int selected){
    if (selected == core0.coreNo) {
        printf("core0's accumulator value is currently: %u\n", core0.accValue);
        printf("core0's secondary value is currently: %u\n\n", core0.secValue);
    } 
    if (selected == core1.coreNo) {
        printf("core1's accumulator value is currently: %u\n", core1.accValue);
        printf("core1's secondary value is currently: %u\n\n", core1.secValue);
    }
}

int ACouple(char* operator, char* aCouple[]){
    int i;
    int check;
    for(i =0; i<=2; i++){
        int check = strcmp(operator,aCouple[i]);
        if(check == 0 && i == 0) {
            activeCore.accValue = 0;
        }
        if(check == 0 && i == 1) {
            int temp = activeCore.accValue; 
            activeCore.accValue = activeCore.secValue;
            activeCore.secValue = temp;
        }
        if(check == 0 && i == 2) {
            activeCore.secValue = activeCore.accValue;

        } 
    }
}

int HCouple(char* operator,char* operand, char* hCouple[]){
    long reOperand;
    char* ptr;
    int i;
    reOperand = strtol(operand, &ptr, 10);
    reOperand = (int)reOperand;
    for(i = 0; i<=1; i++){
        int check = strcmp(operator,hCouple[i]);
        if(check == 0 && i>0 && activeCore.accValue > reOperand) {
            printf("%u\n", check);
            activeCore.accValue -= reOperand;
        } 
        if(check == 0 && i<1) {
            printf("%u\n", check);
            activeCore.accValue += reOperand;         
        }
    }
}

int PCouple(char* array0, char* array1, char* array2, int activeCorecoreNo) {
/*    //get activecoreno to establish what transfers are possible
    char* addpCouple[4]= {"up","down","left","right"};
    //handle all cases as a one directional ransfer - if the array0 is valid 
    // entertain the rest , if not - kill.
    switch (activeCorecoreNo) {
        case 0:
            if(array0 = addpCouple[2]) {
                
            }
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
    }*/
}
    int parser(char* stream) {
    char* aCouple[3] = {"clr","swp","sav","neg"} ;
    char* hCouple[2] = {"add","sub","jmp","jgz","jlz","jez","jro","jnz"} ;
    char* pCouple[1]= {"mov"};
    int i;
    char* p = strtok (stream, " \n");
    char* array[3];
    while (p != NULL) {
        array[i++] = p;
        p = strtok (NULL, " \n");
    }
    for(i =0; i <=2; i++) {
       printf("comparing with index value %u i.e the element called %s \n", i, aCouple[i]);
        if (strcmp(array[0],aCouple[i]) == 0) {
            printf("aCouple detected\n");
            ACouple(array[0],aCouple);
            return 0;
        }
    }
    for (i =0; i <=1; i++) {
        printf("comparing with index value %u i.e the element called %s \n", i, hCouple[i]);
        if (strcmp(array[0],hCouple[i]) == 0) {
            printf("hCouple detected\n");
            HCouple(array[0], array[1],hCouple);
            return 0;         
        }
    }
    for (i =0; i<= 0; i++) {
        printf("comparing with index value %u i.e the element called %s \n", i, pCouple[i]);
        if (strcmp(array[0],pCouple[i]) == 0) {
            printf("pCouple detected\n");
            PCouple(array[0],array[1],array[2], 3);
        } else {
            printf("failed to find a single match\n");
        }
    }
}
 int main() {
     /* open up text files for all cores
     activate a listening connection for all cores*/
    int num;
    FILE *fptr;
    
    if ((fptr = fopen("assembly.txt","r")) == NULL){
        printf("Error! opening file\n");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   fscanf(fptr,"%d", &num);

   printf("Value of n=%d", num);
   fclose(fptr); 

 }

 /*
 //REQUIRMENTS

//CLOCK
/SYNCRONISE CPU OPERATIONS AND CHECKING OF CODE

//NODES , WITH INTERNAL REGISTERS AND PORTS, TO ALLOW FOR COMMUNICATION

MAR, MDR , PC

ADD
SUB
SWP
SAV
MOV 
NEG
JMP
JEZ
JNZ
JGZ
JLZ
JRO
*/
int  i,j;
int x = 0;

void assemble() {


}

void tokenize(char* instruction) {
  
    int parity = strcmp(instruction, "");
    printf("%u\n", parity);
    printf("TOKENIZER RECEIVED: %s", instruction);
    int z=0;
    char* tokenArray[60];
    tokenArray[z] = strtok(instruction," \n");
    while(tokenArray[z]!=NULL) {
        printf("TOKEN: %s\n", tokenArray[z]);
        tokenArray[++z] = strtok(NULL," \n");
    }
}
void clean(char* stream, int lineCount) {
    for(i=0;stream[i]==' '||stream[i]=='\t';i++);
    for(j=0;stream[i];i++) {
        stream[j++]=stream[i];
    }
    stream[j] = '\0';
	for(i=0;stream[i]!='\0';i++) {
        if(stream[i]!=' '&& stream[i]!='\t')
            j=i;
    } 
    stream[j+1]='\0';
    char* instruction[lineCount];
    instruction[x] = stream;
    printf("\nCLEANER RECEIVED: %s", instruction[x]);
    tokenize(instruction[x]);
    x++;
    

}
void fetch() {
    int lineCount;
    FILE *saveFile = fopen("savefile.txt","r");
    if (saveFile == NULL ) {
        perror("Savefile missing!");
        exit(1);
    }
    char lineBuffer[128];
    while(fgets(lineBuffer,sizeof(lineBuffer),saveFile)!= NULL) {
        lineCount++;
        clean(lineBuffer, lineCount);
    }
}


int main() {
    fetch();
}