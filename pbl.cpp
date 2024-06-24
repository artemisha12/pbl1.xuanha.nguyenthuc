#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define ERROR_ID -1


// khai bao kieu cau truc BOOk
struct Book
{
    int ms;
    char ten[100];
    char tac_gia[100];
    char nha_xuat_ban[100];
    int nam;
    int tinh_trang_sach;
    int soluong;
    int soluongmuon;
	};
typedef struct Book book;


struct BookNode
{
    struct Book BookInf;
    struct BookNode *next;
};
typedef struct BookNode *Position;
typedef struct BookNode BookNode;
typedef struct BookNode *Node;
 
// tao node dau tien
Node CreateHead()
{
    Node head;
    head = NULL;
    return head;
}


// tao mot node moi
Node MakeBookNode(book Book)
{
    Node p;
    p = (Node)malloc(sizeof(struct BookNode));
    p->BookInf = Book;
    p->next = NULL;
    return p;
}


// xac dinh do dai
int size(Node a)
{
    int dem = 0;
    while (a != NULL)
    {
        ++dem;
        a = a->next;
    }
    return dem;
}
// chen vao dau danh sach
Node InsertFirst(Node head, book bookinf)
{
    Node tmp = MakeBookNode(bookinf);
    if (head == NULL)
    {
        head = tmp;
    }
    else
    {
        tmp->next = head;
        head = tmp;
    }
	printf("Them sach thanh cong!\n");

    return head;
}
// them mot phan tu vao cuoi
Node InsertLast(Node head, book bookinf)
{
    Node tmp = MakeBookNode(bookinf);
    if (head == NULL)
    {
        head = tmp;
    }
    else
    {
        Node p = head; // lap mot node moi de khong lam thay doi node head ban dau
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = tmp;
    }
    return head;
}


// Them vao sau mot quyen sach thong qua ma so sách
Node InsertAfter(Node head, book bookinf, int Ms)
{
    if (head == NULL)
    { // neu rong thi chen vo dau
        head = InsertFirst(head, bookinf);
    }
    Node p = head;                           // bien p de duyet
    int notfound = 1;                        // cho ban dau là không tim thay
    while (p->next != NULL && notfound == 1) // out neu da tim duoc vi tri
    {
        if (p->BookInf.ms == Ms)
        {
            notfound = 0; // ?ánh d?u ?? t?m th?y và out
            Node tmp = MakeBookNode(bookinf);
            tmp->next = p->next;
            p->next = tmp;
        }
        p = p->next;
    }
    if (notfound)
        printf("khong tim thay vi tri nay\n");
    else printf("Them sach thanh cong!\n");
    return head;
}


// in mot quyen sach
void xuat(Node book)
{
     printf("%-10d%-40s%-40s%-40s%-25d%-10d%-10d\n",book->BookInf.ms, book->BookInf.ten, book->BookInf.tac_gia, book->BookInf.nha_xuat_ban,
           book->BookInf.nam, book->BookInf.tinh_trang_sach, book->BookInf.soluong);
}


// tim theo ten sach
void FindBookName(Node head)
{  
    char name[60];
    printf("nhap ten sach muon tim : ");
	getchar ();  
    fgets(name,sizeof(name),stdin);
    name[strcspn(name, "\n")] = '\0';
    printf ("%-10s%-40s%-40s%-40s%-25s%-10s%-10s\n","BookID","BookName","Author","Publisher", "PublisYear","Status","Amount");
    Node currentNode = head;
    int found = FALSE;
    while (currentNode != NULL)
    {
        if (strcmpi((currentNode->BookInf.ten),(name)) == 0)
        {
            xuat(currentNode);
            found = TRUE;
        }
        currentNode = currentNode->next;
    }
    if (!found ) printf ("khong tim thay sach\n ");
}



