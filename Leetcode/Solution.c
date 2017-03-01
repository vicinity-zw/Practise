#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int comp(const void *p1, const void *p2)
{
	return (*(int *)p1 - *(int *)p2);
}

void showInfo(int *nums, int numsSize)
{
	int i = 0;
	for (i = 0; i < numsSize; i++)
	{
		printf("%d  ", nums[i]);
	}
	printf("\n");
}

int** permutenorecursive(int* nums, int numsSize, int* returnSize) 
{
	int i = 0;
	int j = 0;
	int iTmp = 0;
	int iLeft = 0;
	int iRight = 0;
	
	qsort(nums, numsSize, sizeof(int), comp);
	
	while(1)
	{
		showInfo(nums, numsSize);
		for (i = numsSize - 2; i >= 0; i--)
		{
			if (nums[i] < nums[i + 1])
				break;
		}
		
		if (i < 0)
		{
			return NULL;
		}

		for (j = numsSize - 1; j > i; j--)
		{
			if (nums[j] > nums[i])
				break;	
		}

		
		iTmp = nums[j];
		nums[j] = nums[i];
		nums[i] = iTmp;

		iLeft = i + 1;
		iRight = numsSize - 1;
		while(iLeft < iRight)
		{
			iTmp = nums[iLeft];
			nums[iLeft] = nums[iRight];
			nums[iRight] = iTmp;
			iLeft++;
			iRight--;
		}
	}
		
}

int Volume(int *height, int iStart, int iEnd)
{
	int i = 0;
	int iMin = 0;
	int iVol = 0;

	iMin = (height[iStart] < height[iEnd]) ? (height[iStart]) : (height[iEnd]);
	
	for (i = iStart + 1; i < iEnd; i++)
	{
		iVol += (iMin - height[i]);
	}

	return iVol;
}

