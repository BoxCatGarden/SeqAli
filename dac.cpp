#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))

static int m, n;
static const char *X, *Y;

static unsigned int opt(int i, int j) {
	if (i == m) return 2*(n-j);
	else if (j == n) return 2*(m-i);
	else {
		unsigned int penalty = X[i] == Y[j] ? 0 : 1;
		return min(penalty + opt(i+1, j+1), min(2+opt(i+1, j),2+opt(i, j+1)));
	}
}

unsigned int Copt(const char* s1, const char* s2) {
	X = s1, Y = s2;
	m = strlen(X), n = strlen(Y);
	return opt(0,0);
}

/*
int main() {
	unsigned int cost;
	//system("pause");
	cin >> cost;
	cost = Copt("AACGTG", "TGGAAA");
	cout << cost << endl;

	return 0;
}*/