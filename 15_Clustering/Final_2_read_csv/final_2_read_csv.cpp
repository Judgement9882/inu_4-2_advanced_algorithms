#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_VALUE 1000 // x, y, z 축의 최대값
#define NUM_PTS 46562 // 데이터의 개수가 46562개
#define NUM_CLUSTER 4 // n개의 그룹으로 나누기

struct point { // 좌표
	int x;
	int y;
	int z;
};

struct point points[NUM_PTS]; // 구조체 배열 생성
int cluster[NUM_CLUSTER] = { -1 }; // cluster 배열 : 클러스터의 대표가 되는 점들의 고유 번호를 저장.
int distanceToClusterHead[NUM_PTS] = { INT_MAX }; // 각각의 점에서 클러스터 대표 점까지 거리를 나타냄.
int clusterIdx = 0; // 몇개의 그룹의 대표가 결정됐는지 추적하기위한 변수


// 랜덤하게 점 만들기
//void initPoints() {
//	srand(345);
//
//	for (int i = 0; i < NUM_PTS; i++) {
//		points[i].x = rand() % MAX_VALUE;
//		points[i].y = rand() % MAX_VALUE;
//		/*printf("%d, %d\n", points[i].x, points[i].y);
//		printf("=-=======\n");*/
//	}
//}

// 직선 거리 계산 (거리의 제곱)
int calcDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
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
				int dist = calcDistance(points[i].x, points[i].y, points[i].z, points[cluster[j]].x, points[cluster[j]].y, points[cluster[j]].z);

				// 거리가 더 짧으면 업데이트. (최소거리만 저장)
				if (dist < distanceToClusterHead[i]) {
					distanceToClusterHead[i] = dist;
				}
			}
		}
	}
}

// 최소 거리중 가장 큰 값을 가진 것 찾기
//int findNewClusterHead() {
//	int maximum = 0;
//	int maxIdx = -1;
//	for (int i = 0; i < NUM_PTS; i++) {
//		if (isClusterHead(i) == 0) { // cluster head가 아닐 경우에만 실행
//			if (distanceToClusterHead[i] > maximum) { // 가장 최대 거리인 것을 뽑아서
//				maximum = distanceToClusterHead[i];
//				maxIdx = i; // 인덱스 저장
//			}
//		}
//	}
//	return maxIdx;
//}

// points[idx]가 속하는 cluster 번호를 반환
// 어떤 클러스터에 속하는지 알려줌 ( 가장 가까운 클러스터 헤드 )

int findClosestCluster(int idx) {
	int clusterDist = INT_MAX;
	int clusterIdx = -1;

	for (int i = 0; i < NUM_CLUSTER; i++) { // 모든 클러스터에 대한 거리를 구해서 최소값을 취함
		int dist = calcDistance(points[idx].x, points[idx].y, points[idx].z, points[cluster[i]].x, points[cluster[i]].y, points[cluster[i]].z);
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
			sum += calcDistance(points[i].x, points[i].y, points[i].z, points[cluster[c]].x, points[cluster[c]].y, points[cluster[c]].z);
		}
	}
	return sum / (NUM_PTS - NUM_CLUSTER);
}


void retAveragePoint(int c) {
	int sum_x = 0;
	int sum_y = 0;
	int sum_z = 0;
	int cnt = 0;
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) {
			int clus_num = findClosestCluster(i);
			if (clus_num == c) {
				cnt++;
				sum_x += points[i].x;
				sum_y += points[i].y;
				sum_z += points[i].z;
			}
		}
	}
	if (cnt == 0) {
		printf("there isn't any cluster\n");
		return;
	}

	points[cluster[c]].x = sum_x / cnt;
	points[cluster[c]].y = sum_y / cnt;
	points[cluster[c]].z = sum_z / cnt;
	printf("%d번째 클러스터 x : %d , y : %d, z : %d\n", c, points[cluster[c]].x, points[cluster[c]].y, points[cluster[c]].z);
}

int main() {

	// initPoints();
	char str_temp[1024];
	char* p;
	int line = 0;

	FILE* csvFile = NULL;
	// fopen_s(&csvFile, "problem.csv", "r");
	csvFile = fopen("problem.csv", "r");
	if (csvFile != NULL) {
		while (!feof(csvFile)) {
			fgets(str_temp, 1024, csvFile); // buffer, size, file
			
			p = strtok(str_temp, ",");
			while (p != NULL) {
				points[line].x = atoi(p);
				p = strtok(NULL, ",");
				
				if (p == NULL) break;
				points[line].y = atoi(p);
				p = strtok(NULL, ",");
				
				if (p == NULL) break;
				points[line].z = atoi(p);
				p = strtok(NULL, ",");

				line++;
			}
			
		}
	}
	fclose(csvFile);
	
	/*for (int i = 0; i < NUM_PTS; i++) {
		printf("x : %d, y : %d, z : %d\n", points[i].x, points[i].y, points[i].z);
	}*/

	for (int i = 0; i < NUM_CLUSTER; i++) {
		cluster[i] = -1;
	}
	
	// k-mean clustering 시작 - 아무 점이나 클러스터 헤드로 만들기
	for (int i = 0; i < NUM_CLUSTER; i++) {
		cluster[i] = rand() % NUM_PTS;
		clusterIdx++;
	}
	
	int cnt = 0;
	while (cnt++ < 50) {
		printf("%d번째 실행 ========================\n", cnt);
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

	printf("Average distance of clusters : %f", avgDistanceOfClusters());
	return 0;
}