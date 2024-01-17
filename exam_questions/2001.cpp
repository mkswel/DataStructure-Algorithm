 #include<iostream>
using namespace std;

/**
 * 链表形式的多项式相乘，按照指数降序排列
*/
typedef struct ListNode{
    double coe;
    int exp;//系数和指数
    struct ListNode* next;
}ListNode, *List;

void ADD(List L, ListNode* p){
    
}
/**
 * 多项式L1乘多项式L2
 * 时间复杂度O(n^3)
*/
List mul(List L1, List L2){
    List L=(List)malloc(sizeof(ListNode));
    L->next=NULL;
    if(!L1||!L2)return NULL;
    List t1 = L1->next;
    while(t1){
        List t2 = L2->next;
        while(t2){
            ListNode* p = (ListNode*)malloc(sizeof(ListNode));
            p->exp=t1->exp+t2->exp;
            p->coe=t1->coe*t2->coe;
            List tmp=L->next, pre=L;
            while(tmp&&tmp->exp>p->exp)pre=tmp, tmp=tmp->next;
            if(!tmp||tmp->exp<p->exp){
                p->next=tmp;
                pre->next=p;
            }
            else tmp->coe+=p->coe, free(p);
            t2=t2->next;
        }
        t1=t1->next;
    }
    return L;
}
const int N1 = 4, N2 = 3;
pair<double, int> p1[N1]={{3,5},{3.5,4},{2.4,2},{6.6,1}}, p2[N2]={{2.3,5},{4.5,3},{6.7,2}};

void create(List &L, int num){
    L=new ListNode;
    L->next=NULL;
    List r=L;
    switch(num){
        case 1:
            for(int i = 0; i < N1; i++){
                List p=new ListNode;
                p->coe=p1[i].first;
                p->exp=p1[i].second;
                p->next=NULL;
                r->next=p;
                r=p;
                cout<<r->coe<<"x^"<<r->exp;
                if(i<N1-1)cout<<"+";
            }
        break;
        case 2:
            for(int i = 0; i < N2; i++){
                List p=new ListNode;
                p->coe=p2[i].first;
                p->exp=p2[i].second;
                p->next=NULL;
                r->next=p;
                r=p;
                cout<<r->coe<<"x^"<<r->exp;
                if(i<N2-1)cout<<"+";
            }
    }
    cout<<endl;
}
int main(){
    List L1, L2;
    create(L1, 1);
    create(L2, 2);
    List L=mul(L1, L2);
    ListNode* p=L->next;
    while(p){
        cout<<p->coe<<"x^"<<p->exp;
        p=p->next;
        if(p)cout<<"+";
    }
    cout<<endl;
    return 0;
}