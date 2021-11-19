#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
	�μ� : ���� ���ڿ�
	��ȯ : lps �迭
*/

auto calculate_lps(string pattern_str) {
	// ���ڿ��� �޾� ù ���ڸ� �迭�� ��ȯ
	int pattern_len = pattern_str.length();
	vector<int> lps(pattern_len); // lps vector
	
	// LPS �迭 ���
	int j = 0;
	for (int i = 1; i < pattern_len; i++) {

		// 3. j�� 0���� ũ��(�߰��κ���) ���� �ʴٸ� j ��ġ�� �ű�.
		// i���� ����������. 
		// �����ߴµ��� �� �ȵǸ� �� ���� -> while������ �۵�
		while (j > 0 && pattern_str[i] != pattern_str[j]) {
			j = lps[j - 1];
		}

		// 1. i��°�� j��°�� ���ٸ�
		if (pattern_str[i] == pattern_str[j]) {
			j++;
			lps[i] = j;
		}

		// 2. i��°�� j��°�� �ٸ��ٸ� i��°�� index�� �ٲ������.
		// but for loop �� ���� i�� �ڵ����� �����Ǳ� ������
		// �ٲ� �ʿ䰡 ����.

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
	
	// i : target_str �� ���� ��ġ �ε���
	// j : pattern_str �� ���� ��ġ �ε���

	int j = 0;
	for (int i = 0; i < target_len; i++) {

		// �߰��� ���� ���� ���
		while (j > 0 && target_str[i] != pattern_str[j]) {
			j = lps[j - 1];
		}

		if (target_str[i] == pattern_str[j]) {
			// ���� ���� �������

			// ������ �������
			if (j == (pattern_len - 1)) {
				cout << "Found matching at " << i - pattern_len + 1 << "\n";
				// �� �¾����� j���� ������Ʈ�ϰ� ó������ ��
				j = lps[j]; // lps�ȿ� ����ִ� ��ġ�� ���� ��
			}
			else { // �׷��� ������� ��ĭ�� �̵��ϸ鼭.
				j++;
			}
		}
	}

	cout << "KMP complete";
	return 0;
}