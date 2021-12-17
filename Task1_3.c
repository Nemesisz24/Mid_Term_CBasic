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
node* front(queue *q){// đưa ra dữ liệu đầu tiên của queue
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
node* findname(queue *q,char name[]){// hàm tìm tên, tìm được trả về node đó( xử lí dần dần theo thứ tự FIFO), không tìm được trả về NULL
    while(size(q) != 1){
        if (strcmp(front(q)->data.name,name) == 0){
            return front(q);
        }
        pop(q);
    }
    if (strcmp(q->head->data.name,name) == 0){
        return q->head; 
    }
    return NULL;
}
int main(){
    add x;
    queue q;
    makequeue(&q);
    FILE *f1 = fopen("phonebook.dat","rb");// File input
    FILE *f2 = fopen("phonebookResultUsingQueue.dat","w+b");// File output
    if (f1 == NULL){
        printf("Error");
        exit(1);
    }
    if (f2 == NULL){
        printf("Error");
        exit(1);
    }
    while(!feof(f1)){// đọc dữ liệu từ file input và push dần dần vào queue cho đến hết
        fread(&x,1,sizeof(add),f1);
        node *p = Cnode(x);
        push(&q,p);
    }
    char name[20];
    printf("Nhap ten can tim: ");
    fflush(stdin);
    gets(name);
    node *kq = findname(&q,name);
    if (kq == NULL) 
        printf("khong tim thay ten nay!");
    else{
        printf("Thong tin:\nTen: %s\nSDT: %s\nEmail: %s\n",kq->data.name,kq->data.phone,kq->data.mail);// Ghi kết quả tìm kiếm ra màn hình
        fwrite(&kq->data,1,sizeof(add),f2);// Ghi kết quả tìm kiếm vào file output
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
