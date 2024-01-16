#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main (int argc, char** argv){

    //argv [1] = string; argv[2] is rot13.c
    int i; 
    for (i=0; i<strlen(argv[1]); i++){
        if(isalpha(argv[1][i])){
           
            if (argv[1][i] >= 97){
         
            int offset = (argv[1][i]) - 97;
            
            int new = (offset + 13)%26;
    
            printf("%c", (new + 97));
            }
            else{
        
                int offset= (argv[1][i] - 65);
                int new  = (offset + 13)%26;
                printf("%c", (new + 65));

            }
        }
        else {
            printf("%c", argv[1][i]);
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}