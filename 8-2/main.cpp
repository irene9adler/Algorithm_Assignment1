#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <malloc.h>

using namespace std;

const int N = 100001;
long long ans;//逆序对数

void quick_sort_and_count(int *a,int l,int r)
{
    int left_num = 0;
    int right_num = 0;

    int *left = (int*)calloc(r-l,sizeof(int));
    int *right = (int*)calloc(r-l,sizeof(int));
    //int right[r - l];
    int pivot;
    if(l < r)
    {
        pivot = a[l];
        //cout << "pivot:" << pivot << endl;
        int i;
        for(i = l + 1;i <= r;i++)
        {
            if(a[i] < pivot)
            {
                left[left_num++] = a[i];
                ans += right_num;
            }
            else
            {
                right[right_num++] = a[i];
            }

        }
        ans += left_num;
       /* cout << "left_num:" << left_num <<endl;
        cout << "right_num:" << right_num <<endl;
        cout << "ans:" << ans <<endl;*/

        quick_sort_and_count(left,0,left_num - 1);
        quick_sort_and_count(right,0,right_num - 1);
    }
}


int main()
{
    clock_t start,end;
    int num[N];//存储需要排序的数字
    /*从文件中逐行读取数字存入数组*/
    ifstream infile;
    infile.open("9.txt");
    if(!infile) cout<<"error"<<endl;
    int t1;

    int len = 0;
    cout<<"存入数组"<<endl;
    while(infile>>t1)
    {
       num[len] = t1;
       len++;
    }

    /*打印数组*/
    /*int i;
    for(i=0;i<len;i++)
        cout<<num[i]<<endl;
    cout<<endl;*/

    /*数组排序并计算逆序数*/
    ans = 0;
    start = clock();
    quick_sort_and_count(num,0,len-1);
    end = clock();

   /* for(i=0;i<len;i++)
        cout<<num[i]<<endl;
    cout<<endl;*/


    cout << "文件中数字逆序对数为：" << ans << endl;
    cout << "time to quick sort and count : " << (double)(end-start)/CLK_TCK <<endl;
    return 0;
}
