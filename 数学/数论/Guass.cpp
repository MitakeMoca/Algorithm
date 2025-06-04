#include <bits/stdc++.h>
using namespace std;

#define eps 1e-6

double A[105][105] = {0};

bool Guass(int n);

int main()
{
	int n;
	cin >> n;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n + 1; j++){
			cin >> A[i][j];
		}
	}

	if(Guass(n)){
		for(int i = 1; i <= n; i++){
			printf("%.2f\n", A[i][n + 1]);
		}
	}
	else{
		puts("No Solution");
	}
	return 0;
}

bool Guass(int n)
{
	for(int i = 1; i <= n; i++){

		int r = i;
		for(int j = i; j <= n; j++){
			if(fabs(A[j][i]) > eps){
				r = j;
				break;
			}
		}

		if(r != i) swap(A[r], A[i]);
		if(fabs(A[i][i]) < eps) return false;
		for(int j = n + 1; j >= 1; j--){
			A[i][j] /= A[i][i];
		}

		for(int k = i + 1; k <= n; k++){
			for(int j = n + 1; j >= i; j--){
				A[k][j] -= A[i][j] * A[k][i];
			}
		}

		// for(int k = 1; k <= n; k++){
		// 	for(int j = 1; j <= n + 1; j++){
		// 		cout << A[k][j] << ' ';
		// 	}
		// 	puts("");
		// }
	}

	for(int i = n; i >= 1; i--){
		for(int j = n + 1; j > i; j--){
			A[i][n + 1] -= A[i][j] * A[j][n + 1]; 
		}
	}
	return true;
}