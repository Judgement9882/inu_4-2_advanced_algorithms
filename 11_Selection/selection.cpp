#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> num = { 56, 32, 33, 4, 9, 10, 98, 83, 22, 68 };
int orderToFind = 5; // 5��° ���ڸ� ã�����

void selection(int _pivot, int _left, int _right, int _which) {
	int left = _left;
	int right = _right;

	// Ż������
	if (right < left) {
		cout << "Found " << orderToFind << "The number is " << num[_which] << "\n";
		return;
	}

	while (1) {
		// pivot ���� ���� left ��Ҵ� �Ѿ
		while (num[_pivot] > num[left]) {
			left++;
		}
		// pivot ���� ū rigth ��Ҵ� �ڸ��̵�x
		while (num[_pivot] < num[right]) {
			right--;
		}

		// �����͵��� ��������, ū ���� ����������
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
				// �ι����� �з��� �Ǵ� good division
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
	// selection�� quicksort �Լ��� �������Ѽ� ����. ���������.
	// pivot : pivot�� ��ġ
	// 1 : left�� ��ġ
	// num.size() - 1 : right�� ��ġ
	// orderToFind-1 : K��° ����, �迭 ���� K-1
	selection(pivot, 1, num.size() - 1, orderToFind - 1);
	return 0;
}