#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

int* twoSum(int* nums, int numsSize, int target)
{
    int *index = NULL;
    int curr_target = target;
    int index1 = -1, index2 = -1;
    assert(nums != NULL);
    index = calloc(2, sizeof(int));
   
    for (int i = 0; i < numsSize; i++) {
        curr_target = target - nums[i];
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] == curr_target) {
                index1 = i + 1;
                index2 = j + 1;
                break;
            }
        }
    }
    printf("Index: %d, %d\n", index1, index2);
    index[0] = index1;
    index[1] = index2;
    return index;
}

int *createArray(int num)
{
    return NULL;
}

int main()
{
    int arr[] = {1, 2, 3};
    int target = 1;
    int *index = twoSum(arr, 3, target);
    free(index);
    return 0;
}
