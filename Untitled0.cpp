#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool isIdentifier(char word[]){
    int i=0;
    char ch;
    if( (word[0]>='a'&&word[0]<='z')||(word[0]>='A'&&word[0]<='Z')||(word[0]=='_')){
        while(word[i]!='\0')
        {
            ch = word[i++];
            if (!((ch>='a'&& ch<='z')||(ch>='A' && ch<='Z')||(ch>='0'&& ch<='9')||(ch=='_')))return false;

        }
    }
    else return false;
    return true;
}

int main(){
    char line[100];
    while (fgets(line, 100, stdin)) {
        int count = 0;
        char *word = strtok(line, " \n\t");
        while (word != NULL) {
            if(isIdentifier(word))count++;
            word = strtok(NULL, " \n\t");
        }
        printf("%d\n", count);
    }
    return 0;
}

