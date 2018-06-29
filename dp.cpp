#include <math.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

template <class T>
static T** PrimitiveMatrix(int h, int w) {
	unsigned int headLength = h*sizeof(T*);
	unsigned int pieceLength = w*sizeof(T);
	int i;
	char* buf = new char[headLength + h*pieceLength];
	T** matrix = (T**)buf;
	for (i = 0; i < h; ++i) {
		matrix[i] = (T*)&buf[headLength + i*pieceLength];
	}
	return matrix;
}

template <class T, class E>
static void printMatrix(T** matrix, int h, int w, E) {
	int i, j;
	for (i = 0; i < h; ++i) {
		for (j = 0; j < w; ++j) {
			cout << (E)matrix[i][j] << " ";
		}
		cout << endl;
	}
}

/* Calculate the cost matrix and construct the record matrix. */
unsigned int Dopt(const char* X, const char* Y, char**& R)  {
	int m = strlen(X);
	int n = strlen(Y);
	int i, j, k;
	char pre;
	unsigned int penalty, val[3];
	unsigned int** C = PrimitiveMatrix<unsigned int>(m+1,n+1);
	R = PrimitiveMatrix<char>(m+1,n+1);
	for (k = 0; k < m+n+1; ++k) {
		j = n - k;
		if (j < 0) j = 0;
		while (j < n+1) {
			i = m+n-j-k;
			if (i < 0) break;
			if (i == m) {
				C[i][j] = 2*(n-j);
				R[i][j] = 2;
			} else if (j == n) {
				C[i][j] = 2*(m-i);
				R[i][j] = 0;
			} else {
				penalty = X[i] == Y[j] ? 0 : 1;
				val[0] = C[i+1][j] + 2;
				val[1] = C[i+1][j+1] + penalty;
				val[2] = C[i][j+1] + 2;
				pre = val[0] < val[1] ? 0 : 1;
				if (val[2] < val[pre]) pre = 2;
				C[i][j] = val[pre];
				R[i][j] = pre;
			}
			++j;
		}
	}
	R[m][n] = -1;
	unsigned int re = C[0][0];
	delete[] (void*)C;
	return re;
}

/* Construct the optimal alignment with the record matrix */
void Alignment(char* X, char* Y, char** R, string& s1, string& s2) {
	int i, j;
	s1 = s2 = "";
	i = j = 0;
	while (~R[i][j]) {
		switch (R[i][j]) {
		case 0:
			s1 += X[i++];
			s2 += '-';
			break;
		case 1:
			s1 += X[i++];
			s2 += Y[j++];
			break;
		case 2:
			s1 += '-';
			s2 += Y[j++];
			break;
		}
	}
}

/*
int main() {
	char** R;
	char* X = "AA";
	char* Y = "T";
	cout << Dopt(X, Y, R) << endl;
	printMatrix(R, 3, 2, (int)1);
	string Xs, Ys;
	Alignment(X, Y, R, Xs, Ys);
	cout << Xs << endl;
	cout << Ys << endl;
	delete[] (void*)R;
	return 0;
}*/