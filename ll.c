#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAX_LISTS       200
#define MAX_ELEMENTS    200

/* Per node structure. */
typedef struct ListNode {
    int val;                // Value carried by the node.
    struct ListNode *next;  // Pointer to the next node.
} ListNode;

/*
 * Utility to print the list given the head.
 */
void printList(ListNode *head)
{
    ListNode *curr = head;
    printf("Printing list: ");
    while (curr != NULL) {
        printf("%d->", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

/*
 * Create a node and initialize it with a val.
 */
ListNode *createNode(int val)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    node->val = val;
    return node;
}

/*
 * Delete a given node.
 */
void deleteNode(ListNode *node)
{
    free(node);
}

/*
 * Merge two linked lists.
 */
ListNode *mergeLists(ListNode *head1, ListNode *head2)
{
    ListNode *result;
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }
    if (head1->val <= head2->val) {
        result = head1;
        result->next = mergeLists(head1->next, head2);
    } else {
        result = head2;
        result->next = mergeLists(head1, head2->next);
    }
    return result;
}

/*
 * Given a linked list, split it into two parts.
 * The front points to the start of the first part,
 * the back points to the start of the last part.
 */
void frontBackSplit(ListNode *head, ListNode **front, ListNode **back)
{
    ListNode *fast;
    ListNode *slow;
    if ((head == NULL) || (head->next == NULL)) {
        *front = head;
        *back = NULL;
    } else {
        slow = head;
        fast = head->next;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        *front = head;
        *back = slow->next;
        slow->next = NULL;
    }
}

/*
 * Given a list head, sort the elements of the linked list
 * by value.
 */
ListNode *sortList(ListNode *head)
{
    ListNode *a, *b;
    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }
    frontBackSplit(head, &a, &b);
    a = sortList(a);
    b = sortList(b);
    head = mergeLists(a, b);
    return head;
}

/*
 * Code to merge numLists linked lists.
 */
ListNode *mergeManyLists(ListNode **lists, int numLists)
{
    ListNode *result = NULL;
    int minValue = INT_MAX;
    int targetList = 0;
    int i = 0;
    for (i = 0; i < numLists; i++) {
        if (lists[i] != NULL) {
            if (lists[i]->val <= minValue) {
                minValue = lists[i]->val;
                result = lists[i];
                targetList = i;
            }
        }
    }
    if (result != NULL) {
        lists[targetList] = lists[targetList]->next;
        result->next = mergeManyLists(lists, numLists);
    }
    return result;
}

/*
 * Code to create a list.
 */
ListNode *createList(int arr[], int numElems)
{
    ListNode *head = NULL;
    ListNode *curr = NULL;
    ListNode *prev = NULL;
    for (int i = 0; i < numElems; i++) {
        curr = createNode(arr[i]);
        if (i == 0) {
            head = curr;
        } else {
            prev->next = curr;
        }
        prev = curr;
    }
    return head;
}

/*
 * Given a head, deleting an entire list.
 */
void deleteList(ListNode *head)
{
    ListNode *curr = head;
    ListNode *next = curr->next;
    while (curr != NULL) {
        //printf("Deleting: %d\n", curr->val);
        next = curr->next;
        deleteNode(curr);
        curr = next;
    }
}

/*
 * Code to create an array of random numbers
 * of which the linked list is created.
 */
int *createArray(int *numElems)
{
    int *arr;
    int num = rand() % MAX_ELEMENTS + 1;
    arr = calloc(num, sizeof(int));
    assert(arr != NULL);
    for (int i = 0; i < num; i++) {
        arr[i] = rand() % INT_MAX;
    }
    *numElems = num;
    return arr;
}

/*
 * Code to destroy an array.
 */
void destroyArray(int *arr)
{
    assert(arr != NULL);
    free(arr);
}

void destroyListArray(ListNode **arr, int numLists)
{
    assert(arr != NULL);
    for (int i = 0; i < numLists; i++) {
        deleteList(arr[i]);
    }
}


ListNode **createListArray(int *numLists)
{
    ListNode **arr;
    int listSize = 0;
    int *listArray;
    int num = rand() % MAX_LISTS + 1;
    arr = calloc(num, sizeof(ListNode *));
    assert(arr != NULL);
    for (int i = 0; i < num; i++) {
        listArray = createArray(&listSize);
        assert(listArray != NULL);
        arr[i] = createList(listArray, listSize);
        arr[i] = sortList(arr[i]);
        //printList(arr[i]);
        destroyArray(listArray);
    }
    *numLists = num;
    return arr;
}

int main()
{
    ListNode *result = NULL;
    int numLists;
    ListNode **lists = createListArray(&numLists); 
    result = mergeManyLists(lists, numLists);
    //printList(result);
    deleteList(result);
    assert(lists != NULL);
    free(lists);
    return 0;
}
