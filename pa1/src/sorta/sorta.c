#include<stdio.h>
#include<string.h>


int main (int argc, char** argv){
    int i, j;
    char *temp; 
    
    for (i = 1; i<argc;i++){ 
       
        for (j=i+1; j<argc; j++){ 
           
            if (strcmp(argv[i], argv[j]) > 0){ 
                
                temp = argv[i]; 
                argv[i]=argv[j]; 
                argv[j] = temp; 
    
            }
        }
    }

    for (i=1; i<argc; i++){
        printf("%s\n", argv[i]);

    }

}
