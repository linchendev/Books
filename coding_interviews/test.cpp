#include <iostream>
#include <vector>
using namespace std;

#include <string.h>
#include <stdlib.h>

int main()
{
	/*
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	swap(a[0], a[1]);

	for(int i = 0; i < a.size(); ++i)
		cout << a[i] << endl;
		*/

	/*
	string buf;
	while(cin >> buf)	//以空格进行分割
		cout << buf << endl;
	*/

	/*
	char *a[2];

	a[0] = new char('a');
	a[1] = new char('b');

	for(int i = 0; i < 2; i++)
		cout << *(a[i]) << endl;
		*/

	char NONWORD[] = "\n";

	cout << sizeof(NONWORD)/sizeof(char) << endl;
	cout << strlen(NONWORD) << endl;
}
