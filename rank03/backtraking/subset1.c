#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int** subset(int* nums, int numSize, int* returnSize, int** returnColumnSizes)
{
	returnSize = pow(2, numSize);

	int** result = (int**)malloc(*returnSize * sizeof(int));
	*returnColumnSize = (int*)malloc(*returnSize * sizeof(int));

	for (int i = 0; i < *returnSize; i++){
		
		int count = 0;
		for(int j = 0; j < numSizes; j++){
			if(i & (1 << j)){
				count++;
			}
		}

		result[i] = (int*)malloc(count * sizeof(int));
		(*returnColumnSizes)[i] = count;

		int index = 0;
		for (int j = 0; j < numSize; j ++){
			if (i & ( 1 << j)){
				result[i][index++] = nums[j];
			}
		}
	}
	return result;
}

