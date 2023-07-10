#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

// REQUIRES: vector A
// EFFECTS: do the square sort asked by the question
// TODO: finish this function
vector<int> square_sort(vector<int> &A)
{	
	vector<int> result;
	result.emplace_back(0);
	int zeroPos = 0;
	while (A[zeroPos] != 0) {
		zeroPos++;
	}
	int left = zeroPos - 1;
	unsigned right = zeroPos + 1;
	while (left >= 0 && right <= size(A) - 1) {
		if (A[left] * (-1) >= A[right]) {
			result.emplace_back(A[right]*A[right]);
			right++;
		}
		else {
			result.emplace_back(A[left]*A[left]);
			left--;
		}
	}
	while (left >= 0) {
        result.emplace_back(A[left]*A[left]);
		left--;
    }
    while (right <= size(A) - 1) {
        result.emplace_back(A[right]*A[right]);
		right++;
    }
	return result;
}

// MAIN
// NOTE: DO NOT MODIFY THIS PART
int main()
{
	vector<int> A;
	string s;
	getline(cin, s);

	stringstream ss(s);
	int temp;
	while (ss >> temp)
		A.emplace_back(temp);

	for (auto item : square_sort(A))
		cout << item << " ";
	cout << "\n";
	return 0;
}
