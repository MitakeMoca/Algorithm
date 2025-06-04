#include <bits/stdc++.h>
using namespace std;

int A[1000000] = {0};
int B[1000000] = {0};
int C[1000000] = {0};
int Sa, Sb, Sc;

void addLarge();
void subLarge();
void mulLarge();
bool cmp();

int main()
{
	string a, b;
	cin >> a >> b;

	Sa = a.size();
	Sb = b.size();
	for(int i = 0; i < a.size(); i++){
		A[i] = (a[Sa - i - 1] ^ 48);
	}

	for(int i = 0; i < b.size(); i++){
		B[i] = (b[Sb - i - 1] ^ 48);
	}

	//addLarge();
	//subLarge();
	mulLarge();
	return 0;
}

void addLarge()
{
	Sc = max(Sa, Sb);
	for(int i = 0; i < Sc; i++){
		C[i] += A[i] + B[i];
		C[i + 1] = C[i] / 10;
		C[i] %= 10;
	}

	while(C[Sc] != 0){
		C[Sc + 1] = C[Sc] / 10;
		C[Sc++] %= 10;
	}

	for(int i = Sc - 1; i >= 0; i--){
		cout << C[i];
	}
}

void subLarge()
{
	if(!cmp()){
		cout << "-";
		swap(A, B);
		swap(Sa, Sb);
	}

	Sc = max(Sa, Sb);
	for(int i = 0; i < Sc; i++){
		C[i] = A[i] - B[i];
		if(C[i] < 0){
			C[i] += 10;
			A[i + 1]--;
		}
	}

	while(Sc > 1 && C[Sc - 1] == 0) Sc--;
	for(int i = Sc - 1; i >= 0; i--) cout << C[i];
}

bool cmp()
{
	if(Sa != Sb) return Sa > Sb;
	for(int i = Sa - 1; i >= 0; i--){
		if(A[i] != B[i]) return A[i] > B[i];
	}
	return true;
}

void mulLarge()
{
	Sc = Sa + Sb;

	for(int i = 0; i < Sa; i++){
		for(int j = 0; j < Sb; j++){
			C[i + j] += A[i] * B[j];
			C[i + j + 1] += C[i + j] / 10;
			C[i + j] %= 10;
		}
	}

	while(Sc > 1 && C[Sc - 1] == 0) Sc--;
	for(int i = Sc - 1; i >= 0; i--) cout << C[i];
}