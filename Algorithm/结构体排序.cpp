#include<algorithm>
#include<iostream>
using namespace std;

/*
样例
1 3 4
2 5 3
6 3 4
2 4 6
1 7 5
3 4 5
5 6 7
2 4 3
1 3 2
2 5 3
*/
const int N = 10;
struct S
{

    int a;
    int b;
    int c;
    bool operator< (const S &w)const    //先按a正序排，再按b逆序排，再按c正序排(sort()默认正序是升序)
    {
        if(this->a==w.a)
        {
            if(this->b==w.b)
            {
                return this->c < w.c;
            }
            else return this->b > w.b;
        }
        else return this->a < w.a;
    }
    
};

bool cmp(const S &x,const S &y)
{
    return x.a > y.a;
}

int main()
{
    S h[N];
    for(int i=0;i<N;i++)
    {
        scanf("%d%d%d",&h[i].a,&h[i].b,&h[i].c);
    }
    sort(h,h+N);
    for(int i=0;i<N;i++)
    {
        printf("(%d,%d,%d)\n",h[i].a,h[i].b,h[i].c);
    }
    sort(h,h+N,cmp);  //按a降序
    puts("\n");
    for(int i=0;i<N;i++)
    {
        printf("(%d,%d,%d)\n",h[i].a,h[i].b,h[i].c);
    }

    return 0;
}