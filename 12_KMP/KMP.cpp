#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
	인수 : 패턴 문자열
	반환 : lps 배열
*/

auto calculate_lps(string pattern_str) {
	// 문자열을 받아 첫 문자를 배열로 반환
	int pattern_len = pattern_str.length();
	vector<int> lps(pattern_len); // lps vector
	
	// LPS 배열 계산
	int j = 0;
	for (int i = 1; i < pattern_len; i++) {

		// 3. j가 0보다 크고(중간부분임) 같지 않다면 j 위치를 옮김.
		// i값은 변하지않음. 
		// 수행했는데도 또 안되면 또 실행 -> while문으로 작동
		while (j > 0 && pattern_str[i] != pattern_str[j]) {
			j = lps[j - 1];
		}

		// 1. i번째와 j번째가 같다면
		if (pattern_str[i] == pattern_str[j]) {
			j++;
			lps[i] = j;
		}

		// 2. i번째와 j번째가 다르다면 i번째의 index를 바꿔줘야함.
		// but for loop 에 의해 i가 자동으로 증가되기 때문에
		// 바꿀 필요가 없음.

	}
	return lps;
}



int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	// target string
	// string target_str = "ABABABABBABABABABC";
	string target_str = "ABABABABBABABABABCABABABABC";

	// pattern string
	string pattern_str = "ABABABABC";

	int target_len = target_str.length();
	int pattern_len = pattern_str.length();
	
	vector<int> lps = calculate_lps(pattern_str);

	for (int i = 0; i < pattern_len; i++) {
		cout << i << "---->" << lps[i] << "\n";
	}

	// --- string matching
	cout << "------------- start string matching " << pattern_str << " to " << target_str << "\n";
	
	// i : target_str 의 현재 위치 인덱스
	// j : pattern_str 의 현재 위치 인덱스

	int j = 0;
	for (int i = 0; i < target_len; i++) {

		// 중간에 맞지 않을 경우
		while (j > 0 && target_str[i] != pattern_str[j]) {
			j = lps[j - 1];
		}

		if (target_str[i] == pattern_str[j]) {
			// 만약 전부 맞을경우

			// 끝까지 왔을경우
			if (j == (pattern_len - 1)) {
				cout << "Found matching at " << i - pattern_len + 1 << "\n";
				// 다 맞았으면 j값을 업데이트하고 처음부터 비교
				j = lps[j]; // lps안에 들어있는 위치로 가서 비교
			}
			else { // 그렇지 않을경우 한칸씩 이동하면서.
				j++;
			}
		}
	}

	cout << "KMP complete";
	return 0;
}