#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

typedef struct {
	int** length;
	char** direction;
	int lcsLength;
} LCS, *LCS_PTR;

LCS_PTR findLCSLength(char* m, char* n, int x, int y);
void printLCS(char** dMatrix, char* str, int i, int j, int index);
void findAllLCS(int** lMatrix, char* str1, char* str2, int x, int y, string lcsSoFar, set<string>* mySet); 
void printLengthMatrix(int** c, char *string1, char *string2, int string1Size, int string2Size);
void printDirectionMatrix(char** c, char *string1, char *string2, int string1Size, int string2Size);

int main(int argc, char** argv)
{
	int n, k, x, y, i = 0;
	string line;
	char *token, *tempStr;
	char* strArr[2], *str1, *str2;
	LCS_PTR lcsResult = new LCS;

	// Runs in the case that user wants LCS length and singular printed LCS.
	while (getline(cin, line))
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
			while (token != NULL) {
				strArr[k++] = token;
				token = strtok(NULL, " ");
			}
			str1 = strArr[0], str2 = strArr[1];
			x = strlen(str1), y = strlen(str2);
			lcsResult = findLCSLength(str1, str2, x, y);
			if(argc == 2 && strcmp(argv[1], "-all") == 0) {
				string lcsSoFar("");
				set<string>* mySet = new set<string>();
				findAllLCS(lcsResult -> length, str1, str2, x, y, lcsSoFar, mySet);
				set<string>::iterator it;
				for (it = mySet -> begin(); it != mySet -> end(); ++it) {
					cout << *it;
				}
				cout << endl;
			}
			else {
				printf("%d ", lcsResult->lcsLength);
				printLCS(lcsResult -> direction, str1, x, y, (lcsResult -> lcsLength));
			}
		}
	}

	// Frees space allocated by program to prevent memory leaks and, finally, returns 0.
	for (int i = 0; i < x; i++) {
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
	int** lengthMatrix = new int*[x + 1];
	char** directionalMatrix = new char*[x + 1];
	for (int i = 0; i <= x; i++) {
		lengthMatrix[i] = new int[y + 1];
		directionalMatrix[i] = new char[y + 1];
	}
	for (int i = 0; i <= x; i++) {
		lengthMatrix[i][0] = 0;
	}
	for (int j = 0; j <= y; j++) {
		lengthMatrix[0][j] = 0;
	}
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			if (m[i - 1] == n[j - 1]) {
				lengthMatrix[i][j] = lengthMatrix[i - 1][j - 1] + 1;
				directionalMatrix[i][j] = 'D';
			}
			else if (lengthMatrix[i - 1][j] > lengthMatrix[i][j - 1]) {
				lengthMatrix[i][j] = lengthMatrix[i - 1][j];
				directionalMatrix[i][j] = 'U';
			}
			else {
				lengthMatrix[i][j] = lengthMatrix[i][j - 1];
				directionalMatrix[i][j] = 'L';
			}
		}
	}
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			if (lengthMatrix[i][j] > max)
				max = lengthMatrix[i][j];
		}
	}
	result -> length = lengthMatrix;
	result -> direction = directionalMatrix;
	result -> lcsLength = max;
	return result;
}

void printLCS(char** dMatrix, char* str, int i, int j, int index) {
	char lcs[index + 1];
	lcs[index] = '\0';
	while (i > 0 && j > 0)
	{
		if (dMatrix[i][j] == 'D')
		{
			lcs[index - 1] = str[i - 1];
			i--;
			j--;
			index--;
		}
		else if (dMatrix[i][j] == 'U')
			i--;
		else
			j--;
	}
	printf("%s\n", lcs);
}

void findAllLCS(int** lMatrix, char* str1, char* str2, int i, int j, string lcsSoFar, set<string>* mySet) 
{
	if(lMatrix[i][j] == 0) {
		stringstream ss;
		ss << "(" << lcsSoFar << ")\n";
		mySet -> insert(ss.str());
		return;
	}
	if(str1[i-1] == str2[j-1])
	{
		stringstream ss;			
		if (lMatrix[i][j] > 1) {
			ss << ", <" << i << ", " << j << ">" << lcsSoFar;
		}
		else {
			ss << "<" << i << ", " << j << ">" << lcsSoFar;
		}
		findAllLCS(lMatrix, str1, str2, i-1, j-1, ss.str(), mySet);
	}
	if(lMatrix[i][j-1] == lMatrix[i][j]) {
		findAllLCS(lMatrix, str1, str2, i, j-1, lcsSoFar, mySet);
	}
	if(lMatrix[i-1][j] == lMatrix[i][j]) {
		findAllLCS(lMatrix, str1, str2, i-1, j, lcsSoFar, mySet);
	}
}

/* Functions for printing the cost and direction matrices (for convenience of finding LCS all algorithm).
void printLengthMatrix(int** c, char *string1, char *string2, int string1Size, int string2Size) {
	printf("   ");
	for(int i=1; i<= string2Size; i++){
		printf("  %c", string2[i-1]);
	}
	printf("\n");
	for(int i=0; i <= string1Size; i++){
		if(i == 0){
			printf(" ");
		}else{
			printf("%c", string1[i-1]);
		}
		for(int j=0; j<= string2Size; j++){
			printf("|%d|", c[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}

void printDirectionMatrix(char** c, char *string1, char *string2, int string1Size, int string2Size){
	printf("   ");
	for(int i=1; i<= string2Size; i++){
		printf("  %c", string2[i-1]);
	}
	printf("\n");
	for(int i=0; i <= string1Size; i++){
		if(i == 0){
			printf(" ");
		}else{
			printf("%c", string1[i-1]);
		}
		for(int j=0; j<= string2Size; j++){
			if (c[i][j] != '\0')
				printf("|%c|", c[i][j]);
			else
				printf("|x|");
		}
		printf("\n");
	}
	printf("\n-------------------------------------\n");
	return;
}
*/
