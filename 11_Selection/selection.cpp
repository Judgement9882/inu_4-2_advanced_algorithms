#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> num = { 56, 32, 33, 4, 9, 10, 98, 83, 22, 68 };
int orderToFind = 5; // 5번째 숫자를 찾고싶음

void selection(int _pivot, int _left, int _right, int _which) {
	int left = _left;
	int right = _right;

	// 탈출조건
	if (right < left) {
		cout << "Found " << orderToFind << "The number is " << num[_which] << "\n";
		return;
	}

	while (1) {
		// pivot 보다 작은 left 요소는 넘어감
		while (num[_pivot] > num[left]) {
			left++;
		}
		// pivot 보다 큰 rigth 요소는 자리이동x
		while (num[_pivot] < num[right]) {
			right--;
		}

		// 작은것들은 왼쪽으로, 큰 것은 오른쪽으로
		if (left < right) {
			swap(num[left], num[right]);
		}

		else {
			if (right == _which) {
				cout << "Found " << orderToFind << "The number is " << num[_which] << "\n";
				return;
			}

			else {
				swap(num[_pivot], num[right]);

				if (right > _which) {
					selection(_pivot, _left, right - 1, _which);
				}
				// 두번만에 분류가 되는 good division
				else { // right < _which
					selection(right + 1, right + 2, _right, _which);
				}
				return;
			}
		}
	}
}

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	int pivot = 0;
	// selection은 quicksort 함수를 변형시켜서 만듦. 재귀적으로.
	// pivot : pivot의 위치
	// 1 : left의 위치
	// num.size() - 1 : right의 위치
	// orderToFind-1 : K번째 숫자, 배열 기준 K-1
	selection(pivot, 1, num.size() - 1, orderToFind - 1);
	return 0;
}