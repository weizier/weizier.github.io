#include <iostream>
using namespace std;
//��������
void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //���м��������͵�һ�������� �μ�ע1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // ���������ҵ�һ��С��x����
                j--;
            if(i < j)
                s[i++] = s[j];

            while(i < j && s[i] < x) // ���������ҵ�һ�����ڵ���x����
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        for(int i=0;i<8;i++){
            cout<<s[i];
        }
        cout<<endl;
        quick_sort(s, l, i - 1); // �ݹ����
        quick_sort(s, i + 1, r);
    }
}

main(){
    int s[] = {8,9,5,7,4,6,3,6};
    quick_sort(s,0,7);
    for(int i=0;i<8;i++){
        cout<<s[i];
    }
    cout<<endl;
    char a[10];
    cin>>a;
    cout<<a;
}
