#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int N = 100001;

int num[N];//�洢��Ҫ���������
int tmp[N];//ÿ�κϲ�����ʱ����
long long ans;//�������

void merge_sort(int l,int m,int r)
{
    int i = l;
    int j = m + 1;
    int k = l;
    while(i <= m && j <= r)
    {
        if(num[i] > num[j])//i < j,a[i] > a[j] ����
        {
            tmp[k++] = num[j++];
            ans += m - i + 1;//a[i]���������
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
    /*���ļ������ж�ȡ���ִ�������*/
    ifstream infile;
    infile.open("8.txt");
    if(!infile) cout<<"error"<<endl;
    int t1;

    int len = 0;
    cout<<"��������"<<endl;
    while(infile>>t1)
    {
       num[len] = t1;
       len++;
    }

    /*��ӡ����*/
    int i;
    for(i=0;i<len;i++)
        cout<<num[i]<<endl;
    cout<<endl;

    /*�������򲢼���������*/
    ans = 0;
    sort_and_count(0,len-1);

    cout << "�ļ��������������Ϊ��" << ans << endl;
    return 0;
}
