#include <iostream>
#include <stdlib.h>
using namespace std;

//rand[start, end]
int RandBetween(int min, int max)
{
	//TODO:max,min检查..
	return rand()%(max-min+1) + min;
}

void SwapInt(int array[], int from, int to)
{
	int temp = array[from];
	array[from] = array[to];
	array[to] = temp;
}

//随机节点
//这种方式好，边界条件少，容易记
void QuickSort_1(int array[], int len, int start, int end)
{
	if(array == NULL || len <= 1 || start >= end)
		return;

	int pivotIndex = RandBetween(start, end);
	SwapInt(array, pivotIndex, end);

	int small = start - 1;
	for(int index = start; index < end; ++index)
	{
		if(array[index] < array[end])
		{
			small++;
			if(small != index)
			{
				SwapInt(array, small, index);
			}
		}
	}

	++small;
	SwapInt(array, small, end);

	if(small > start)
		QuickSort_1(array, small-start, start, small-1);
	if(small < end)
		QuickSort_1(array, end-small, small+1, end);
}

//选取首个字段作为pivotkey
void QuickSort_2(int array[], int len, int start, int end)
{
	if(array == NULL || len <= 1 || start >= end)
		return;

	int pivotIndex = start;
	int pivotValue = array[start];
	int low = start;
	int high = end;
	
	while(low < high)
	{
		while(array[high] >= pivotValue && high > low)
			--high;
		if(high != low)
		{
			SwapInt(array, low, high);
		}

		while(array[low] <= pivotValue && low < high)
			++low;
		if(high != low)
		{
			SwapInt(array, low, high);
		}
	}

	pivotIndex = low;
	if(pivotIndex > start)
		QuickSort_1(array, pivotIndex-start, start, pivotIndex-1);
	if(pivotIndex < end)
		QuickSort_1(array, end-pivotIndex, pivotIndex+1, end);
}

int median(int array[], int start, int end)
{
	if(end - start <= 1)
		return start;

	int a = array[start];
	int mid = (end-start)/2 + start;
	int b = array[mid];
	int c = array[end];

	if(a < b)
		if(b < c)
			return b;
		else if(a < c)
			return c;
		else
			return a;
	else if(a < c)
		return a;
	else if(b < c)
		return c;
	else
		return b;
}

//STL,最佳
void QuickSort_3(int array[], int len, int start, int end)
{
	if(array == NULL || len <= 1 || start >= end)
		return;

	int pivotIndex = median(array, start, end);
	int pivotValue = array[pivotIndex];

	cout << pivotIndex << "-" << pivotValue << endl;
	int low = start;
	int high = end+1;
	
	while(true)
	{
		while(array[low] < pivotValue) ++low;
		--high;
		while(pivotValue < array[high]) --high;
		if(!(low < high))
			break;
		SwapInt(array, low, high);
		++low;
	}

	pivotIndex = low;
	array[pivotIndex] = pivotValue;
	if(pivotIndex > start)
		QuickSort_3(array, pivotIndex-start, start, pivotIndex-1);
	if(pivotIndex < end)
		QuickSort_3(array, end-pivotIndex, pivotIndex+1, end);
}

//3个循环
void InsertSort_1(int array[], int len)
{
	if(array == NULL || len <= 1)
		return;

	for(int i = 1; i < len; ++i)
	{
		int j = 0;
		int temp = array[i];
		for(; j <= i-1; ++j)
		{
			if(temp < array[j])
				break;
		}

		if(j <= i-1)
		{
			for(int x = i; x >= j+1; --x)
				array[x] = array[x-1];
			array[j] = temp;
		}
	}
}

//2个循环
void InsertSort_2(int array[], int len)
{
	if(array == NULL || len <= 1)
		return;

	for(int i = 1; i < len; ++i)
	{
		int j = i-1;
		int temp = array[i];
		for(; j >= 0 && temp < array[j]; --j)
		{
			array[j+1] = array[j];
		}
		array[j+1] = temp;
	}
}

void copy_backward(int array[], int start, int end)
{
	for(int i = end; i > start; --i)
		array[i] = array[i-1];
}

//STL
void InsertSort_3(int array[], int len)
{
	if(array == NULL || len <= 1)
		return;

	for(int i = 1; i < len; ++i)
	{
		int temp = array[i];
		if(temp < array[0])
		{
			copy_backward(array, 0, i);
			array[0] = temp;
		}
		else
		{
			int last = i;
			int next = i;
			--next;
			while(temp < array[next])
			{
				array[last] = array[next];
				last = next;
				--next;
			}
			array[last] = temp;
		}
	}
}


int main()
{
	int ar[] = {2,2,3,4,1,5,89,3,444};
	int len = sizeof(ar)/sizeof(int);
	QuickSort_3(ar, len, 0, len-1);
	//InsertSort_3(ar, len);

	for(int i = 0; i < len; ++i)
		cout << ar[i] << endl;

	return 0;
}
