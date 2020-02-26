#include <bits/stdc++.h>
using namespace std;

int main () {
	FILE *csv = fopen("finalResult.csv", "r");
	int nusp;
	char *nome;
	cout << fscanf(csv, "%m[^,],%d,%*s", &nome, &nusp) << endl;
	cout << string(nome) << nusp << endl;
}
