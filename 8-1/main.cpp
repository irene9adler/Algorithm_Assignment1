#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int N = 100001;

int num[N];//存储需要排序的数字
int tmp[N];//每次合并的临时数组
long long ans;//逆序对数

void merge_sort(int l,int m,int r)
{
    int i = l;
    int j = m + 1;
    int k = l;
    while(i <= m && j <= r)
    {
        if(num[i] > num[j])//i < j,a[i] > a[j] 逆序
        {
            tmp[k++] = num[j++];
            ans += m - i + 1;//a[i]后面均逆序
        }
        else
        {
            tmp[k++] = num[i++];
        }
    }
    while(i <= m) tmp[k++] = num[i++];
    while(j <= r) tmp[k++] = num[j++];
    for(int i=l;i<=r;i++)
        num[i] = tmp[i];
}

void sort_and_count(int l,int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;
        sort_and_count(l,m);
        sort_and_count(m+1,r);
        merge_sort(l,m,r);
    }
}

int main()
{
    /*从文件中逐行读取数字存入数组*/
    ifstream infile;
    infile.open("8.txt");
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
    int i;
    for(i=0;i<len;i++)
        cout<<num[i]<<endl;
    cout<<endl;

    /*数组排序并计算逆序数*/
    ans = 0;
    sort_and_count(0,len-1);

    cout << "文件中数字逆序对数为：" << ans << endl;
    return 0;
}
