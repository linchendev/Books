#include <iostream>
#include <vector>
using namespace std;

#include <stdlib.h>
#include <stdio.h>

void printResult(vector<int>& a)
{
	for(int i = 0; i < a.size(); ++i)
		::printf("%d ", a[i]);
	::printf("\n");
}

//打印数组的所有排列
//从后往前,更容易理解
//permgen2(a, 4);
void permgen1(vector<int>& a, int n)
{
	if(n == 0) {
		printResult(a);
	} else {
		for(int i = 0; i < n; ++i)
		{
			swap(a[i], a[n-1]);
			permgen1(a, n-1);
			swap(a[n-1], a[i]);	//回溯后a排列保持不变
		}
	}
}

//从前往后
void permgen2(vector<int>& a, int n)
{
	if(n == a.size()) {
		printResult(a);
	} else {
		for(int i = n; i < a.size(); ++i)
		{
			swap(a[i], a[n]);
			permgen2(a, n+1);
			swap(a[n], a[i]);	//回溯后a排列保持不变
		}
	}
}

//从N个数组取M个数进行排列组合
void permgenM(vector<int>& a, int n, int M)
{
	if(n == M) {
		printResult(a);
	} else {
		for(int i = n; i < M; ++i)
		{
			swap(a[i], a[n]);
			permgenM(a, n+1, M);
			swap(a[n], a[i]);	//回溯后a排列保持不变
		}
	}
}

//组合，从n中取m个数进行组合,a中数字互斥
//组合不够散列!比如5 4 6就不能出现,但满足互斥需求，因为并不是要求全排列
void comb(vector<int>& a, vector<int>& b, int n, int m)
{
	int i;
	if(m == 0) {
		printResult(b);	
	} else {
		for(int i = n - 1; i >= 0; --i)
		{
			b[m-1] = a[i];
			comb(a, b, i, m-1);
		}
	}
}

int main()
{
	vector<int> a, b;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	//permgenM(a, 0, 2);
	b.resize(3);	
	comb(a, b, a.size(), 3);
}

