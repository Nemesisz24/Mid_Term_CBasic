#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct add{// Cấu trúc address phonebook
    char name[30];
    char phone[10];
    char mail[50];
}add;
typedef struct node{// Cấu trúc 1 node
    add data;
    struct node* next;
}node;
node *head;
node *Cnode(add x){// hàm tạo 1 node mới
    node *p = (node*)malloc(sizeof(node));
    p->data = x;
    p->next = NULL;
    return p;
}
void addnode(node *p){//hàm thêm node vào danh sách liên kết đơn
    node *k;
    if (head == NULL)
        head = p;
    else{
        for (k=head;k->next != NULL;k=k->next)
            ;;
        k->next = p;
    }
}
int findnode(char name[]){// hàm tìm node sử dụng self-organizing search ( nếu tìm được thì chuyển lên làm node đầu tiên). tìm được trả về 1, không thì trả về 0
    node *k;
    if (strcmp(head->data.name,name) == 0){
        return 1;
    }
    else{
        for (k=head->next;k->next != NULL;k=k->next){
        if (strcmp(k->data.name, name) == 0){
            node *k1;
            k1=head;
            while(k1->next != k)
                k1=k1->next;
            k1->next = k->next;
            k->next = head;
            head = k;
            return 1;
            }
        }
    }
    return 0;
}
int main(){
    head = NULL;
    FILE *f1 = fopen("phonebook.dat","rb");// file input
    FILE *f2 = fopen("phonebookResultLL.dat","w+b");// file output
    if (f1 == NULL){
        printf("Error");
        exit(1);
    }
    while(!feof(f1)){
        add x;
        fread(&x,sizeof(add),1,f1);
        node *p = Cnode(x);
        addnode(p);
    }
    printf("Nhap ten can tim:");
    char name[100];
    fflush(stdin);
    gets(name);
    if (findnode(name) == 0)
        printf("Khong co ten nay!");
        else{
            printf("Thong tin:\nTen: %s\nPhone: %s\nEmail: %s\n",head->data.name,head->data.phone,head->data.mail);// in thông tin người được tìm kiếm ra màn hình
            fwrite(&head->data,1,sizeof(add),f2);// ghi thông tin người được tìm kiếm vào file output, thông tin bây giờ nằm ở node đầu tiên(head)
        }
    fclose(f1);
    fclose(f2);
    return 0;
}
