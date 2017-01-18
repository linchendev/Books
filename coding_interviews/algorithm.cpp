/**
 * \brief 一些算法
 *
 */

#include <iostream>
#include <deque>
#include <vector>
#include <map>
using namespace std;

#include <stdlib.h>

// 马尔可夫链
enum {
	NPREF	= 2,		/*number of prefix words*/
	NHASH	= 4093,		/*size of state hash table array*/
	MAXGEN	= 10000,	/*maxinum words generated*/
	MULTIPLIER = 256,
};

typedef deque<string> Prefix;
map<Prefix, vector<string> >  statetab;	//prefix -> suffixes

void add(Prefix& prefix, const string& s)
{
	if(prefix.size() == NPREF) {
		statetab[prefix].push_back(s);
		prefix.pop_front();
	}
	prefix.push_back(s);
}

void build(Prefix& prefix, istream& in)
{
	string buf;
	while(in >> buf)	//自动以空格进行了分割
		add(prefix, buf);
}

string NONWORD("\n");

void generate(int nwords)
{
	Prefix prefix;
	int i;

	for(i = 0; i < NPREF; i++)
		add(prefix, NONWORD);

	for(i = 0; i < nwords; i++) {
		vector<string>& suf = statetab[prefix];
		const string& w = suf[rand() % suf.size()];
		if(w == NONWORD)
			break;
		cout << w << "\n";
		prefix.pop_front();
		prefix.push_back(w);
	}
}

int main()
{
	int nwords = MAXGEN;
	Prefix prefix;

	int i;
	for(i = 0; i < NPREF; i++)
		add(prefix, NONWORD);

	build(prefix, cin);
	add(prefix, NONWORD);
	generate(nwords);
	return 0;
}
