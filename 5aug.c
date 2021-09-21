
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define name 50
#define address 100
#define phone_s 20

typedef struct
{
    int st_id;
    char st_name[name];
    char st_fa_name[name];
    char st_adr[address];
    char phone[phone_s];
    int cls;

} student;

void headMsg()
{
    system("cls");

    printf("\t\t\t***********************************\n");
    printf("\t\t\t*                                 *\n");
    printf("\t\t\t*      Student record system      *\n");
    printf("\t\t\t*                                 *\n");
    printf("\t\t\t***********************************\n\n\n");

}

void add()
{

    student d;
    FILE *filep;
    filep=fopen("dataBase.bin","ab+");
    char decision='Y';
    fseek(filep,0,SEEK_END);
    while(decision=='Y'|| decision=='y')
    {
        headMsg();
        printf("\t\t\t Enter student ID: ");
        scanf("%d",&d.st_id);
        fflush(stdin);
        printf("\t\t\t Student name: ");
        gets(d.st_name);
        fflush(stdin);
        printf("\t\t\t Enter student father name: ");
        gets(d.st_fa_name);
        fflush(stdin);
        printf("\t\t\t Enter student address: ");
        gets(d.st_adr);
        fflush(stdin);
        printf("\t\t\t Enter student phone number: ");
        fflush(stdin);
        gets(d.phone);
        printf("\t\t\t Enter student class: ");
        scanf("%d",&d.cls);

        fwrite(&d,sizeof(d),1,filep);
        printf("\n\t\t\t****************************************\n");
        printf("\t\t\t*                                      *\n");
        printf("\t\t\t*       Record added successfully      *\n");
        printf("\t\t\t*                                      *\n");
        printf("\t\t\t****************************************\n");

        printf("\n\n\t\t\t Want to add another student (Y/N) : ");
        scanf(" %c",&decision);
        fflush(stdin);

    }
    fclose(filep);

}
int findby()
{

    int choice;

    printf("\n");
    printf("\t\t\t How you find student \n");
    printf("\t\t\t----------------------\n");

    printf("\t\t\t 1. Find by student name\n");
    printf("\t\t\t 2. Find by student ID\n");
    printf("\t\t\t 3. Find by student phone number\n");
    printf("\t\t\t Enter your choice : ");
    scanf("%d",&choice);
    printf("\n");
    return choice;
}
void search()
{


    FILE *filep;
    filep=fopen("dataBase.bin","rb+");
    student d;
    rewind(filep);

    char decision='Y';
    while(decision=='Y'|| decision=='y')

    {

        int f=0,id,choice;
        char num[phone_s];
        char sname[name];
        headMsg();
        rewind(filep);



        while(1)
        {

            choice=findby();
            switch (choice)
            {


            case 1:
                printf("\t\t\tEnter student name : ");
                fflush(stdin);
                gets(sname);
                break;
            case 2:
                printf("\t\t\tEnter student ID : ");
                scanf("%d",&id);
                break;
            case 3:
                printf("\t\t\tEnter student phone number : ");
                fflush(stdin);
                gets(num);
                break;
            default:
                printf("\n\t\t\t---!Wrong key!---\n");
                printf("\t\t\tPress correct key\n\n");
                break;
            }
            if(choice==1||choice==2||choice==3)
                break;
        }

        while(fread(&d,sizeof(d),1,filep)==1)
        {
            if(strcmp(d.st_name,sname)==0||d.st_id==id||strcmp(d.phone,num)==0)
            {
                f=1;
                break;
            }

        }
        if(f)
        {
            headMsg();
            printf("\n\n");
            printf("\t\t\t Student ID: %d\n",d.st_id);
            printf("\t\t\t Student name: %s\n",d.st_name);
            printf("\t\t\t Student's father name: %s\n",d.st_fa_name);
            printf("\t\t\t Student's address: %s\n",d.st_adr);
            printf("\t\t\t Student phone number: %s\n",d.phone);
            printf("\t\t\t Student class: %d\n",d.cls);
        }
        else
        {
            printf("\n\n\t\t\t\t*******************\n");
            printf("\t\t\t\t* No record found *\n");
            printf("\t\t\t\t*******************\n");
        }
        printf("\n\n\t\t\t Want to search another student information (Y/N) : ");
        scanf(" %c",&decision);
        fflush(stdin);

    }
}
void del()
{


    student d;
    FILE *filep,*tempf;

    char decision='Y';
    while(decision=='Y'|| decision=='y')

    {

        int f=1,id,choice;
        char num[phone_s];
        char sname[name];
        filep=fopen("dataBase.bin","rb+");
        tempf=fopen("temp.bin","wb+");
        headMsg();
        rewind(filep);

        while(1)
        {

            choice=findby();
            switch (choice)
            {


            case 1:
                printf("\t\t\tEnter student name : ");
                fflush(stdin);
                gets(sname);
                break;
            case 2:
                printf("\t\t\tEnter student ID : ");
                scanf("%d",&id);
                break;
            case 3:
                printf("\t\t\tEnter student phone number : ");
                fflush(stdin);
                gets(num);
                break;
            default:
                printf("\n\t\t\t---!Wrong key!---\n");
                printf("\t\t\tPress correct key\n\n");
                break;
            }
            if(choice==1||choice==2||choice==3)
                break;
        }
        while(fread(&d,sizeof(d),1,filep)==1)
        {

            if(strcmp(d.st_name,sname)==0||d.st_id==id||strcmp(d.phone,num)==0)
            {
                headMsg();
                printf("\t\t\t ==============================================\n");
                printf("\t\t\t =    These information deleted permanently   =\n");
                printf("\t\t\t ==============================================\n");

                printf("\t\t\t Student ID: %d\n",d.st_id);
                printf("\t\t\t Student name: %s\n",d.st_name);
                printf("\t\t\t Student's father name: %s\n",d.st_fa_name);
                printf("\t\t\t Student's address: %s\n",d.st_adr);
                printf("\t\t\t Student phone number: %d\n",d.phone);
                printf("\t\t\t Student class: %d\n",d.cls);
                f=0;
                continue;
            }

            fwrite(&d,sizeof(d),1,tempf);
        }
        if(f)
        {
            printf("\n\n");
            printf("\t\t\t\t*******************\n");
            printf("\t\t\t\t* No record found *\n");
            printf("\t\t\t\t*******************\n");
        }


        printf("\n\n\t\t\t Want to delete another information (Y/N) : ");
        scanf(" %c",&decision);
        fflush(stdin);

        fclose(tempf);
        fclose(filep);
        remove("dataBase.bin");
        rename("temp.bin","dataBase.bin");

    }


}
void update()
{



    FILE *filep;
    filep=fopen("dataBase.bin","rb+");
    student d;
    rewind(filep);
    char decision='Y';
    while(decision=='Y'|| decision=='y')

    {
        int f=0,id,choice;
        char num[phone_s];
        char sname[name];
        headMsg();
        rewind(filep);

        while(1)
        {

            choice=findby();
            switch (choice)
            {


            case 1:
                printf("\t\t\tEnter student name : ");
                fflush(stdin);
                gets(sname);
                break;
            case 2:
                printf("\t\t\tEnter student ID : ");
                scanf("%d",&id);
                break;
            case 3:
                printf("\t\t\tEnter student phone number : ");
                fflush(stdin);
                gets(num);
                break;
            default:
                printf("\n\t\t\t---!Wrong key!---\n");
                printf("\t\t\tPress correct key\n\n");
                break;
            }
            if(choice==1||choice==2||choice==3)
                break;
        }
        while(fread(&d,sizeof(d),1,filep)==1)
        {
            if(strcmp(d.st_name,sname)==0||d.st_id==id||strcmp(d.phone,num)==0)
            {
                f=1;
                break;
            }
        }
        if(f)
        {
            headMsg();

            fseek(filep,-sizeof(d),SEEK_CUR);
            fflush(stdin);
            printf("\t\t\t Student name: ");
            gets(d.st_name);
            fflush(stdin);
            printf("\t\t\t Enter student father name: ");
            gets(d.st_fa_name);
            fflush(stdin);
            printf("\t\t\t Enter student address: ");
            gets(d.st_adr);
            fflush(stdin);
            printf("\t\t\t Enter student phone number: ");
            fflush(stdin);
            gets(d.phone);
            printf("\t\t\t Enter student class: ");
            scanf("%d",&d.cls);

            fwrite(&d,sizeof(d),1,filep);



        }
        else
        {
            printf("\n\n\t\t\t\t*******************\n");
            printf("\t\t\t\t* No record found *\n");
            printf("\t\t\t\t*******************\n");
        }
        printf("\n\n\t\t\t Do you want to update another student information (Y/N) : ");
        scanf(" %c",&decision);
        fflush(filep);
    }
    fclose(filep);




}
void display()
{


    headMsg();
    FILE *filep;
    filep=fopen("dataBase.bin","rb+");
    student d;
    rewind(filep);
    int i=0;
    while((fread(&d,sizeof(d),1,filep))==1)
    {
        printf("\t\t\t----------------------------------\n");
        printf("\t\t\t-     Student %d information     -\n",i+1);
        printf("\t\t\t----------------------------------\n");
        printf("\t\t\t Student ID: %d\n",d.st_id);
        printf("\t\t\t Student name: %s\n",d.st_name);
        printf("\t\t\t Student's father name: %s\n",d.st_fa_name);
        printf("\t\t\t Student's address: %s\n",d.st_adr);
        printf("\t\t\t Student phone number: %s\n",d.phone);
        printf("\t\t\t Student class: %d\n\n\n",d.cls);
        i++;

    }

    system("pause");
    fclose(filep);

}

void menu()
{


    printf("\t\t\t  1. Add student\n");
    printf("\t\t\t  2. Search student\n");
    printf("\t\t\t  3. Delete student\n");
    printf("\t\t\t  4. Update information\n");
    printf("\t\t\t  5. Display information\n");
    printf("\t\t\t  6. Exit\n");
    printf("\n");
    printf("\t\t\t  Enter your choice: ");


}
int main()
{

    int num;

    while(1)
    {
        system("cls");

        headMsg();

        menu();
        scanf("%d",&num);
        switch (num)
        {
        case 1:
            add();
            break;
        case 2:
            search();
            break;
        case 3:
            del();
            break;
        case 4:
            update();
            break;
        case 5:
            display();
            break;
        case 6:
            exit(1);
            break;
        default:

            printf("\n\n\t\t\t*******************************\n");
            printf("\t\t\t*                             *\n");
            printf("\t\t\t*       ! Wrong key !         *\n");
            printf("\t\t\t*   Enter your choice again   *\n");
            printf("\t\t\t*                             *\n");
            printf("\t\t\t*******************************\n\n\n");
            system("pause");
            continue;


        }


    }
}

