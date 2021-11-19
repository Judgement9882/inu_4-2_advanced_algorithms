/*
	quick sort�ʹ� �ٸ���(���� �������� �ڸ��� �ٲ�)
	merge sort�� ��ģ ����� �����ϱ� ����
	������ ������ �ʿ���.

	ex) {1, 2, 3, 4}, {5, 6, 7, 8} ��ġ����
	{x, x, x, x, o, o, o, o} �� �ʿ���.
	-> quick sort ��� 2�� ���� �ʿ�

	�ð����⵵�� nlogn

	merge sort�� ù��°, �ι�°�� ����
	����° �׹�°�� ���� �� �Ŀ� �ΰ��� ��ġ�Ƿ�
	���ʴ�� �����ؾ��� -> ������ ������鼭 ����
	
	MergeSort(A, p, q) p : ó�� q : ��
	If (p<q){
		k = p+q/2 // ������ �����鼭 ����
		MergeSort(A, p, k)
		MergeSort(A, k+1, q)
		A[p~k] �� A[k+1~p]�� ���Ѵٴ� �ǹ�.
		
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> inputNum = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
vector<int> outputNum = inputNum;

void mergeSort(int p, int q) {
	if (p < q) {
		int m = (p + q) / 2;
		mergeSort(p, m);
		mergeSort(m + 1, q);

		// merging two parts
		int i = p; // �� �κ� ����Ű�� �ε���
		int j = m + 1; // �� �κ� ����Ű�� �ε���
		int g = p; // �������� �κ� ����Ŵ

		while (1) {
			if (i <= m && j <= q) { // i�� j�� ���������� �����ȿ� �ִٸ�
				if (inputNum[i] < inputNum[j]) { // �պκ��� �� ������
					outputNum[g] = inputNum[i]; // �������� �κп� ������ ����
					g++; // �������� �κ� �ε��� ����
					i++; // �� �κ� �ε��� ����
				}
				else { // �޺κ��� �� ������
					outputNum[g] = inputNum[j]; // �������� �κп� �޺κ� �߰�
					g++; // �������� �κ� �ε��� ����
					j++; // �޺κ� �ε��� ����
				}
			}

			else if (i <= m && j > q) { // ������ �������� �ִ�.
				outputNum[g] = inputNum[i]; // �������� �κп� ������ ����
				g++; // �������� �κ� �ε��� ����
				i++; // �� �κ� �ε��� ����
			}
			else if (i > m && j <= q) { // �������� �������� �ִ�.
				outputNum[g] = inputNum[j]; // �������� �κп� �޺κ� �߰�
				g++; // �������� �κ� �ε��� ����
				j++; // �޺κ� �ε��� ����
			}
			else {// �ٲ� �κб����� �ֽ�ȭ
				for (int i = p; i <= q; i++) {
					inputNum[i] = outputNum[i];
				}
				return;
			}
		}
	}
}

void showOutputNum() {
	for (int i = 0; i < 10; i++) {
		cout << outputNum[i] << ", ";
	}
	cout << "\n";
}

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	mergeSort(0, 9); // mergesort ����
	showOutputNum(); // ���� �Ŀ� ����� �����ִ� �Լ�
	

	return 0;
}