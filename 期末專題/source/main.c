#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int map[100][100];
int row, column;//行，列
int count = 0;//紀錄節點個數
int i, j;
int startPoint, endPoint;
int path[100], visited[100] = { 0 };
int pathNumber = 0;

//
//初始化連線矩陣 (畫圖)
// 
void createGraphics()
{
	int tmp[4][2] = { {0,1},{1,0},{-1,0},{0,-1} }; //上 右 左 下
	memset(map, 0, sizeof(map));//把圖初始化為0
	for (i = 0; i < row*column; i++)
	{
		//找到該點上下左右4個點初始map 
		int r = i / column;//X軸座標
		int c = i % column;//Y軸座標
		for (j = 0; j < 4; j++)//每個點最多有4個路徑
		{
			//（r,c)相鄰的點為（r1,c1) 
			int r1 = r + tmp[j][0];
			int c1 = c + tmp[j][1];	//偵測路徑
			if (r1 >= 0 && r1 < row&&c1 >= 0 && c1 < column)//限制圖的大小
			{
				map[i][r1*column + c1] = 1;//把會用到的路徑設為1
			}
		}
	}
}


//
//返回第n個節點相連線序號最小的節點 
//
int first(int n)
{
	for (i = 0; i < row*column; i++)
	{
		if (map[n][i] == 1)
			return i;
	}
	printf("起點為故障點，請輸入一個不為故障點的起點\n");
	return 0;
}


//
//返回第n個節點相鄰的點的個數
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
//返回第n個節點相連的比now節點序號大的節點,
//
int next(int n, int now)
{
	for (i = now + 1; i < row*column; i++)
	{
		if (map[n][i] == 1)
			return i;
	}
	return 1000;  //當找不到節點n的下一個節點，返回1000
}


//
//DFS尋找所有路徑 
//
void DFS(int nowPoint, int count)
{
	char direction;
	visited[nowPoint] = 1;
	path[count++] = nowPoint; //儲存正確路徑
	if (startPoint > endPoint) {
		direction = 'L'; //如果終點數字大於起點數字只能往左下走
	}else if (startPoint < endPoint) {
		direction = 'R'; //如果起點數字大於終點數字只能往右上走
	}
	if (nowPoint == endPoint && (count) >= 1)
	{
		int select = 0;

		if (direction == 'R') {
			for (i = 0; i < (count)-1; i++) {
				if (path[i] > path[i + 1])
					select = 1;		
			} //判斷往右上走的路徑是否正確
		}else if (direction == 'L') {
			for (i = 0; i < (count)-1; i++) {
				if (path[i] < path[i + 1])
					select = 1;		
			} //判斷往左下走的路徑是否正確
		} //正確select=0

		if (select == 0) {
			pathNumber++;
			printf("這兩個城市間第%d條簡單路徑為: ", pathNumber);

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
	visited[nowPoint] = 0;  //將走過的路徑設為0 
	(count)--;
	return;
}


int main()
{
	int count = 0, pathNumber = 0;
	printf("請輸入要生成圖的行和列：\n");
	scanf("%d%d", &row, &column);
	createGraphics();
	printf("請輸入要找到路徑的起點和終點:\n");
	scanf("%d%d", &startPoint, &endPoint);
	if (startPoint != endPoint) {
		startPoint--;
		endPoint--;
		DFS(startPoint, count);
	}else {
		printf("\n選擇錯誤\n\n");
	}
	system("pause");
	return 0;
}