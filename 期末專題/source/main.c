#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int map[100][100];
int row, column;//��A�C
int count = 0;//�����`�I�Ӽ�
int i, j;
int startPoint, endPoint;
int path[100], visited[100] = { 0 };
int pathNumber = 0;

//
//��l�Ƴs�u�x�} (�e��)
// 
void createGraphics()
{
	int tmp[4][2] = { {0,1},{1,0},{-1,0},{0,-1} }; //�W �k �� �U
	memset(map, 0, sizeof(map));//��Ϫ�l�Ƭ�0
	for (i = 0; i < row*column; i++)
	{
		//�����I�W�U���k4���I��lmap 
		int r = i / column;//X�b�y��
		int c = i % column;//Y�b�y��
		for (j = 0; j < 4; j++)//�C���I�̦h��4�Ӹ��|
		{
			//�]r,c)�۾F���I���]r1,c1) 
			int r1 = r + tmp[j][0];
			int c1 = c + tmp[j][1];	//�������|
			if (r1 >= 0 && r1 < row&&c1 >= 0 && c1 < column)//����Ϫ��j�p
			{
				map[i][r1*column + c1] = 1;//��|�Ψ쪺���|�]��1
			}
		}
	}
}


//
//��^��n�Ӹ`�I�۳s�u�Ǹ��̤p���`�I 
//
int first(int n)
{
	for (i = 0; i < row*column; i++)
	{
		if (map[n][i] == 1)
			return i;
	}
	printf("�_�I���G���I�A�п�J�@�Ӥ����G���I���_�I\n");
	return 0;
}


//
//��^��n�Ӹ`�I�۾F���I���Ӽ�
// 
int sumCount(int n)
{
	
	for (i = 0; i < row*column; i++)
	{
		if (map[n][i] == 1)
			count++;
	}
	return count;
}


//
//��^��n�Ӹ`�I�۳s����now�`�I�Ǹ��j���`�I,
//
int next(int n, int now)
{
	for (i = now + 1; i < row*column; i++)
	{
		if (map[n][i] == 1)
			return i;
	}
	return 1000;  //��䤣��`�In���U�@�Ӹ`�I�A��^1000
}


//
//DFS�M��Ҧ����| 
//
void DFS(int nowPoint, int count)
{
	char direction;
	visited[nowPoint] = 1;
	path[count++] = nowPoint; //�x�s���T���|
	if (startPoint > endPoint) {
		direction = 'L'; //�p�G���I�Ʀr�j��_�I�Ʀr�u�੹���U��
	}else if (startPoint < endPoint) {
		direction = 'R'; //�p�G�_�I�Ʀr�j����I�Ʀr�u�੹�k�W��
	}
	if (nowPoint == endPoint && (count) >= 1)
	{
		int select = 0;

		if (direction == 'R') {
			for (i = 0; i < (count)-1; i++) {
				if (path[i] > path[i + 1])
					select = 1;		
			} //�P�_���k�W�������|�O�_���T
		}else if (direction == 'L') {
			for (i = 0; i < (count)-1; i++) {
				if (path[i] < path[i + 1])
					select = 1;		
			} //�P�_�����U�������|�O�_���T
		} //���Tselect=0

		if (select == 0) {
			pathNumber++;
			printf("�o��ӫ�������%d��²����|��: ", pathNumber);

			for (i = 0; i < (count)-1; i++)
			{
				printf("%d-->", path[i] + 1);
			}
			printf("%d\n", path[(count)-1] + 1);
			select = 0;
		}
	}
	else
	{
		int k;
		for (k = first(nowPoint); k < row*column; k = next(nowPoint, k))
		{
			if (visited[k] == 0)
				DFS(k, count);
		}
	}
	visited[nowPoint] = 0;  //�N���L�����|�]��0 
	(count)--;
	return;
}


int main()
{
	int count = 0, pathNumber = 0;
	printf("�п�J�n�ͦ��Ϫ���M�C�G\n");
	scanf("%d%d", &row, &column);
	createGraphics();
	printf("�п�J�n�����|���_�I�M���I:\n");
	scanf("%d%d", &startPoint, &endPoint);
	if (startPoint != endPoint) {
		startPoint--;
		endPoint--;
		DFS(startPoint, count);
	}else {
		printf("\n��ܿ��~\n\n");
	}
	system("pause");
	return 0;
}