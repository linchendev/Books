//排序算法
#include <iostream>
#include "Array.h"
#include <exception>

using namespace std;

//1.快速排序
//方式一：offer书中提供的一种实现,
//从一个方向同时推进
//采用随机pivotkey的方式
int Partition_1(int array[], int len, int start, int end)
{
	if(array == NULL || len <= 0 || start < 0 || end >= len)
		throw new std::exception();

	int index = RandomInRange(start, end);
	Swap(&array[index], &array[end]);

	int small = start - 1;
	for(index = start; index < end; ++index)
	{
		if(array[index] < array[end])
		{
			++small;
			if(small != index)
			{
				Swap(&array[index], &array[small]);
			}
		}
	}

	++small;
	Swap(&array[small], &array[end]);

	return small;
}

void QuickSort_1(int array[], int len, int start, int end)
{
	if(array == NULL || len == 0)
		return;

	int index = Partition_1(array, len, start, end);
	if(index > start)
		QuickSort_1(array, len, start, index-1);
	if(index < end)
		QuickSort_1(array, len, index+1, end);
}

//方式二
//从两个方向向中间靠近
//算法条件:1.选取start作为pivotkey（必须），最后low的位置的值就是pivotkey,所以最后一个交换是没有必要的
int QuickSort_2(int array[], int len, int start, int end)
{
	if(array == NULL || len <= 0 || start < 0 || end >= len)
		throw new std::exception();

	if(start < end)
	{
		int index = start;
		int high = end;
		int low = start;
		int pivotkey = array[low];

		while(low < high)
		{
			while(array[high] > pivotkey && high > low)
				--high;
			
			if(high != low)
			{
				int temp = array[high];
				array[high] = array[low];
				array[low] = temp;
			}

			//两个while中必须有一个带上等于处理，也可以同时带上
			while(array[low] <= pivotkey && low < high)
				++low;	

			if(low != high)
			{
				int temp = array[low];
				array[low] = array[high];
				array[high] = temp;
			}
		}

		//这句代码非常关键,这个index位置的值肯定是小于等于pivotkey
		index = low;
		//array[index] = pivotkey;
		QuickSort_2(array, len, start, index-1);
		QuickSort_2(array, len, index+1, end);
	}
}

//STL,最佳
void QuickSort_3(int array[], int len, int start, int end)
{
	if(array == NULL || len <= 1 || start >= end)
		return;

	//这里还可以进行优化，取首,尾,中三个值进行比较去中间值
	int pivotIndex = start;
	int pivotValue = array[start];
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


void InsertSort_1(int array[], int len)
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
//节省了一个边界判断，在处理大数据时可以显著优化
void InsertSort_2(int array[], int len)
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
	int a[] = {1,2,1,9,9,4,5,6,6,7,8};

	int len = sizeof(a)/sizeof(int);
	//QuickSort_1(a, len, 0, len-1);
	QuickSort_2(a, len, 0, len-1);

	for(int i = 0; i < len; ++i)
		std::cout << a[i] << std::endl;
}
