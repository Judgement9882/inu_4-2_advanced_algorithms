#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 600 // x, y ���� �ִ밪
#define NUM_PTS 100 // �������� ������ 100��
#define NUM_CLUSTER 6 // 6���� �׷����� ������

struct point { // ��ǥ
	int x;
	int y;
};

struct point points[NUM_PTS]; // ����ü �迭 ����

int cluster[NUM_CLUSTER] = { -1 }; // cluster �迭 : Ŭ�������� ��ǥ�� �Ǵ� ������ ���� ��ȣ�� ����.

int distanceToClusterHead[NUM_PTS] = { INT_MAX }; // ������ ������ Ŭ������ ��ǥ ������ �Ÿ��� ��Ÿ��.
int clusterIdx = 0; // ��� �׷��� ��ǥ�� �����ƴ��� �����ϱ����� ����


// �����ϰ� �� �����
void initPoints() {
	srand(345);

	for (int i = 0; i < NUM_PTS; i++) {
		points[i].x = rand() % MAX_VALUE;
		points[i].y = rand() % MAX_VALUE;
		/*printf("%d, %d\n", points[i].x, points[i].y);
		printf("=-=======\n");*/
	}
}

// ���� �Ÿ� ��� (�Ÿ��� ����)
int calcDistance(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

// points[idx] �� cluster head�� 1 ��ȯ. �ƴϸ� 0 ��ȯ
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

// �� ���� ���� cluster head�鿡 ���� �Ÿ� �� �ּ� �Ÿ� ���ϱ�
void measureMinimumDistanceToClusterHead() {
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) { // cluster head�� �ƴҰ�쿡�� ����
			for (int j = 0; j < NUM_CLUSTER; j++) {

				if (cluster[j] == -1) { // ���� ���ǰ� �ȵ����� break
					break;
				}
				// �ڱ��ڽŰ� Ŭ������ ������ �Ÿ��� �� ���.
				int dist = calcDistance(points[i].x, points[i].y, points[cluster[j]].x, points[cluster[j]].y);

				// �Ÿ��� �� ª���� ������Ʈ. (�ּҰŸ��� ����)
				if (dist < distanceToClusterHead[i]) {
					distanceToClusterHead[i] = dist;
				}
			}
		}
	}
}

// �ּ� �Ÿ��� ���� ū ���� ���� �� ã��
int findNewClusterHead() {
	int maximum = 0;
	int maxIdx = -1;
	for (int i = 0; i < NUM_PTS; i++) {
		if (isClusterHead(i) == 0) { // cluster head�� �ƴ� ��쿡�� ����
			if (distanceToClusterHead[i] > maximum) { // ���� �ִ� �Ÿ��� ���� �̾Ƽ�
				maximum = distanceToClusterHead[i];
				maxIdx = i; // �ε��� ����
			}
		}
	}
	return maxIdx;
}

// points[idx]�� ���ϴ� cluster ��ȣ�� ��ȯ
// � Ŭ�����Ϳ� ���ϴ��� �˷��� ( ���� ����� Ŭ������ ��� )

int findClosestCluster(int idx) {
	int clusterDist = INT_MAX;
	int clusterIdx = -1;

	for (int i = 0; i < NUM_CLUSTER; i++) { // ��� Ŭ�����Ϳ� ���� �Ÿ��� ���ؼ� �ּҰ��� ����
		int dist = calcDistance(points[idx].x, points[idx].y, points[cluster[i]].x, points[cluster[i]].y);
		if (dist < clusterDist) {
			clusterDist = dist;
			clusterIdx = i;
		}
	}
	return clusterIdx;
}

// �� ���� �Ҽ� cluster head���� �Ÿ��� ��հ� : ���� �м�

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

	// k-mean clustering : �ƹ� ���̳� Ŭ������ ���� �����
	for (int i = 0; i < NUM_CLUSTER; i++) {
		cluster[clusterIdx] = NUM_CLUSTER * (i+1);
		clusterIdx++;
	}

	int cnt = 0;
	while (cnt++ < 100) {

		// �� �� ���� �� ������ Ŭ������ �������� �Ÿ��� ��� �ʱ�ȭ
		for (int i = 0; i < NUM_PTS; i++) {
			distanceToClusterHead[i] = INT_MAX;
		}

		measureMinimumDistanceToClusterHead(); // �ּ� �Ÿ��� �����ϴ� �Լ�

		for (int j = 0; j < NUM_CLUSTER; j++) {
			retAveragePoint(j);
		}

		
		//int c = findNewClusterHead(); // �ּҰŸ��� �ִ밪�� ���� ���� ����
		//cluster[clusterIdx] = c; // Ŭ������ ���� ����
		//clusterIdx++; // �ε��� ����
	}

	printf("%f", avgDistanceOfClusters());

	return 0;
}