/**
 * \brief 一些算法
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*=======================markov-chain 马尔可夫链=====================================*/
enum {
	NPREF	= 2,		/*number of prefix words*/
	NHASH	= 4093,		/*size of state hash table array*/
	MAXGEN	= 10000,	/*maxinum words generated*/
	MULTIPLIER = 16,
};

typedef struct State State;
typedef struct Suffix Suffix;
/* prefix + suffix list */
struct State {
	char	*pref[NPREF];	/* prefix words */
	Suffix	*suf;			/* list of suffixes */
	State	*next;			/* next in hash table */
};

/* list of suffixes */
struct Suffix {
	char	*word;	/* suffix */
	Suffix	*next;	/* next in list of suffixes */
};

/* hash table of states */
State *statetab[NHASH];

char NONWORD[] = "\n";	/* cannot appear as real word */

void addsuffix(State *sp, char *suffix);
void add(char *prefix[NPREF], char *suffix);

/* hash: compute hash value for array of NHASH strings */
unsigned int hash(char *s[NPREF])
{
	unsigned int h;
	unsigned char *p;
	int i;

	h = 0;
	for(i = 0; i < NPREF; i++)
	{
		for(p = (unsigned char *) s[i]; *p != '\0'; p++)
			h = MULTIPLIER * h + *p;
		return h % NHASH;
	}
}

/* lookup: search for prefix; create if request.
 * returns pointer if present or created; NULL if not
 * creation doesn't strdup so strings mustn't change later.
 */
State* lookup(char *prefix[NPREF], int create)
{
	int i, h;
	State *sp = NULL;

	h = hash(prefix);
	for(sp = statetab[h]; sp != NULL; sp = sp->next) {
		for(i = 0; i < NPREF; i++) {
			if(strcmp(prefix[i], sp->pref[i]) != 0)
				break;
		}

		if(i == NPREF)	/* found it */
			return sp;
	}

	if(create) {
		sp = (State *)malloc(sizeof(State));
		for(i = 0; i < NPREF; i++) {
			sp->pref[i] = prefix[i];
		}
		sp->suf = NULL;
		sp->next = statetab[h];
		statetab[h] = sp;
	}
	return sp;
}

/* build: read input, build prefix table */
void build(char *prefix[NPREF], FILE *f)
{
	//假设单词长度9
	char buf[10] = {0}, fmt[10];

	/* create a format string; %s could overflow buf */
	sprintf(fmt, "%%%ds", sizeof(buf)-1);	/* %99s */
	while(fscanf(f, fmt, buf) != EOF) {
		//printf("build: %s %s %s\n", prefix[0], prefix[1], buf);
		add(prefix, buf);
		bzero(buf, sizeof(buf));
	}
}

/* add: add word to suffix list, update prefix */
void add(char *prefix[NPREF], char *suffix)
{
	State *sp;

	int len = strlen(suffix);
	char* p = (char *)malloc(len+1);
	strcpy(p, suffix);

	sp = lookup(prefix, 1);	/* create if not found */
	addsuffix(sp, p);
	/* move the words down the prefix */
	printf("add,prefix: %s, %s %s\n", prefix[0], prefix[1], p);	//指针
	memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
	prefix[NPREF-1] = p;
}

/* addsuffix: add to state. suffix must not change later */
void addsuffix(State *sp, char *suffix)
{
	Suffix *suf;

	suf = (Suffix *) malloc(sizeof(Suffix));
	suf->word = suffix;
	suf->next = sp->suf;
	sp->suf = suf;
}

/* generate: produce output, one word per line */
void generate(int nwords)
{
	State *sp;
	Suffix *suf;
	char *prefix[NPREF], *w;
	int i, nmatch;

	for(i = 0; i < NPREF; i++)	/*reset initial prefix*/
		prefix[i] = NONWORD;

	for(i = 0; i < nwords; i++) {
		sp = lookup(prefix, 0);
		if(!sp) {
			printf("nullptr!");
			return;
		}
		printf("%d: %s - %s\n", i, prefix[0], prefix[1]);
		nmatch = 0;
		for(suf = sp->suf; suf != NULL; suf = suf->next) {
			if(rand()%++nmatch == 0)	/*prob = 1/nmatch*/
				w = suf->word;
		}

		if(strcmp(w, NONWORD) == 0)
			break;

		printf("%s\n", w);
		memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
		prefix[NPREF-1] = w;
	}
}

/*=======================markov-chain 马尔可夫链=====================================*/

int main()
{
	int i, nwords = MAXGEN;
	char *prefix[NPREF];
	
	for(i = 0; i < NPREF; i++) {
		//prefix[i] = (char *)malloc(sizeof(char));
		//*(prefix[i]) = NONWORD[0];
		prefix[i] = NONWORD;	//直接存全局变量地址
	}

	build(prefix, stdin);
	add(prefix, NONWORD);
	generate(nwords);
	return 0;
}

