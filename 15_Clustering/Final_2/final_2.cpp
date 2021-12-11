#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 600 // x, y 축의 최대값
#define NUM_PTS 100 // 데이터의 개수가 100개
#define NUM_CLUSTER 6 // 6개의 그룹으로 나누기

struct point { // 좌표
	int x;
	int y;
};

struct point points[NUM_PTS]; // 구조체 배열 생성

int cluster[NUM_CLUSTER] = { -1 }; // cluster 배열 : 클러스터의 대표가 되는 점들의 고유 번호를 저장.

int distanceToClusterHead[NUM_PTS] = { INT_MAX }; // 각각의 점에서 클러스터 대표 점까지 거리를 나타냄.
int clusterIdx = 0; // 몇개의 그룹의 대표가 결정됐는지 추적하기위한 변수


// 랜덤하게 점 만들기
void initPoints() {
	srand(345);

	for (int i = 0; i < NUM_PTS; i++) {
		points[i].x = rand() % MAX_VALUE;
		points[i].y = rand() % MAX_VALUE;
		/*printf("%d, %d\n", points[i].x, points[i].y);
		printf("=-=======\n");*/
	}
}

// 직선 거리 계산 (거리의 제곱)
int calcDistance(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

// points[idx] 가 cluster head면 1 반환. 아니면 0 변환
int isClusterHead(int idx) {
	for (int i = 0; i < NUM_CLUSTER; i++) {
		if (cluster[i] == -1) {
			break;
		}
		if (cluster[i] == idx) {
			return 1;
		}
	}
	return 0;
}

// 각 점에 대해 cluster head들에 대한 거리 중 최소 거리 구하기
void measureMinimumDistanceToClusterHead() {
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) { // cluster head가 아닐경우에만 진행
			for (int j = 0; j < NUM_CLUSTER; j++) {

				if (cluster[j] == -1) { // 아직 정의가 안됐으면 break
					break;
				}
				// 자기자신과 클러스터 헤드와의 거리를 다 계산.
				int dist = calcDistance(points[i].x, points[i].y, points[cluster[j]].x, points[cluster[j]].y);

				// 거리가 더 짧으면 업데이트. (최소거리만 저장)
				if (dist < distanceToClusterHead[i]) {
					distanceToClusterHead[i] = dist;
				}
			}
		}
	}
}

// 최소 거리중 가장 큰 값을 가진 것 찾기
int findNewClusterHead() {
	int maximum = 0;
	int maxIdx = -1;
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) { // cluster head가 아닐 경우에만 실행
			if (distanceToClusterHead[i] > maximum) { // 가장 최대 거리인 것을 뽑아서
				maximum = distanceToClusterHead[i];
				maxIdx = i; // 인덱스 저장
			}
		}
	}
	return maxIdx;
}

// points[idx]가 속하는 cluster 번호를 반환
// 어떤 클러스터에 속하는지 알려줌 ( 가장 가까운 클러스터 헤드 )

int findClosestCluster(int idx) {
	int clusterDist = INT_MAX;
	int clusterIdx = -1;

	for (int i = 0; i < NUM_CLUSTER; i++) { // 모든 클러스터에 대한 거리를 구해서 최소값을 취함
		int dist = calcDistance(points[idx].x, points[idx].y, points[cluster[i]].x, points[cluster[i]].y);
		if (dist < clusterDist) {
			clusterDist = dist;
			clusterIdx = i;
		}
	}
	return clusterIdx;
}

// 각 점과 소속 cluster head간의 거리의 평균값 : 낙폭 분석

double avgDistanceOfClusters() {
	double sum = 0.0;
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) {
			int c = findClosestCluster(i);
			sum += calcDistance(points[i].x, points[i].y, points[cluster[c]].x, points[cluster[c]].y);
		}
	}
	return sum / 100-6;
}


//auto retAveragePoint(int c) {
//	int sum_x = 0;
//	int sum_y = 0;
//	int cnt = 0;
//	for (int i = 0; i < NUM_PTS; i++){
//		if (isClusterHead(i) == 0) {
//			int clus_num = findClosestCluster(i);
//			if (clus_num == c) {
//				cnt++;
//				sum_x += points[i].x;
//				sum_y += points[i].y;
//			}
//		}
//	}
//	if (cnt == 0) return 0, 0;
//
//	printf("sum_x : %d, cnt : %d, sum/cnt = %d\n==============\n", sum_x, cnt, sum_x / cnt);
//	return sum_x / cnt, sum_y / cnt;
//}

void retAveragePoint(int c) {
	int sum_x = 0;
	int sum_y = 0;
	int cnt = 0;
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) {
			int clus_num = findClosestCluster(i);
			if (clus_num == c) {
				cnt++;
				sum_x += points[i].x;
				sum_y += points[i].y;
			}
		}
	}
	if (cnt == 0) return;

	points[cluster[c]].x = sum_x/cnt;
	points[cluster[c]].y = sum_y/cnt;	
}


int main() {

	initPoints();
	int a = 0;
	int b = 0;
	for (int i = 0; i < NUM_CLUSTER; i++) {
		cluster[i] = -1;
	}

	// k-mean clustering : 아무 점이나 클러스터 헤드로 만들기
	for (int i = 0; i < NUM_CLUSTER; i++) {
		cluster[clusterIdx] = NUM_CLUSTER * (i+1);
		clusterIdx++;
	}

	int cnt = 0;
	while (cnt++ < 100) {

		// 할 때 마다 각 점들의 클러스터 헤드까지의 거리를 계속 초기화
		for (int i = 0; i < NUM_PTS; i++) {
			distanceToClusterHead[i] = INT_MAX;
		}

		measureMinimumDistanceToClusterHead(); // 최소 거리만 정의하는 함수

		for (int j = 0; j < NUM_CLUSTER; j++) {
			retAveragePoint(j);
		}

		
		//int c = findNewClusterHead(); // 최소거리중 최대값을 갖는 것을 선택
		//cluster[clusterIdx] = c; // 클러스터 헤드로 저장
		//clusterIdx++; // 인덱스 증가
	}

	printf("%f", avgDistanceOfClusters());

	return 0;
}