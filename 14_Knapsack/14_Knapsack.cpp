#include <stdio.h>

#define NUM_OF_THING 3 // 물건 종류
#define MAX_WEIGHT 19 // 최대 배낭 무게

struct thing { // 구조체 생성
	int value;
	int weight;
};

typedef struct thing THING;

THING things[NUM_OF_THING] = { {1, 1}, {3, 2}, {5, 3} };

int m[MAX_WEIGHT + 1] = { 0 }; // m[0] ~ m[19]를 모두 0으로 초기화
int kind_of_thing[MAX_WEIGHT + 1][3] = { 0 };

int main() {

	for (int c = 1; c <= MAX_WEIGHT; c++) {
		int temp, prev;

		for (int idx = 0; idx < NUM_OF_THING; idx++) {
			if (c >= things[idx].weight) {
				if (m[c] < things[idx].value + m[c - things[idx].weight]) { // 이전 계산한 값보다 지금 계산한 값이 더 클 경우 최신화를 해줌.
					m[c] = things[idx].value + m[c - things[idx].weight];
					temp = idx;
					prev = c - things[idx].weight;
				}
			}
		}

		if (temp == 0) {
			kind_of_thing[c][0] = kind_of_thing[prev][0] + 1;
			kind_of_thing[c][1] = kind_of_thing[prev][1];
			kind_of_thing[c][2] = kind_of_thing[prev][2];
		}
		else if (temp == 1) {
			kind_of_thing[c][0] = kind_of_thing[prev][0];
			kind_of_thing[c][1] = kind_of_thing[prev][1] + 1;
			kind_of_thing[c][2] = kind_of_thing[prev][2];
		}
		else {
			kind_of_thing[c][0] = kind_of_thing[prev][0];
			kind_of_thing[c][1] = kind_of_thing[prev][1];
			kind_of_thing[c][2] = kind_of_thing[prev][2] + 1;
		}

		printf("The maximum value of m[%d] = %d\n", c, m[c]);
		printf("v1 : %d, v2 : %d, v3 : %d\n", kind_of_thing[c][0], kind_of_thing[c][1], kind_of_thing[c][2]);
		printf("---------------------\n");
	}

	return 0;
}