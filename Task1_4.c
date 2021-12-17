#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct add{// cấu trúc address phonebook 
    char name[30];
    char phone[10];
    char mail[50];
}add;
typedef struct node{// cấu trúc 1 node
    add data;
    struct node *next;
} node;
node *Cnode(add x){// tạo 1 node mới
    node *p = (node*)malloc(sizeof(node));
    p->data = x;
    p->next = NULL;
    return p;
}
typedef struct queue{// cấu trúc queue với node đầu (node này là node cuối trong queue)
    node *head;
} queue;
void makequeue(queue *q){
    q->head = NULL;
}
void push(queue *q,node *p){// thêm 1 node vào queue
    if (q->head == NULL) q->head = p;
    else{
        p->next = q->head;
        q->head = p;
    }
}
void pop(queue *q){// xóa node đầu tiên của queue
    node *k;
    if (q->head->next == NULL) q->head = NULL;
    else{
        for (k=q->head;k->next->next != NULL;k=k->next)
            ;;
        k->next = NULL;
    }
}
node* front(queue *q){// đưa ra node chua dữ liệu đầu tiên của queue
    node *k;
    for (k=q->head;k->next != NULL;k=k->next)
        ;;
    return k;
}
int empty(queue *q){// kiểm tra queue rỗng hay không
    if (q->head == NULL)
        return 1;
        else return 0;
}
int size(queue *q){// trả về kích cỡ queue
    int dem = 0;
    node *k;
    for (k=q->head;k!=NULL;k=k->next){
        dem++;
    }
    return dem;
}
int main(){
    FILE *f1 = fopen("phonebook.dat","rb");// File input đọc dữ liệu
    FILE *f2 = fopen("RemoveFromQueue.dat","wb");// File output
    queue q;
    makequeue(&q);
    add x[100];
    int n;
    if (f1 == NULL || f2 == NULL){
        printf("Error");
        exit(1);
    }
    printf("Nhap so data muon doc tu file input: ");
    scanf("%d",&n);
    fread(x,n,sizeof(add),f1);
    int i;
    for (i=0;i<n;i++){
        node *p = Cnode(x[i]);
        if (size(&q) < 11)// trong khi size queue vẫn nhỏ hơn 11 thì push vào queue
            push(&q,p);
        if (size(&q) == 11){// khi size queue bằng 11 thì đẩy dữ liệu đầu tiên của queue vào file output, cứ thế lần lượt để giữ queue luôn ở size bằng 10
            fwrite(&front(&q)->data,1,sizeof(add),f2);
            pop(&q);
        }
    }
    fclose(f1);
    fclose(f2);
}