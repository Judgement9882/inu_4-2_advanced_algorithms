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
	return sum / (NUM_PTS - NUM_CLUSTER);
}

int main() {

	initPoints();

	for (int i = 0; i < NUM_CLUSTER; i++) {
		cluster[i] = -1;
	}

	// points[34]�� ù ��° Ŭ������ �׷����� ���� (�ƹ��ų�)
	cluster[clusterIdx] = 34;
	clusterIdx++;

	while (clusterIdx < NUM_CLUSTER) {
		// �� �� ���� �� ������ Ŭ������ �������� �Ÿ��� ��� �ʱ�ȭ
		for (int i = 0; i < NUM_PTS; i++) {
			distanceToClusterHead[i] = INT_MAX;
		}
		measureMinimumDistanceToClusterHead(); // �ּ� �Ÿ��� �����ϴ� �Լ�
		int c = findNewClusterHead(); // �ּҰŸ��� �ִ밪�� ���� ���� ����
		cluster[clusterIdx] = c; // Ŭ������ ���� ����
		clusterIdx++; // �ε��� ����
	}

	// printf("%f", avgDistanceOfClusters());

	return 0;
}