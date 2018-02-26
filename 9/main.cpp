#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
typedef struct point//ƽ���ṹ��
{
  double x;
  double y;

  friend bool operator < (const point &a, const point &b){//���㼯����x��������
		if(a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
}point;

const int N = 100;
point points[N];
point a,b;//������

void y_QuickSort(point y_sort_points[],int l,int r)//��д�������� ���㼯����y��������
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
    double res = min(closest(l,m),closest(m,r));//�ֱ�����������������Ծ��룬ȡС
    double tmp;
    int i,j;
    int node_inside_num = 0;
    point node_inside[N];

    //��2d�����ڵ����е������ʱ����
    for(i = m - 1; i >= l && points[m].x - points[i].x < res; i--){
        node_inside[node_inside_num++] = points[i];
    }

    for(i = m + 1; i <= r && points[m].x - points[i].x < res; i++){
            node_inside[node_inside_num++] = points[i];
    }

    //��y�������ڵĵ�����
    y_QuickSort(node_inside,0,node_inside_num - 1);
    for(i = 0;i < node_inside_num;i++)
    {
        cout << "node_inside[" << i << "]:" << node_inside[i].x<<","<<node_inside[i].y<< endl;
    }
    //��y�����������ڵ�ÿ���㣬�����������7����ľ��� ���С�����������������������������
    for(i = 0;i < node_inside_num;i++)
    {
        int end_inside;
        if(node_inside_num - i - 1 < 8) end_inside = node_inside_num;//��i���治���˸���
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
    cin>>n;//��ȡƽ���е�ĸ���
    int i;
    for(i=0; i<n ; i++){
    	cin>>points[i].x>>points[i].y;//��n���������ֵ����points����
    }

    sort(points,points+n);//����x����ֵΪpoints��������
    double result = closest(0,n - 1);
    cout<<"������Ϊ��("<<a.x<<","<<a.y<<") ("<<b.x<<","<<b.y<<") ����Ϊ��"<<result<<endl;


    return 0;
}
