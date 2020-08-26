#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int main()
{
	ofstream myfile;
	myfile.open("resultnew(5,10).txt");
	FILE* fp1;
	FILE* fp2;
	fp1 = fopen("Alist_A_1024(5,10).txt", "r");
	fp2 = fopen("Alist_B_1024(5,10).txt", "r");
	int n = 1024;
	int k = 512;
	int dc = 10;
	int dv = 5;
	int cnt = 0;
	//long int A[k][dc] = {0};
	int* A = (int*)malloc(k * dc * sizeof(int));
	//int B[n][dv] = {0};
	int* B = (int*)malloc(n * dv * sizeof(int));
	//int G[k][n] = {0};
	int* G = (int*)malloc(k * n * sizeof(int));
	int c1;
	int c2;
	int a1;
	int a2;
	int b1;
	int b2;
	while (1)
	{

		fscanf(fp1, "%d", &c1);
		fscanf(fp2, "%d", &c2);

		cnt = cnt + 1;
		a1 = (cnt - 1) / dc;
		b1 = (cnt - 1) % dc;
		a2 = (cnt - 1) / dv;
		b2 = (cnt - 1) % dv;
		B[a2 * dv + b2] = c2;
		//A[a1][b1] = c1;
		A[a1 * dc + b1] = c1;
		if (feof(fp1)) {
			break;
		}

	}
	fclose(fp1);
	fclose(fp2);

	int e = 2;
	float eps[20];
	//cfloat d
	double D1[20];
	double S;
	double t1;
	for (int i0 = 0; i0 < 20; i0++) {
		eps[i0] = 0.5 + 0.02 * (i0);

		t1 = 0;
		S = 0;
		while (t1 != 100) {
			int y[1024] = { 0 };
			int y2[1024] = { 0 };
			int cn = 0;
			vector<int> res;
			vector<int> C;
			for (int i = 1; i < n + 1; i++) {
				double a = ((double)rand() / (RAND_MAX));
				if (a > (1 - eps[i0])) {
					y[i - 1] = e;
					y2[i - 1] = e;

				}
				else if (a > (1 - eps[i0]) / 2 && a < (1 - eps[i0])) {
					y[i - 1] = 0;
					y2[i - 1] = 0;
					cn = cn + 1;
				}
				else if (a > 0 && a < (1 - eps[i0]) / 2) {
					y[i - 1] = 1;
					y2[i - 1] = 1;
					cn = cn + 1;
				}

			}

			int cnt0 = 1;
			int cnt1;
			int cnt2 = 0;
			int a;
			while (cn != 0 && cnt0 != 0) {
				cnt0 = 0;
				for (int i = 0; i < k; i++) {
					cnt1 = 0;
					for (int j = 0; j < dc; j++) {
						if (A[i * dc + j] != 0) {
							G[i * n + A[i * dc + j] - 1] = 1;
							if (y[A[i * dc + j] - 1] != e) {
								cnt1 = cnt1 + 1;
								a = j;
							}
						}
					}
					if (cnt1 == 1) {
						cnt0 = cnt0 + 1;
						cnt2 = cnt2 + 1;
						res.push_back(i);
						C.push_back(A[i * dc + a] - 1);
						y[A[i * dc + a] - 1] = e;

					}
				}
				cn = 0;
				for (int i = 0; i < n; i++) {
					if (y[i] != e) {
						cn = cn + 1;
					}
				}

			}
			int w[512] = { 0 };
			for (int i = cnt2; i > 0; i--) {
				for (int j = 0; j < dv; j++) {
					if (B[C[i - 1] * dv + j] != 0) {
						if (res[i - 1] != B[C[i - 1] * dv + j] - 1) {
							w[res[i - 1]] = w[res[i - 1]] + w[B[C[i - 1] * dv + j] - 1];
						}
					}
				}
				w[res[i - 1]] = (w[res[i - 1]] + y2[C[i - 1]]) % 2;
			}
			int Y[1024] = { 0 };
			int D[1024] = { 0 };
			float s = 0;

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < k; j++) {
					Y[i] = w[j] * G[j * n + i] + Y[i];
				}
				Y[i] = Y[i] % 2;
				if (y2[i] != e) {
					D[i] = (Y[i] + y2[i]) % 2;
					if (D[i] == 1) {
						s = s + 1;
					}
				}
			}
			S = S + s;
			t1 = t1 + 1;

		}
		D1[i0] = S / (n * t1);
		myfile << D1[i0] << " ";
		myfile << eps[i0] << "\n";
		printf("\n%E %E", D1[i0], eps[i0]);

	}
	myfile.close();
	return 0;
}

