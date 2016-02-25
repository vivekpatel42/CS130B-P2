#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

typedef struct { 
	int** length;
	char** direction;
	int lcsLength;
} LCS, *LCS_PTR;

LCS_PTR findLCSLength(char* m, char* n, int x, int y);
void printLCS(char** dMatrix, char* str, int i, int j);

int main() 
{
	int n, k, x, y, i = 0;
	string line;
	char *token, *tempStr;
	char* strArr[2], *str1, *str2;
	LCS_PTR lcsResult = new LCS;
	while (getline(cin,line))
	{
		k = 0;
		if (i == 0) {
			n = atoi(line.c_str());
			i++;
		}
		else {
			tempStr = new char[line.size() + 1];
			strcpy(tempStr, line.c_str());
			token = strtok(tempStr, " ");
			while(token != NULL) {
				strArr[k++] = token;
				token = strtok(NULL, " ");
			}
			str1 = strArr[0], str2 = strArr[1];
			printf("%s %s\n", str1, str2);
			x = strlen(str1), y = strlen(str2);
			printf("%d, %d\n", x, y);
			lcsResult = findLCSLength(str1, str2, x, y);
			printf("The longest common subsequence between %s and %s is of size %d.\n", str1, str2, lcsResult->lcsLength);
			printLCS(lcsResult -> direction, str1, x-1, y-1);
		}
	}
	
	return 1;
	for(int i = 0; i < x; i++) {
		delete[] (lcsResult -> length)[i];
		delete[] (lcsResult -> direction)[i];
	}
	delete[] (lcsResult -> length);
	delete[] (lcsResult -> direction);
	return 0;
}

LCS_PTR findLCSLength(char* m, char* n, int x, int y) {
	LCS_PTR result = new LCS;
	int max = 0;
	int** lengthMatrix = new int*[x];
	char** directionalMatrix = new char*[x];
	for(int i = 0; i < x; i++) {
		lengthMatrix[i] = new int[y];
		directionalMatrix[i] = new char[y];
	}
	for(int i = 1; i < x; i++) {
		lengthMatrix[i][0] = 0;
	}
	for(int j = 1; j < y; j++) {
		lengthMatrix[0][j] = 0;
	}
	for(int i = 1; i < x; i++) {
		for(int j = 1; j < y; j++) {
			if(m[i] == n[j]) {
				lengthMatrix[i][j] = lengthMatrix[i-1][j-1] + 1;
				directionalMatrix[i][j] = 'D';
			}
			else if(lengthMatrix[i-1][j] >= lengthMatrix[i][j-1]) {
				lengthMatrix[i][j] = lengthMatrix[i][j-1];
				directionalMatrix[i][j] = 'U';
			}
			else {
				lengthMatrix[i][j] = lengthMatrix[i][j-1];
				directionalMatrix[i][j] = 'L';
			}
		}
	}
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			if(lengthMatrix[i][j] >= max) 
				max = lengthMatrix[i][j];
		}
	}
	result -> length = lengthMatrix;
	result -> direction = directionalMatrix;
	result -> lcsLength = max;
	return result;
}

void printLCS(char** dMatrix, char* str, int i, int j) {
	if(i == 0 || j == 0) {
		printf("\n");
		return;
	}
	if(dMatrix[i][j] == 'D') {
		printLCS(dMatrix, str, i-1, j-1);
		printf("%c", str[i]);
	}
	else if(dMatrix[i][j] == 'U') {
		printLCS(dMatrix, str, i-1, j);
	}
	else {
		printLCS(dMatrix, str, i, j-1);
	}
}