// tim theo ten tac gia
void FindAuthor(Node head)
{  
    char name[60];
    printf("nhap ten tac gia muon tim : ");
    getchar ();  
    fgets(name,sizeof(name),stdin);
    name[strcspn(name, "\n")] = '\0';
     printf ("%-10s%-40s%-40s%-40s%-25s%-10s%-10s\n","BookID","BookName","Author","Publisher", "PublisYear","Status","Amount");
    Node currentNode = head;
    int found = FALSE;
    while (currentNode != NULL)
    {
        if (strcmpi((currentNode->BookInf.tac_gia),(name)) == 0)
        {
            xuat(currentNode);
            found = TRUE;
        }
        currentNode = currentNode->next;
    }
    if (!found ) printf ("khong tim thay sach\n ");
}


// tim theo ten nha xuat ban
void FindPublisher(Node head)
{  
    char name[60];
    printf("nhap ten nha xuat ban muon tim : ");
    getchar ();  
    fgets(name,sizeof(name),stdin);
    name[strcspn(name, "\n")] = '\0';
    printf ("%-10s%-40s%-40s%-40s%-25s%-10s%-10s\n","BookID","BookName","Author","Publisher", "PublisYear","Status","Amount");
    Node currentNode = head;
    int found = FALSE;
    while (currentNode != NULL)
    {
        if (strcmpi((currentNode->BookInf.nha_xuat_ban),(name)) == 0)
        {
            xuat(currentNode);
            found = TRUE;
        }
        currentNode = currentNode->next;
    }
    if (!found ) printf ("khong tim thay sach\n ");
}
//Xoa node dau tien
Node deleteFirst(Node a)
{
    if(a==NULL) printf("Khong co gi de xoa!");
    else    a=a->next;
    return a;
}
//Xoa node cuoi cung
Node deleteLast(Node a)
{
    if(a==NULL || a->next==NULL) return deleteFirst(a);
    Node p=a;
    while(p->next->next!=NULL) p=p->next;
    p->next=NULL;
    return a;
}
//Xoa sach theo ma so
Node deleteID(Node a)
{
    int id;
    int found = 1;
    printf("Nhap ma so sach can xoa: ");
    scanf("%d", &id);
    if(a==NULL || a->BookInf.ms==id) a=deleteFirst(a);
    else
    {
        for(Node p = a; p->next != NULL; p=p->next)
        {
            if(p->BookInf.ms == id)
            {  
                found = 0;
                p->next = p->next->next;
                break;
            }
        }
        if(found)   printf("Khong tim thay vi tri nay!\n");
    }
    return a;
}
//Xoa sach sau mot ma so nao do
Node deleteAfterID(Node a)
{
    int id;
    printf("Nhap ma so sach truoc sach can xoa: ");
    scanf("%d",&id);
    if(a==NULL) printf("Khong co gi de xoa!");
    else
    {
        int found =1;
        for(Node p=a; p->next!=NULL; p=p->next)
        {
            if(p->BookInf.ms==id)
            {
                found=0;
                p->next=p->next->next;
            }
        }
        if(found) printf("Khong tim thay vi tri nay!\n");
    }
    return a;
}


Node deleteBookName(Node a)
{
    int found = 1;
    char bookname[60];
    printf("Nhap ten sach can xoa: ");
    fflush(stdin);
    fgets(bookname, sizeof(bookname), stdin);
    // Loai bo cac ky tu newline
    if (bookname[strlen(bookname) - 1] == '\n')
        bookname[strlen(bookname) - 1] = '\0';


    if (a == NULL || strcmpi(a->BookInf.ten, bookname) == 0)
    {
        a = deleteFirst(a);
        printf("Da xoa sach %s.\n",bookname);
    }
    else
    {
        for(Node p=a; p->next!=NULL; p=p->next)
        {
            if(strcmpi(p->next->BookInf.ten, bookname) == 0)
            {
                found=0;
                p->next=p->next->next;
                printf("Da xoa sach %s.\n",bookname);
                break;
            }
        }
        if(found) printf("Khong co ten sach nay trong thu vien!\n ");
    }


    return a;
}

