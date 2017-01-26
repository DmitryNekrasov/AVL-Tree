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

void rootLeftRight(struct Node* root, int depth) {
    if (root) {
        for (int i = 0; i < depth; i++) {
            printf(" ");
        }
        printf("%d (", root->key);
        if (root->left) {
            printf("%d, ", root->left->key);
        } else {
            printf("_, ");
        }
        if (root->right) {
            printf("%d)\n", root->right->key);
        } else {
            printf("_)\n");
        }

        rootLeftRight(root->left, depth + 1);
        rootLeftRight(root->right, depth + 1);
    }
}

void printTree(struct Node* root) {
    printf("\n");
    rootLeftRight(root, 0);
    printf("\n");
}

int main(int argc, char *argv[])
{
    struct Node* root = NULL;
    int key;
    while (1) {
        printf("---> ");
        scanf("%d", &key);
        if (key == 0) {
            break;
        }
        root = insert(root, key);
        printTree(root);
    }

    return 0;
}
