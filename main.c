#include <malloc.h>
#include <stdio.h>

struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};

struct Node* makeNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->height = 1;
    node->left = node->right = NULL;
}

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    return 0;
}