Node deleteAuthor(Node head){
	int found =0; 
	char author[60];
	printf("Nhap ten tac gia can xoa: ");
	fflush(stdin);
    fgets(author, sizeof(author), stdin);
    if (author[strlen(author) - 1] == '\n')
        author[strlen(author) - 1] = '\0';
    
    if (head==NULL){
    	printf("Thu vien rong!\n");
    	return NULL;
	}
	if (strcmpi(head->BookInf.tac_gia, author) == 0)
    {
        found = 1;
        Node temp = head;
        head = head->next;
        free(temp);
        if (head == NULL) 
            return NULL;
    }
 Node current = head;
    while (current->next != NULL)
    {
        if (strcmpi(current->next->BookInf.tac_gia, author) == 0)
        {
            found = 1;
            Node temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }

  
    if (!found)
        printf("Khong co sach cua tac gia %s trong thu vien!\n", author);
    else
        printf("Da xoa sach cua tac gia %s\n", author);

    return head;
}

void display(Node head)
{
    printf ("%-10s%-40s%-40s%-40s%-25s%-10s%-10s\n","BookID","BookName","Author","Publisher", "PublisYear","Status","Amount");
    int count = 1;
    Node p=head ;
    while (p != NULL)
    {
        printf("%-10d%-40s%-40s%-40s%-25d%-10d%-10d\n",p->BookInf.ms, p->BookInf.ten, p->BookInf.tac_gia, p->BookInf.nha_xuat_ban,
             p->BookInf.nam, p->BookInf.tinh_trang_sach,p->BookInf.soluong);
        count++;
        p = p->next;
    }
}
//Cac ham hoan doi
void swapint(int *x,int *y){
    int temp=*x;
    *x=*y;
    *y=temp;
}
void swapBookInf(Node t, Node p){
    book temp = t->BookInf;
    t->BookInf = p->BookInf;
    p->BookInf =temp;
}
//Xem danh sach theo thu tu: theo van alphabet cua ten sach
void sortBookName(Node a)
{
    for(Node p = a; p != NULL; p = p->next)
    {
        Node t = p;
        for(Node q = p->next; q != NULL; q = q->next)
        {
            if(strcmp(t->BookInf.ten,q->BookInf.ten) > 0)
            {
                t = q;
            }
        }
        if(t!=p )swapBookInf(t,p);
    }
    display(a); // Tr? v? danh sách d? s?p x?p


}


void  sortAuthor(Node a){
    for(Node p=a; p!=NULL; p=p->next){
        Node t=p;
        for(Node q=p->next; q!=NULL; q=q->next){
            if(strcmp(t->BookInf.tac_gia,q->BookInf.tac_gia)>0) t=q;
        }
        if(t!=p) swapBookInf(t,p);
    }
    display(a);
}
void sortNXB(Node a){
    for(Node p=a; p!=NULL; p=p->next){
        Node t=p;
        for(Node q=p->next; q!=NULL; q=q->next){
            if(strcmp(t->BookInf.nha_xuat_ban,q->BookInf.nha_xuat_ban)>0) t=q;
        }
        if(t!=p) swapBookInf(t,p);
    }
    display(a);
}
 void displayAvailable (Node head ){
    printf ("%-10s%-40s%-40s%-40s%-25s%-10s%-10s\n","BookID","BookName","Author","Publisher", "PublisYear","Status","Amount");
    int count = 1;
    Node p = head ;
    while (p != NULL)
        {  if (p->BookInf.tinh_trang_sach!=0){
            printf("%-10d%-40s%-40s%-40s%-25d%-10d%-10d\n",p->BookInf.ms, p->BookInf.ten, p->BookInf.tac_gia, p->BookInf.nha_xuat_ban,
             p->BookInf.nam, p->BookInf.tinh_trang_sach,p->BookInf.soluong);
          }
        count++;
        p = p->next;
}
 }
void displayLent (Node head ){
    printf ("%-10s%-40s%-40s%-40s%-25s%-10s%-10s\n","BookID","BookName","Author","Publisher", "PublisYear","Status","LentAmount");
    int count = 1;
    Node p = head ;
    while (p != NULL)
        {  if (p->BookInf.soluongmuon>0 ){
            printf("%-10d%-40s%-40s%-40s%-25d%-10d%-10d\n",p->BookInf.ms, p->BookInf.ten, p->BookInf.tac_gia, p->BookInf.nha_xuat_ban,
             p->BookInf.nam, p->BookInf.tinh_trang_sach,p->BookInf.soluongmuon);
             
        count++;}
        p = p->next;
   
     
 }
}


Node fixID(Node a)
{
    int ID, found=0;
    Node p;
    printf("Nhap ma so sach can sua: "); scanf("%d",&ID);
    for( p=a; p!=NULL; p=p->next){
        if(p->BookInf.ms==ID)
        {
            found=1;
            break;
        }
    }
    if(found){
        int newID;
        printf("Nhap ma so moi: "); scanf("%d",&newID);
        p->BookInf.ms=newID;
    }
    else printf("Khong tim thay ma so sach!\n");
    return a;
}


Node fixBookName(Node a){
    int found = 0;
    char bookname[60];
    Node p;
    printf("Nhap ten sach can sua: ");
    fflush(stdin);
    fgets(bookname,sizeof(bookname),stdin);
    if (bookname[strlen(bookname) - 1] == '\n') {
        bookname[strlen(bookname) - 1] = '\0';
}
    for( p=a; p!=NULL; p=p->next){
        if(strcmpi(p->BookInf.ten,bookname)==0)
        {
            found=1;
            break;
        }
    }
    if(found){
        char newbookname[60];
        printf("Nhap ten sach moi: ");
        fflush(stdin);
        fgets(newbookname,sizeof(newbookname),stdin);
        if (newbookname[strlen(newbookname) - 1] == '\n') {
            newbookname[strlen(newbookname) - 1] = '\0';
        }
       // p->BookInf.ten = (char *)malloc(strlen(newbookname) + 1);
        strcpy(p->BookInf.ten, newbookname);
       
    }
    else printf("Khong tim thay ten sach!\n");
    return a;
}


Node fixAuthor(Node a){
    int found = 0;
    char author[60];
    Node p;
    printf("Nhap ten tac gia can sua: ");
    fflush(stdin);
    fgets(author,sizeof(author),stdin);
    if (author[strlen(author) - 1] == '\n') {
        author[strlen(author) - 1] = '\0';
}
    for( p=a; p!=NULL; p=p->next){
        if(strcmpi(p->BookInf.tac_gia,author)==0)
        {
            found=1;
            break;
        }
    }
    if(found){
        char newAuthor[60];
        printf("Nhap ten tac gia moi: ");
        fflush(stdin);
        fgets(newAuthor,sizeof(newAuthor),stdin);
        if (newAuthor[strlen(newAuthor) - 1] == '\n') {
            newAuthor[strlen(newAuthor) - 1] = '\0';
        }
      //  p->BookInf.tac_gia = (char *)malloc(strlen(newAuthor) + 1);
        strcpy(p->BookInf.tac_gia, newAuthor);
       
    }
    else printf("Khong tim thay ten tac gia!\n");
    return a;
}


Node fixNXB(Node a){
    int found = 0;
    char nxb[60];
    Node p;
    printf("Nhap ten NXB can sua: ");
    fflush(stdin);
    fgets(nxb,sizeof(nxb),stdin);
    if (nxb[strlen(nxb) - 1] == '\n') {
        nxb[strlen(nxb) - 1] = '\0';
}
    for( p=a; p!=NULL; p=p->next){
        if(strcmpi(p->BookInf.nha_xuat_ban,nxb)==0)
        {
            found=1;
            break;
        }
    }
    if(found){
        char newNXB[60];
        printf("Nhap ten NXB moi: ");
        fflush(stdin);
        fgets(newNXB,sizeof(newNXB),stdin);
        if (newNXB[strlen(newNXB) - 1] == '\n') {
            newNXB[strlen(newNXB) - 1] = '\0';
        }
      //  p->BookInf.nha_xuat_ban = (char *)malloc(strlen(newNXB) + 1);
        strcpy(p->BookInf.nha_xuat_ban, newNXB);
       
    }
    else printf("Khong tim thay ten NXB!\n");
    return a;
}
book Inputbook (){
    book newbook;
    printf ("Nhap ma so sach : ");
    scanf("%d",&newbook.ms);
    getchar();
    printf ("Nhap ten sach : ");
    fgets(newbook.ten,sizeof(newbook.ten),stdin);
    newbook.ten[strcspn(newbook.ten, "\n")] = '\0';
    printf ("Nhap ten tac gia :  ");
    fgets(newbook.tac_gia,sizeof(newbook.tac_gia),stdin);
    newbook.tac_gia[strcspn(newbook.tac_gia, "\n")] = '\0';
    printf ("Nhap ten nha xuat ban : ");  
    fgets(newbook.nha_xuat_ban,sizeof(newbook.nha_xuat_ban),stdin);
    newbook.nha_xuat_ban[strcspn( newbook.nha_xuat_ban, "\n")] = '\0';
    printf ("Nhap nam xuat ban : ");
    scanf("%lu",&newbook.nam);
    newbook.tinh_trang_sach =TRUE;
    printf("Nhap so luong sach:");
    scanf("%lu",&newbook.soluong);
    newbook.soluongmuon=0; 
  return newbook;
}
Node  Borrow (Node head ){
    Node p= head ;
    printf ("Nhap ma so sach ban can muon : ");
    int id;
    scanf ("%d",&id);
    printf ("\n"); 
    printf ("Nhap so luong sach ban can muon : ") ;
    unsigned int sl; 
    scanf ("%lu",&sl); 
    char s[100];
    int found =0;
    while (p!=NULL && found==0 ){
        if (p->BookInf.ms==id) {
        	found = 1;
        	strcpy(s,p->BookInf.ten);
        	if (sl<p->BookInf.soluong) {
            p->BookInf.tinh_trang_sach = 1;
            p->BookInf.soluong-=sl ;
			p->BookInf.soluongmuon +=sl; 
            }
            else if(p->BookInf.soluong == sl ) {
            	p->BookInf.tinh_trang_sach = 0;
            	p->BookInf.soluong=0;
			    p->BookInf.soluongmuon =sl; 
			}
			else if (p->BookInf.soluong<sl ) 
			     {printf ("So luong sach hien tai khong du!\n") ;
			       return head;
			}
			
		}
            p=p->next;
        }
        if (!found ) printf ("Khong co sach mà ban can muon!! \n");
        else printf ("Ban da muon thanh cong %lu sach %s. \n",sl ,s);
        return head;
    }
Node ReturnBook (Node head){
    Node p= head;
  //  displayLent(head );
    printf ("Nhap ma so sach ban muon tra  : ");
    int id;
    scanf ("%d",&id);
    int found =0;
     printf ("\n"); 
    printf ("Nhap so luong sach ban se tra : ") ;
    unsigned int sl; 
    scanf ("%lu",&sl); 
    char s[100];
    while (p!=NULL && found==0 ){
        if (p->BookInf.ms==id && p->BookInf.soluongmuon >0 ) {
            p->BookInf.tinh_trang_sach = 1;
            found = 1;
            strcpy(s,p->BookInf.ten);
        if (p->BookInf.soluongmuon >= sl ) {
        	p->BookInf.soluong += sl;
			p->BookInf.soluongmuon -=sl;  
		}
        }
            p= p-> next;
    }
        if (!found) printf ("Khong co sach mà ban can muon!! \n");
        else printf ("Ban da tra %s thanh cong \n",s);
    return head;
    }
book getLineData(char *line ){
    book book;
    book.ms= ERROR_ID;
    char *token;
    token= strtok (line,",");   // tim va tra lai chuoi dau tien truoc ","
    if (token == NULL ){
        printf ("Line khong co du lieu ");
        exit (-1);
    }
    book.ms = atoi (token ); //chuyen token thanh so
    int index=0;
    for (;; index++)
    {
        token = strtok (NULL, ",");//goi null nhu phan tu dau va tiep tuc tach tai vi tri cu
        if (token==NULL) break; // neu gap null da den cuoi dong or khong con gi de tach thi dung
        if (index==0)
          strcpy(book.ten,token) ;
        else if (index==1)
          strcpy(book.tac_gia,token);
        else if (index==2)
          strcpy(book.nha_xuat_ban,token);
        else if (index==3)
          book.nam = atoi(token);
        else if (index==4 ) 
          book.soluong = atoi(token) ;
        else {
            printf ("Du lieu khong hop le!");
            exit (-1);
           }
       }
        if (index < 4) {
        printf("Dong không day du thông tin\n");
        exit(-1);
    }
    book.tinh_trang_sach = TRUE;
    book.soluongmuon=0; 
  return book;
}
Node  ReadFile (Node head , char fname[100]){
       FILE *file;
       char line[400];
       file = fopen (fname,"r");
                if (file == NULL){
                    printf ("Co loi khi mo file !");
                    exit (-1);
                }
    while(fgets(line,sizeof(line),file)!= NULL){
        book bookinf = getLineData(line );
        if (bookinf.ms!= ERROR_ID ) {
           head= InsertLast(head,bookinf);
        }
    }
    printf ("Mo file thanh cong");
    fclose(file);
    getchar();
    return head;
}

void  ExportFile (Node head , char fname[100]){
    FILE *file ;
    file = fopen (fname,"w");
    if (file == NULL){
                    printf ("Co loi khi mo file !");
                    return;}
    for(Node p=head; p!=NULL; p=p->next){
    	fprintf(file, "%d,", p->BookInf.ms);
        fputs(p->BookInf.ten, file);
        fputs(",", file);
        fputs(p->BookInf.tac_gia, file);
        fputs(",", file);
        fputs(p->BookInf.nha_xuat_ban, file);
        fputs(",", file);
        fprintf(file, "%d,", p->BookInf.nam);
        fprintf(file, "%d,", p->BookInf.tinh_trang_sach);
        fprintf(file, "%d,", p->BookInf.soluong);
        fputs("\n", file);
	}
	printf("Luu file thanh cong!\n");
    fclose(file);
}

void menuIntro(){
    printf("\t**********************************************************************\n");
    printf("\t*                DO AN LAP TRINH TINH TOAN                           *\n");
    printf("\t*___________________QUAN LY THU VIEN_________________________________*\n");
    printf("\t*                                                                    *\n");
    printf("\t*          GIANG VIEN HUONG DAN : Nguyen Cong Danh                   *\n");
    printf("\t*     THUC HIEN BOI : HUYNH THI XUAN HA && NGUYEN PHUOC NGUYEN THUC  *\n");
    printf("\t*                                                                    *\n");
    printf("\t**********************************************************************\n");
}
void menu()
{   
    printf("\t**********************************************************************\n");
    printf("\t*                DO AN LAP TRINH TINH TOAN                           *\n");
    printf("\t*___________________QUAN LY THU VIEN_________________________________*\n");
    printf("\t*                                                                    *\n");
    printf("\t*          GIANG VIEN HUONG DAN : Nguyen Cong Danh                   *\n");
    printf("\t*     THUC HIEN BOI : HUYNH THI XUAN HA && NGUYEN PHUOC NGUYEN THUC  *\n");
    printf("\t*                                                                    *\n");
    printf("\t**********************************************************************\n");
    printf("\t         ___________________MENU___________________________\n");
    printf("\t        |  1. Khoi tao danh sach                           |\n");
    printf("\t        |  2. Them mot cuon sach vao thu vien              |\n");
    printf("\t        |  3. Xoa mot cuon sach khoi thu vien              |\n");
    printf("\t        |  4. Tim kiem sach                                |\n");
    printf("\t        |  5. Xem toan bo sach trong thu vien              |\n");
    printf("\t        |  6. Muon / tra sach                              |\n");
    printf("\t        |  7. Chinh sua danh sach                          |\n");
    printf("\t        |  8. Luu va xuat file                             |\n");
    printf("\t        |  0. Thoat chuong trinh.                          |\n");
    printf("\t        |__________________________________________________|\n");
}
//menu khoi tao sach
void menuInitialize (){
    printf ("_________Khoi tao danh sach__________\n");
    printf (" 1. Khoi tao danh sach rong \n");
    printf (" 2. Doc danh sach tu file \n");
}
// menu  Thêm m?t cu?n sách vào danh sách
void menuInsert()
{
    printf ("___________Them sach_________\n");
    printf (" 1.Them vao dau danh sach\n");
    printf (" 2.Them vao cuoi danh sach\n");
    printf (" 3.Them vao sau mot cuon sach nao do\n");
}
 // menu Xoá m?t cu?n sách kh?i danh sách theo
void menuDelete()
{
    printf ("___________Xoa sach theo _________\n");
    printf (" 1. Ma so  \n");
    printf (" 2. Ten sach \n");
    printf (" 3. Ten tac gia \n");
    printf (" 4. Xoa dau danh sach \n");
    printf (" 5. Xoa sau o sau cuon sach co ma so nao do\n");
    printf (" 6. Xoa cuoi danh sach \n");
   
   
   
}
void menuFix(){
    printf ("___________Chinh sua noi dung sach theo _________\n");
    printf (" 1. Ma so  \n");
    printf (" 2. Ten sach \n");
    printf (" 3. Ten tac gia \n");
    printf (" 4. Ten NXB \n");
}


// menu tim kiem sach
void menuFind ()
{
  printf ("___________Tim kiem sach  _________\n");
  printf (" 1. Tim theo ten sach   \n");
  printf (" 2. Tim theo ten tac gia  \n");
  printf (" 3. Tim theo ten nha xuat ban  \n");
}
//menu xem sach
void menudisplay(){
    printf ("___________ Xem danh sach _________\n");
    printf (" 1. Xem toan bo sach trong danh sach   \n");
    printf (" 2. Xem nhung cuon sach dang cho muon \n");
    printf (" 3. Xem nhung cuon sach chua cho muon  \n");
    printf (" 4. Xem sach theo thu tu  \n");
}
void menudisplay2(){
    printf (" 1. Theo van alphabet cua ten sach   \n");
    printf (" 2. Theo van alphabet cua ten tac gia \n");
    printf (" 3. Theo van alphabet cua ten nha xuat ban  \n");
}
void menuBorrowReturn(){
    printf (" 1. Muon sach  \n");
    printf (" 2. Tra sach \n");
}


int main()
{
    int n,c,b,a,d,e,g,h;
    Node head= CreateHead();
do{
    menu();
    printf ("Nhap lua chon cua ban : ");
    scanf("%d",&n);
    system("cls");
     menuIntro();  
    switch (n) {
        //khoi tao danh sach
        case 1 : {
            menuInitialize();
            printf ("Nhap lua chon cua ban : ");
            scanf ("%d",&a);
            if (a==1){
                 Node head = CreateHead();
                 printf ("Ban da khoi tao thu vien thanh cong \n") ;
            }
            if (a==2){
                char fname[100];
                printf ("Nhap ten file :");
                getchar();
                fgets(fname,sizeof(fname),stdin);
                size_t len = strlen(fname);
                if (len > 0 && fname[len - 1] == '\n') {
                 fname[len - 1] = '\0';
                  }

                head = ReadFile(head,fname);
                         }
            break;
        }
        //Them mot cuon sach vao thu vien
        case 2 : {
            printf ("_____Nhap sach ban muon chen______ \n");
            book book1;
            book1 = Inputbook();
            menuInsert();
            printf ("Nhap lua chon cua ban :");
            scanf ("%d",&b);
            if (b==1){
                head = InsertFirst(head,book1);
            }
            else if (b==2){
                head= InsertLast (head,book1);
            }
            if (b==3){
                printf ("Nhap ID sach ban muon chen vao phia sau : ");
                int id;
                scanf("%d",&id);
               head= InsertAfter(head,book1,id);
            }
            break;
        }
       // Xoa mot cuon sach khoi thu vien
        case 3:{
            menuDelete();
            printf ("Nhap lua chon cua ban : ");
            scanf ("%d",&c);
            if (c==1) {
                head = deleteID(head );
                display(head);
            }
             else if (c==2){
                head = deleteBookName(head );
                display(head);
            }
            else if (c==3){
                head = deleteAuthor (head);
                display(head);
            }
             else if(c==4) {
                head = deleteFirst (head );
                printf("Da xoa dau danh sach\n");
                display(head);
            }
            else if (c==5){
                head = deleteAfterID(head);
                display(head);
            }
            else if (c==6){
                head = deleteLast(head);
                printf("Da xoa cuoi danh sach\n");
                display(head);
            }
            break;
        }
       
        //Tim kiem sach
        case 4: {
       
            menuFind();
            printf (" Nhap lua chon cua ban : ");
            scanf ("%d",&d);
               if (d==1) {
                        FindBookName( head); break;
                    }
                else if (d==2 ){
                         FindAuthor(head);
                }
                else if (d==3){
                    FindPublisher(head);break;
                }
             break;  
        }
        //xem sach  
        case 5:{
            menudisplay();
            printf (" Nhap lua chon cua ban : ");
            scanf ("%d",&d);
            if(d==1){
                display(head);
            }
            if(d==2){
                displayLent(head);
            }
            if(d==3){
                displayAvailable(head);
               
            }
            if(d==4){
                menudisplay2();
                int e;
                printf (" Nhap lua chon cua ban : ");
                scanf ("%d",&e);
                if(e==1){
                    sortBookName(head);
                   }
                if(e==2){
                    sortAuthor(head);
                }
                if(e==3){
                    sortNXB(head);
                }
            }
            break;
        }
        case 6: {  
             menuBorrowReturn() ;
             printf ("Nhap lua chon : ");
             scanf("%d",&g);
            if(g==1){
                 displayAvailable(head);
                 head = Borrow (head);
                    }
            if (g==2){
                displayLent(head);
                head = ReturnBook(head);     }  
            break;
        }
       
        //sua thong tin sach  
        case 7:{    
            menuFix();
            int f;
            printf("Nhap lua chon: "); scanf("%d",&f);
            if(f==1){
                head=fixID(head);
                display(head);
                break;
            }
            if(f==2){
                head = fixBookName(head);
                display(head);
                break;
            }
            if(f==3){
                head = fixAuthor(head);
                display(head);
            break;
            }
            if(f==4){
                head = fixNXB(head);
                display(head);
                break;
            }
        }
        case 8:{
            printf ("____Save and Export file____\n");
            printf ("Nhap ten file :");
            char fname2[100];
            fflush(stdin);
            fgets(fname2,sizeof(fname2),stdin);
            size_t len = strlen(fname2);
    		if (len > 0 && fname2[len - 1] == '\n') {
        	fname2[len - 1] = '\0';
    		}
    		ExportFile(head,fname2);
    	}
    	case 0:{
    		printf("Dong chuong trinh!");
			return 0;
		}
}

    system("pause");
    system ("cls");
}
      while (1);

	printf("Dong chuong trinh!");


    free(head);
    return 0;
}




