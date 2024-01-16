#include <stdio.h>
#include <stdlib.h>

typedef struct node{ 

    int data;
    struct node* left; 
    struct node* right;

} Node;

Node* createdNode(int data){ 

    Node* newNode = (Node*)malloc(sizeof(Node)); //allocate memory for a new binary tree node 
                                                 
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}

Node* Insert(Node* root, int data){
    if (root == NULL){
        //if null, create new node and return it
        printf("inserted\n");
        return createdNode(data);

    }
    else if (data == root -> data){
        //if inserted data = root's data, don't insert because it's a duplicate
        printf("not inserted\n");
        
    }
    else if (data < root -> data){
        //if inserted data < root data, insert to the left 
        root -> left = Insert(root -> left, data); 
    }

    else { // if data > root, insert to the right
        root -> right = Insert(root -> right, data);
        }

        return root;
}

void Search(Node* root, int data){

    if (root == NULL){
        printf("absent\n");
        return;
    }

    if (root -> data == data){
        printf("present\n");
    }

    else if (data < root -> data){
        // if data is less than root, search in the left
        Search(root -> left, data);
    }
    else{
        // if data is greater than root, search right
        Search(root -> right, data);
    }

}

void printTree(Node* root){ 
                            
    //check if root node is NULL
    if (root == NULL){ 
        return;
    }

    else{
        printf("("); //beginning of subtree
       
        printTree(root->left); //go through left subtree
        printf("%d", root->data); //after going through left subtree, print data in the node
        printTree(root->right); // go through right child of node, going through right subtree
       
        printf(")"); //end of the subtree
    }
}

Node* findMinimum(Node* node){
    
    //find the leftmost node
    while(node -> left != NULL){
        node = node -> left;
    }
    return node;
}

//delete a Node
Node* Delete(Node* root, int data) {
    
    if (root == NULL) {
        printf("absent\n");
        return root;
    }
    
    // if deleted data < data at root, go through left subtree
    if (data < root->data) {
        
        root->left = Delete(root->left, data);

    } else if (data > root->data) { // if deleted data > data at root, go through right tree
       
        root->right = Delete(root->right, data);

    } else { // if deleted data matches data in the root. 
        
        // root has no children
        if (root->left == NULL && root->right == NULL) {
           
            printf("deleted\n");
            free(root);
            root = NULL;

        // Root has only one child on either side
        } else if (root->left == NULL) {

            printf("deleted\n");
            // update root
            Node* temporary = root;
           // replace root with its right child 
            root = root->right;
            free(temporary);

        } else if (root->right == NULL) {

            printf("deleted\n");
            //update root
            Node* temporary = root;
            //replace root with its left child
            root = root->left;
            free(temporary);

        } else { // The root has two children
            
            //find min value node in the right subtree (smallest node that's larger than current root)
            Node* temporary = findMinimum(root->right);
            //replace root with data of the min value node
            root->data = temporary->data;
            // delete min value node from right subtree
            root->right = Delete(root->right, temporary->data);

        }
    }

    return root;
}


int main(){
    
    Node* root = NULL;
    char input;
    int data;

    while (scanf(" %c", &input) != EOF){
        //insert/delete node depending on input
        switch(input){

            //insert node
            case 'i':
            scanf("%d", &data);
            root = Insert(root, data);
            break;

            //search for a node
            case 's':
            scanf("%d", &data);
            Search(root, data);
            break;

            //print tree
            case 'p': 
            printTree(root);
            printf("\n");
            break;

            //delete node
            case 'd':
            scanf("%d", &data);
            root = Delete(root, data);
            break;

            // Error case; char input other than i,s,p,d
            default:
            break;

        }
    }

    return 0;

}