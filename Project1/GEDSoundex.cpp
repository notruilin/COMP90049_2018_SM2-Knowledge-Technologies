#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;

const int INSERT = 1, DELETE = 1, REPLACE = 1, SWAP = 1, MATCH = 0, MAXN = 35, MAXA = 125;
const int DICTLEN = 380000, WIKILEN = 4500;

char dict[DICTLEN][MAXN];
char correct[WIKILEN][MAXN];
int dictLen = 0, corLen = 0;
int dis[DICTLEN];
int trans[MAXA];

void init() {
	char str[MAXN];
	freopen("dict.txt","r",stdin);
	while (scanf("%s",str)!=EOF)
		strcpy(dict[dictLen++],str);
	freopen("wiki_correct.txt","r",stdin);
	while (scanf("%s",str)!=EOF)
		strcpy(correct[corLen++],str);
	freopen("wiki_misspell.txt","r",stdin);
	freopen("GEDSoundexResult.txt","w",stdout);
	trans['a']=trans['e']=trans['h']=trans['i']=trans['o']=trans['u']=trans['w']=trans['y'] = '0';
	trans['b']=trans['p']=trans['f']=trans['v'] = '1';
	trans['c']=trans['g']=trans['j']=trans['k']=trans['q']=trans['s']=trans['x']=trans['z'] = '2';
	trans['d']=trans['t'] = '3';
	trans['l'] = '4';
	trans['m']=trans['n'] = '5';
	trans['r'] = '6';
}

string soundex(string s) {
	int i;
	//cout << "0 " << s << endl;
	for (i=1; i<s.length(); i++) {
		s[i] = trans[s[i]];
	}
	//cout << "1 " << s << endl;
	string str = s.substr(0,1);
	for (i=1; i<s.length(); i++) {
		if (s[i] != s[i-1])
			str += s[i];
	}
	//cout << "2 " << str << endl;
	s = str.substr(0,1);
	for (i=1; i<str.length(); i++) {
		if (str[i] != '0') {
			s += str[i];
		}
	}
	//cout << "3 " << s << endl;
	return s.substr(0,4);
}

int min3(int a,int b,int c) {
	a = min(a,b);
	return min(a,c);
}

int isEqual(char a, char b) {
	if (a == b)
		return MATCH;
	else
		return REPLACE;
}

int globalEditDistance(char* f, char* t) {
	int j,k,lt,lf;
	int A[MAXN][MAXN];
	lf = strlen(f);
	lt = strlen(t);
	A[0][0] = 0;
	for (j=1; j<=lt; j++)	A[j][0] = j * INSERT;
	for (k=1; k<=lf; k++)	A[0][k] = k * DELETE;
	for (j=1; j<=lt; j++)
		for (k=1; k<=lf; k++) {
			A[j][k] = min3(
				A[j][k-1] + DELETE,
				A[j-1][k] + INSERT,
				A[j-1][k-1] + isEqual(f[k-1], t[j-1]));
			if (j>=2 && k>=2 && f[k-1] == t[j-2] && f[k-2] == t[j-1]) {
				A[j][k] = min(A[j][k], A[j-2][k-2]+SWAP);
			}
		}
	return A[lt][lf];
}

void test() {
	char misWord[MAXN],transMisWord[MAXN],transDict[MAXN],c;
	int attempt = 0, i, rightW = 0, index = 0;
	int minDistance, minSoundex;
	while (scanf("%s",misWord)!=EOF) {
		c = ' ';
		minDistance = 0x7fffffff;
		minSoundex = 0x7fffffff;
		for (i = 0; i < dictLen; i++) {
			dis[i] = globalEditDistance(misWord, dict[i]);
			minDistance = min(minDistance, dis[i]);
		}
		printf("Misspell Word:%s\n", misWord);
		printf("GED Predicted Words: ");
		for (i = 0; i < dictLen; i++) {
			if (dis[i] == minDistance) {
				printf("%s ",dict[i]);
				strcpy(transMisWord,soundex(misWord).c_str());
				strcpy(transDict,soundex(dict[i]).c_str());
				dis[i] = globalEditDistance(transMisWord, transDict);
				if (dis[i] < minSoundex)
					minSoundex = dis[i];
			}
			else
				dis[i] = 0x7fffffff;
		}
		printf("\nFinal Predicted Words: ");
		for (i = 0; i < dictLen; i++) {
			if (dis[i] == minSoundex) {
				++attempt;
				if (strcmp(dict[i], correct[index])==0) {
					c = 'O';
					++rightW;
				}
				printf("%s ",dict[i]);
			}
		}
		if (c == ' ')	c = 'X';
		printf("\nMinimum GED distance: %d\n", minDistance);
		printf("Minimum Soundex distance: %d\n", minSoundex);
		printf("correct: %s %c\n\n", correct[index], c);
		++index;
	}
	printf("The number of correct responses: %d\n", rightW);
	printf("The number of attempted responses: %d\n", attempt);
	printf("The number of misspelled words: %d\n", corLen);
	printf("Precision: %.3lf\n", (double)rightW/attempt);
	printf("Recall: %.3lf\n", (double)rightW/corLen);
}

int main() {
	clock_t start,end;
	start = clock();
	init();
	test();
	end = clock();
	printf("\nRun Time: %lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
