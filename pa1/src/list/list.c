#include<stdio.h>
#include<stdlib.h>


//create Node struct
struct Node{ 

    int data; 
    struct Node* next; 

};

// Function to create a new Node
struct Node* CreateNode(int value){ 

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
    
    newNode -> data = value; 
    newNode -> next = NULL; 
    return newNode; 
}

//function to insert into linked list 
void insertInto (struct Node** head, int value){ 

    // prevent duplicates
    struct Node* current = *head;
    while (current != NULL){
        if (current -> data == value){
            return;
        }
        current = current -> next;
    }
    struct Node* newNode = CreateNode(value);
    if (*head == NULL || value < ((*head) -> data)){ 
        newNode -> next = *head; 
        *head = newNode; 
    }
    else { //if value to be inserted is greater than or equal to the current head's value
        struct Node* current = *head;
        while (current -> next != NULL && current -> next -> data < value){ 

            current = current -> next; 

        }
       
        newNode -> next = current -> next; 
        current -> next = newNode; 
    
    }

}

//delete function
void deleteFrom (struct Node** head, int value){
    struct Node* current = *head;
    struct Node* old = NULL;

    while (current != NULL && current -> data != value){ 

        old = current; 
        current = current -> next; 
    }

    if (current != NULL){ 
        if (old == NULL){ 
            *head = current -> next; 
        }else{ 

            old -> next = current -> next; 
        }
        free(current); 
    }

}

// freeMem = frees mem allocated for each node of list, one at a time
void freeMem(struct Node* head){
    struct Node* current = head; 

    while (current != NULL){
        struct Node* placeholder = current;
        current = current -> next;
        free(placeholder); 
    }

}

void Print(struct Node* head) {
    struct Node* current = head;
    static int listNumber = 0; 
    static int prevNodeCount = 0; // In case node is added to the front of list

    // Count the number of nodes in the list before printing
    int nodeCount = 0;

    while (current != NULL) {
        nodeCount++;
        current = current->next;
    }

    if (nodeCount > prevNodeCount) {
        listNumber++;
    }

    else if (nodeCount < prevNodeCount) {
        listNumber--;
    }

    prevNodeCount = nodeCount; 

    int currentListNumber = listNumber; 
    

    printf("%d :", currentListNumber);

    current = head; 

    while (current != NULL) {
        printf(" %d", current->data);
        current = current->next;
    }

    printf("\n");
}





int main (){
    struct Node* head = NULL;
    char input;
    int value;


    while (scanf(" %c %d", &input, &value) != EOF){

        if (input == 'i' ){
            
            insertInto(&head, value);
    
        }
        else if(input =='d'){
            
            deleteFrom(&head, value);

        }

        Print(head);
    }
    

    freeMem(head);
    
   return EXIT_SUCCESS;
}
