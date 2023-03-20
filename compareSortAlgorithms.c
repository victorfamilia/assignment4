#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L = (int*) malloc(n1*sizeof(int));
	int *R = (int*) malloc(n2*sizeof(int));

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}	
	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{	

	if (l < r) {
    	// Same as (l+r)/2, but avoids overflow for
    	// large l and h
    	int m = l + (r - l) / 2;
  
    	// Sort first and second halves
    	mergeSort(pData, l, m);
    	mergeSort(pData, m + 1, r);
  
     	merge(pData, l, m, r);
    }

}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	
	int i, item, j;
	for (i = 1; i < n; i++)
	{
		item = *(pData + i);
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		for(j=i-1; j>=0; j--)
		{
			if(*(pData + j) > item)
			 *(pData + j + 1) = *(pData + j);
			else
			 break;
		}
		*(pData + j + 1) = item;	
	}

}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{

	int i, j,temp;
	for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++)
		{

			if (*(pData + j) > *(pData + j + 1))
			{//then swap
				temp = *(pData + j);
				*(pData + j) = *(pData + j + 1);
				*(pData + j + 1) = temp;
			}
		}
	}

}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	
	int i, j, min_idx, temp;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (*(pData + j) < *(pData + min_idx))
			min_idx = j;
		// Swap the found minimum element with the first element
		temp = *(pData + i);
		*(pData + i) = *(pData + min_idx);
		*(pData + min_idx) = temp;
	}

}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		{
			for (int i=0;i<dataSz;++i)
			{
			fscanf(inFile, "%d\n", *ppData + i);
			}
		}	
	}	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}