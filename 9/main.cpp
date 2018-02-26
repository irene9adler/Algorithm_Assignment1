#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
typedef struct point//平面点结构体
{
  double x;
  double y;

  friend bool operator < (const point &a, const point &b){//将点集按照x坐标排序
		if(a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
}point;

const int N = 100;
point points[N];
point a,b;//最近点对

void y_QuickSort(point y_sort_points[],int l,int r)//手写快速排序 将点集按照y坐标排序
{
    if (l < r)
    {
        int i = l, j = r;
        point x = y_sort_points[l];
        while (i < j)
        {
            while(i < j && y_sort_points[j].y>= x.y)
                j--;
            if(i < j)
                y_sort_points[i++] = y_sort_points[j];
            while(i < j && y_sort_points[i].y< x.y)
                i++;
            if(i < j)
                y_sort_points[j--] = y_sort_points[i];
        }
        y_sort_points[i] = x;
        y_QuickSort(y_sort_points,l, i - 1);
        y_QuickSort(y_sort_points,i + 1, r);
    }
}

double Distance(point a,point b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closest(int l,int r)
{
    if(l == r)
    {
         a.x = points[l].x;
		 a.y = points[l].y;

		 b.x = points[r].x;
		 b.y = points[r].y;
        return 0;
    }
    else if(l == r - 1)
    {
         a.x = points[l].x;
		 a.y = points[l].y;

		 b.x = points[r].x;
		 b.y = points[r].y;

        return Distance(points[l],points[r]);
    }

    int m = (l + r)/2;
    double res = min(closest(l,m),closest(m,r));//分别计算左右两边最近点对距离，取小
    double tmp;
    int i,j;
    int node_inside_num = 0;
    point node_inside[N];

    //将2d条带内的所有点存入临时数组
    for(i = m - 1; i >= l && points[m].x - points[i].x < res; i--){
        node_inside[node_inside_num++] = points[i];
    }

    for(i = m + 1; i <= r && points[m].x - points[i].x < res; i++){
            node_inside[node_inside_num++] = points[i];
    }

    //按y将条带内的点排序
    y_QuickSort(node_inside,0,node_inside_num - 1);
    for(i = 0;i < node_inside_num;i++)
    {
        cout << "node_inside[" << i << "]:" << node_inside[i].x<<","<<node_inside[i].y<< endl;
    }
    //对y排序后的条带内的每个点，计算其与后面7个点的距离 如果小于左右两边最近距离则更新最近距离
    for(i = 0;i < node_inside_num;i++)
    {
        int end_inside;
        if(node_inside_num - i - 1 < 8) end_inside = node_inside_num;//点i后面不够八个点
        else end_inside = i + 8;
        for(j = i + 1;j < end_inside;j++)
        {
            tmp = Distance(node_inside[i], node_inside[j]);
            if(tmp < res)
            {
               res = tmp;
               a.x = node_inside[i].x;
               a.y = node_inside[i].y;
               b.x = node_inside[j].x;
               b.y = node_inside[j].y;
            }
         }
      }
    return res;
}
int main()
{
    int n;
    cin>>n;//读取平面中点的个数
    int i;
    for(i=0; i<n ; i++){
    	cin>>points[i].x>>points[i].y;//将n个点的坐标值读入points数组
    }

    sort(points,points+n);//按照x坐标值为points数组排序
    double result = closest(0,n - 1);
    cout<<"最近点对为：("<<a.x<<","<<a.y<<") ("<<b.x<<","<<b.y<<") 距离为："<<result<<endl;


    return 0;
}
