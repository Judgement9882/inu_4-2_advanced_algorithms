/*
	quick sort와는 다르게(같은 공간에서 자리를 바꿈)
	merge sort는 합친 결과를 저장하기 위한
	별도의 공간이 필요함.

	ex) {1, 2, 3, 4}, {5, 6, 7, 8} 합치려면
	{x, x, x, x, o, o, o, o} 가 필요함.
	-> quick sort 대비 2배 공간 필요

	시간복잡도는 nlogn

	merge sort는 첫번째, 두번째를 정렬
	세번째 네번째를 정렬 한 후에 두개를 합치므로
	차례대로 접근해야함 -> 반으로 나누어가면서 접근
	
	MergeSort(A, p, q) p : 처음 q : 끝
	If (p<q){
		k = p+q/2 // 반으로 나누면서 접근
		MergeSort(A, p, k)
		MergeSort(A, k+1, q)
		A[p~k] 와 A[k+1~p]를 합한다는 의미.
		
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
		int i = p; // 앞 부분 가리키는 인덱스
		int j = m + 1; // 뒷 부분 가리키는 인덱스
		int g = p; // 합쳐지는 부분 가리킴

		while (1) {
			if (i <= m && j <= q) { // i와 j가 마지막까지 범위안에 있다면
				if (inputNum[i] < inputNum[j]) { // 앞부분이 더 작으면
					outputNum[g] = inputNum[i]; // 합쳐지는 부분에 작은수 대입
					g++; // 합쳐지는 부분 인덱스 증가
					i++; // 앞 부분 인덱스 증가
				}
				else { // 뒷부분이 더 작으면
					outputNum[g] = inputNum[j]; // 합쳐지는 부분에 뒷부분 추가
					g++; // 합쳐지는 부분 인덱스 증가
					j++; // 뒷부분 인덱스 증가
				}
			}

			else if (i <= m && j > q) { // 왼쪽은 범위내에 있다.
				outputNum[g] = inputNum[i]; // 합쳐지는 부분에 작은수 대입
				g++; // 합쳐지는 부분 인덱스 증가
				i++; // 앞 부분 인덱스 증가
			}
			else if (i > m && j <= q) { // 오른쪽은 범위내에 있다.
				outputNum[g] = inputNum[j]; // 합쳐지는 부분에 뒷부분 추가
				g++; // 합쳐지는 부분 인덱스 증가
				j++; // 뒷부분 인덱스 증가
			}
			else {// 바뀐 부분까지만 최신화
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

	mergeSort(0, 9); // mergesort 진행
	showOutputNum(); // 정렬 후에 결과를 보여주는 함수
	

	return 0;
}