void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) 
{
	int i = 0;
	int j = 0;
	int row_has_zero = 0;  
	int line_has_zero = 0;
	for (i = 0; i < matrixRowSize; i++)
	{
		if (matrix[i][0] == 0)
			line_has_zero = 1;
	}

	for (i = 0; i < matrixColSize; i++)
	{
		if (matrix[0][i] == 0)
			row_has_zero = 1;
	}

	for (i = 1; i < matrixRowSize; i++)
	{
		for (j = 1; j < matrixColSize; j++)
		{
			if (matrix[i][j] == 0)
			{
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}

	for (i = 1; i < matrixRowSize; i++)
	{
		for (j = 1; j < matrixColSize; j++)
		{
			 if (matrix[i][0] == 0 || matrix[0][j] == 0)
			{
				matrix[i][j] = 0;
			}
		}
	}

	if (row_has_zero == 1)
	{
		for (j = 0; j < matrixColSize; j++)
		{
			matrix[0][j] = 0;
		}
	}

	if (line_has_zero == 1)
	{
		for (i = 0; i < matrixRowSize; i++)
		{
			matrix[i][0] = 0;
		}
	}

}

int climbStairs(int n) 
{
	int iPrev = 0;
	int iCur = 1;
	int iTmp = 0;
	int i = 0;
	for (i = 1; i <= n; i++)
	{
		iTmp = iCur;
		iCur += iPrev;
		iPrev = iTmp;
	}
	return iCur;
}

int singleNumber(int* nums, int numsSize) 
{
	int iBit = 0;
	int i = 0;
	int iCnt[32] = {0};
	int iRes = 0;

	for (iBit = 0; iBit < 32; iBit++)
	{
		for (i = 0; i < numsSize; i++)
		{
			iCnt[iBit] += (nums[i]>>iBit) & 1; 
		}

		iRes |= (iCnt[iBit]%3)<<iBit;
	}
	return iRes;
}

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) 
{
	int iTotal = 0;
	int iSum = 0;
	int iIndex = 0;
	int iStart = 0;
	if (NULL == gas || 0 == gasSize)
	{
		return -1;
	}
	if (gasSize <= 0||costSize <= 0 ||gasSize != costSize)
	{
		return -1;
	}

	for (iIndex = 0; iIndex < costSize; iIndex++)
	{
		iTotal += gas[iIndex] - cost[iIndex];
		if (iSum < 0)
		{
			iSum = gas[iIndex] - cost[iIndex];
			iStart = iIndex;
		}
		else 
		{
			iSum += gas[iIndex] - cost[iIndex];
		}
	}

	if (iTotal < 0)
		return -1;
	else
		return iStart;
}

/*
1 2 3 4 :  10
1 4 2 3 :   1 + 2 + 1 + 2 = 6
2 1 4 3 :   2 + 1 + 2 + 1 = 6
4 3 2 1:    4 + 3 + 2 + 1 = 10
*/

int candy(int* ratings, int ratingsSize)
{
	int *pNum = NULL;
	int i = 0;

	if (ratings == NULL || ratingsSize < 0)
		return 0;
	pNum = (int *)malloc(sizeof(int)*ratingsSize);
	if (NULL == pNum)
		return 0;
	
	memset(pNum, 0, sizeof(int)*ratingsSize);
	for (i = 0; i < ratingsSize; i++)
	{
		if (i == 0)
		{
			if (ratings[i] < ratings[i + 1])
				pNum[i] = 1;
		}
		else if (ratingsSize - 1 == i)
		{
			if (ratings[i] < ratings[i -1])
				pNum[i] = 1;
		}
	}

	for (i = 1; i < ratingsSize - 1; i++)
	{
		if (i == 0)
		{
			if (ratings[i] > ratings[i + 1])
				pNum[i] = 1;
		}
		else if (ratingsSize - 1 == i)
		{
			if (ratings[i] < ratings[i -1])
				pNum[i] = 1;
		}
	}
  
}

int findKthNum(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    int pa = 0;
    int pb = 0;
    if (nums1Size > nums2Size)
        return findKthNum(nums2, nums2Size, nums1, nums1Size, k);
    if (0 == nums1Size)
        return nums2[k - 1];
    if (1 == k)
        return (nums1[0] < nums2[0]) ? nums1[0] : nums2[0];

    pa = ((k/2) < nums1Size) ? (k/2) : nums1Size;
    pb = k - pa;
    if (nums1[pa - 1] > nums2[pb - 1])
        return  findKthNum(nums1, nums1Size, nums2 + pb, nums2Size - pb, k - pb);
    else if (nums1[pa - 1] < nums2[pb - 1])
        return  findKthNum(nums1 + pa, nums1Size - pa, nums2, nums2Size, k - pa);
    else
        return nums1[pa - 1];
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total = 0;
    int first = 0;
    int second = 0;
    double res = 0;
    total = nums1Size + nums2Size;
    if (total & 1)
    {
        return findKthNum(nums1, nums1Size, nums2, nums2Size, total/2 + 1);
    }
    else
    {
        first = findKthNum(nums1, nums1Size, nums2, nums2Size, total/2);
        second = findKthNum(nums1, nums1Size, nums2, nums2Size, total/2 + 1);
        res = ((double)first + (double)second)/2;
        return res;
    }
}


void rotate(int** matrix, int matrixRowSize, int matrixColSize) {
    int i = 0;
    int j = 0;
    int tmp = 0;
    for (i = 0; i < matrixRowSize/2; i++)
    {
        for (j = i; j < matrixColSize - 1 - i; j++)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[matrixColSize - 1 - j][i];
            matrix[matrixColSize - 1 - j][i] = matrix[matrixRowSize - 1 - i][matrixColSize - 1 - j];
            matrix[matrixRowSize - 1 - i][matrixColSize - 1 - j] = matrix[j][matrixRowSize - 1 - i];
            matrix[j][matrixRowSize - 1 - i] = tmp;
        }
    }
}

void test()
{
	int i = 0;
	int j = 0;
	int iRes = 0;
	//int b[] = {0,1,0,2,1,0,1,3,2,1,2,1};
	int b[] = {4,1,3,2};
	int Size = 0;
	int iElemNum = 1;
	int **pptr = NULL;


	iRes = singleNumber(b, sizeof(b)/sizeof(b[0]));
	iRes = climbStairs(5);

	printf("Climb way :%d\n", iRes);

}


int main()
{
    int a[] = {1, 2, 7, 8};
    int b[] = {3, 4};
    double  res = 0;
    res = findMedianSortedArrays(a, 4, b, 2);
    printf("The Result: %f\n", res);
    
    return 1;
}
/*
[4,1,3,2]     2 
[4,1,2,3]     3
[4,2,3]        1
[3,2,4]        1
[4,2,2]        0
[4,1,3,2]     2 
[2,3,1,4]     2
*/

/*
	int acMatrix[4][4] = {{0,0,0,5},{4,3,1,4},{1,2,1,3}, {0,0,1,1}};

	pptr = (int **)malloc(sizeof(int *)*4);
	if (NULL == pptr)
		return 1;
	for (i = 0; i < 4; i++)
	{
		pptr[i] = (int *)malloc(sizeof(int)*4);
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			pptr[i][j] = acMatrix[i][j];
	}
	
	setZeroes(pptr, 4, 4);

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", pptr[i][j]);
		}
		printf("\n");
	}
*/
