#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

extern unsigned int Copt(const char*,const char*);
extern unsigned int Dopt(const char*,const char*,char**&);

static string& geneSeq(string& s, unsigned int length) {
	static const char S[] = {'A', 'T', 'G', 'C'};
	s = "";
	int i;
	while (length) {
		i = rand()%4;
		s += S[i];
		--length;
	}
	return s;
}

static const int patch_size = 5;

int main() {
	srand((unsigned int)time(NULL));

	string X, Y;
	const unsigned int lengths[] = {5, 6, 7, 8, 20, 40, 100, 500, 1000, 5000};
	const int group_num = sizeof(lengths) / sizeof(unsigned int);
	unsigned int timeCost[2][group_num];
	unsigned int sum[2];
	int i, j;
	DWORD t;
	char** R;
	for (i = 0; i < group_num; ++i) {
		cout << endl << "length: " << lengths[i] << endl;
		sum[0] = sum[1] = 0;
		for (j = 0; j < patch_size; ++j) {
			geneSeq(X, lengths[i]);
			geneSeq(Y, lengths[i]);

			if (lengths[i] < 9) {
				t = timeGetTime();
				cout << Copt(X.c_str(), Y.c_str()) << " ";
				sum[0] += timeGetTime() - t;
			}

			t = timeGetTime();
			cout << Dopt(X.c_str(), Y.c_str(), R) << endl;
			sum[1] += timeGetTime() - t;
			delete[] R;
		}
		for (j = 0; j < 2; ++j)
			timeCost[j][i] = sum[j] / patch_size;
	}

	cout << endl << "Cost:" << endl << "Copt: ";
	for (i = 0; i < group_num; ++i)
		if (lengths[i] < 9)
			cout << timeCost[0][i] << " ";
	cout << endl << "Dopt: ";
	for (i = 0; i < group_num; ++i)
		cout << timeCost[1][i] << " ";
	cout << endl;

	string pause;
	cin >> pause;

	return 0;
}