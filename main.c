//Hansen Patrick
//3/24/2024
//Computer Science I Bonus Assignment

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// Swap function to interchange values of two integers
void swap(int* p1, int* p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Function to allocate memory with tracking of extra memory allocated
void *Alloc(size_t sz)
{
    // Update the count of extra memory allocated
    extraMemoryAllocated += sz;

    // Allocate memory for size and data
    size_t* ret = malloc(sizeof(size_t) + sz);

    // Store size at the beginning of the memory block
    *ret = sz;

    // Return a pointer to the memory block after the size
    return &ret[1];
}

// Function to deallocate memory and update the count of extra memory allocated
void DeAlloc(void* ptr)
{
    // Get the pointer to the size stored before the memory block
    size_t* pSz = (size_t*)ptr - 1;

    // Update the count of extra memory allocated
    extraMemoryAllocated -= *pSz;

    // Free the memory block
    free((size_t*)ptr - 1);
}

// Function to get the size of a dynamically allocated memory block
size_t Size(void* ptr)
{
    // Get the size stored before the memory block
    return ((size_t*)ptr)[-1];
}


void bubbleSort(int* pData, int n)
{
    // Iterate through the array
    for (int i = 0; i < n - 1; i++) {
        // Iterate through the unsorted part of the array
        for (int j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements and swap if necessary
            if (pData[j] > pData[j + 1]) {
                swap(&pData[j], &pData[j+1]);
            }
        }
    }
}



void insertionSort(int* pData, int n)
{
    // Iterate through the array starting from the second element
    for (int i = 1; i < n; i++) {
        // Store the current element
        int num = pData[i];
        int j = i - 1;

        // Move elements of pData[0..i-1], that are greater than num, to one position ahead of their current position
        while (j >= 0 && pData[j] > num) {
            pData[j + 1] = pData[j];
            j = j - 1;
        }

        // Insert num into the correct position
        pData[j + 1] = num;
    }
}



void selectionSort(int* pData, int n)
{
    // Iterate through the array
    for (int i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted part of the array
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (pData[j] < pData[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the first element
        swap(&pData[minIndex], &pData[i]);
    }
}


void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        while (parent < n / 2) {
            int maxChild = 2 * parent + 1; // Left child
            if (maxChild + 1 < n && arr[maxChild] < arr[maxChild + 1]) {
                // Right child exists and is greater than left child
                maxChild++;
            }
            if (arr[parent] < arr[maxChild]) {
                // Swap parent with the largest child if parent is smaller
                swap(&arr[parent],&arr[maxChild]);
            }
            parent = maxChild;
        }
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0],&arr[i]);

        // Heapify the reduced heap
        int parent = 0;
        while (parent < i / 2) {
            int maxChild = 2 * parent + 1; // Left child
            if (maxChild + 1 < i && arr[maxChild] < arr[maxChild + 1]) {
                // Right child exists and is greater than left child
                maxChild++;
            }
            if (arr[parent] < arr[maxChild]) {
                // Swap parent with the largest child if parent is smaller
                swap(&arr[parent],&arr[maxChild]);
            }
            parent = maxChild;
        }
    }
}


void mergeSort(int pData[], int l, int r)
{
    if (l < r) {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Call mergeSort for both halves
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);

        // Merge the sorted halves
        int n1 = m - l + 1;
        int n2 = r - m;
        int *L = (int *)Alloc(n1 * sizeof(int));
        int *R = (int *)Alloc(n2 * sizeof(int));

        // Copy data to temp arrays L[] and R[]
        for (int i = 0; i < n1; i++)
            L[i] = pData[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = pData[m + 1 + j];

        // Merge the temp arrays back into pData[l..r]
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                pData[k] = L[i];
                i++;
            } else {
                pData[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], if there are any
        while (i < n1) {
            pData[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[], if there are any
        while (j < n2) {
            pData[k] = R[j];
            j++;
            k++;
        }

        // Deallocate the memory used for temporary arrays
        DeAlloc(L);
        DeAlloc(R);
    }
}

int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    int i, n, *data;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i=0;i<dataSz;++i)
        {
            fscanf(inFile, "%d ",&n);
            data = *ppData + i;
            *data = n;
        }

        fclose(inFile);
    }

    return dataSz;
}


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
    char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };

    for (i=0;i<4;++i)
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


        printf("Heap Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        heapSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }

}
