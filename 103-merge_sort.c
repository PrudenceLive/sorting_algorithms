#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * PrintArray - prints an array of integers for a range of indices.
 * @array: array of values to be printed
 * @iBeg: starting index value
 * @iEnd: ending index value
 */
void PrintArray(int *array, int iBeg, int iEnd)
{
    int i;

    for (i = iBeg; i < iEnd; i++)
    {
        if (i < iEnd - 1)
            printf("%i, ", array[i]);
        else
            printf("%i\n", array[i]);
    }
}

/**
 * CopyArray - copies elements from source[] to dest[] within a specified range.
 * @source: source array
 * @iBeg: starting index value
 * @iEnd: ending index value
 * @dest: destination array
 */
void CopyArray(int *source, int iBeg, int iEnd, int *dest)
{
    int i;

    for (i = iBeg; i < iEnd; i++)
    {
        dest[i] = source[i];
    }
}

/**
 * TopDownMerge - merges two sorted runs of an array.
 * @source: source array
 * @iBeg: left run starting index value
 * @iMid: right run starting index value
 * @iEnd: right run ending index value
 * @dest: destination array
 */
void TopDownMerge(int *source, int iBeg, int iMid, int iEnd, int *dest)
{
    int i, j, k;

    i = iBeg;
    j = iMid;

    printf("Merging...\n");
    printf("[left]: ");
    PrintArray(source, iBeg, iMid);
    printf("[right]: ");
    PrintArray(source, iMid, iEnd);

    for (k = iBeg; k < iEnd; k++)
    {
        if (i < iMid && (j >= iEnd || source[i] <= source[j]))
        {
            dest[k] = source[i];
            i++;
        }
        else
        {
            dest[k] = source[j];
            j++;
        }
    }

    printf("[Done]: ");
    PrintArray(dest, iBeg, iEnd);
}

/**
 * TopDownSplitMerge - recursive engine of merge_sort, splits the array into runs and merges them.
 * @source: source array
 * @iBeg: starting index value
 * @iEnd: ending index value
 * @dest: destination array
 */
void TopDownSplitMerge(int *source, int iBeg, int iEnd, int *dest)
{
    int iMid;

    if (iEnd - iBeg < 2)
        return;

    iMid = (iEnd + iBeg) / 2;

    TopDownSplitMerge(dest, iBeg, iMid, source);
    TopDownSplitMerge(dest, iMid, iEnd, source);

    TopDownMerge(source, iBeg, iMid, iEnd, dest);
}

/**
 * merge_sort - sorts an array of integers in ascending order using a top-down merge sort algorithm.
 * @array: array of integers to be sorted
 * @size: number of elements in the array
 */
void merge_sort(int *array, size_t size)
{
    int *work_copy;

    if (!array || size < 2)
        return;

    work_copy = malloc(sizeof(int) * size);
    if (!work_copy)
        return;

    CopyArray(array, 0, size, work_copy);
    TopDownSplitMerge(work_copy, 0, size, array);

    free(work_copy);
}

