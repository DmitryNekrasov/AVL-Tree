#include <malloc.h>
#include <stdio.h>

struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};

int max(int a, int b) {
    return a > b ? a : b;
}

struct Node* makeNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->height = 1;
    node->left = node->right = NULL;
}

int height(struct Node* node) {
    return node ? node->height : 0;
}

int balanceFactor(struct Node* node) {
    return height(node->right) - height(node->left);
}

void fixHeight(struct Node* node) {
    int h1 = height(node->left);
    int h2 = height(node->right);
    node->height = max(h1, h2) + 1;
}

struct Node* rotateRight(struct Node* p) {
    struct Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

struct Node* rotateLeft(struct Node* q) {
    struct Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

struct Node* balance(struct Node* p) {
    fixHeight(p);
    if (balanceFactor(p) == 2) {
        if (balanceFactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (balanceFactor(p) == -2) {
        if (balanceFactor(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

struct Node* insert(struct Node* root, int key) {
    if (!root) {
        return makeNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return balance(root);
}

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    return 0;
}
