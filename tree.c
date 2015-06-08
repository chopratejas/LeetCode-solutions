#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <stdbool.h>

typedef struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


void printTree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("Elem: %d\n", root->val);
    printTree(root->right);
}

TreeNode *createNode(int val)
{
    TreeNode *node = calloc(1, sizeof(TreeNode));
    assert(node != NULL);
    node->val = val;
    return node;
}

void destroyNode(TreeNode *node)
{
    assert(node != NULL);
    free(node);
}

TreeNode *insertNode(TreeNode *root, TreeNode *node)
{
    if (root == NULL) {
        root = node;
        return root;
    }
    if (node->val <= root->val) {
        root->left = insertNode(root->left, node);
    } else {
        root->right = insertNode(root->right, node);
    }
    return root;
}

TreeNode *createTree(int arr[], int numElems)
{
    TreeNode *root = NULL;
    TreeNode *curr = NULL;
    assert(arr != NULL);
    for (int i = 0; i < numElems; i++) {
        curr = createNode(arr[i]);
        root = insertNode(root, curr);
    }
    return root;
}

void destroyTree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    destroyNode(root);
}

int main()
{
    int arr[] = {20, 5, 3, 7, 2};
    TreeNode *root = createTree(arr, 5);
    printTree(root);
    destroyTree(root);
    return 0;
}
