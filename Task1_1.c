#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct add{// Cấu trúc address phonebook
    char name[30];
    char phone[10];
    char mail[50];
}add;
int binsearch(add s[],int n,char name[]){// Hàm tìm kiếm nhị phân
    int l,r,mid;
    l=0;
    r=n-1;
    while(l<r){
        mid = (l+r)/2;
        if (strcmp(s[mid].name,name)==0)
            return mid;
        else if (strcmp(s[mid].name,name) > 0){
            r = mid -1;
        }
        else if (strcmp(s[mid].name,name) < 0){
            l= mid + 1;
        }
    }
    return -1;
}
int main(){
    int i,n;
    add arr[100];
    add x;
    /*FILE *f = fopen("phonebook.dat","w+b");
    if (f == NULL){
        printf("Error");
        exit(1);
    }
    printf("Nhap so phan tu: ");
    scanf("%d",&n);
    for (i=0;i<n;i++){
        printf("Nhap tt nguoi thu %d: ",i);
        printf("Nhap ten: ");
        fflush(stdin);
        gets(x.name);
        printf("Nhap sdt: ");
        fflush(stdin);
        gets(x.phone);
        printf("Nhap email: ");
        fflush(stdin);
        gets(x.mail);
        fwrite(&x,sizeof(add),1,f);
    }
    fclose(f);*/
    printf("Nhap so phan tu muon lay: ");// Nhập số phần tử muốn đọc từ file input
    scanf("%d",&n);
    FILE *f1 = fopen("phonebook.dat","rb");// File dùng để đọc phần tử vào chương trình
    FILE *f2 = fopen("phonebook_result.dat","w+b");// File dùng để ghi kết quả
    if (f1 == NULL){
        printf("Error");
        exit(1);
    }
    if (f2 == NULL){
        printf("Error");
        exit(1);
    }
    char ten[20];
    printf("Nhap ten can tim kiem: ");
    fflush(stdin);
    gets(ten);
    fread(arr,sizeof(add),n,f1);
    int k1 = binsearch(arr,n,ten);
    if ( k1 == -1)
        printf("Khong co ten nguoi can tim!");
        else{
            printf("Thong tin tim duoc:\nTen: %s\nSDT: %s\nEmail: %s\n",arr[k1].name,arr[k1].phone,arr[k1].mail);// Ghi kết quả ra màn hình
            fwrite(&arr[k1],sizeof(add),1,f2);// Ghi kết quả vào file output
        }
    fclose(f1);
    fclose(f2);
    return 0;
}