// PhoneBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>

struct node
{
    int num;
    char name[15];
    struct node* next;
};

struct node* list;
FILE* fp;

struct node* getrecord()
{
    struct node* temp, e;
    temp = (struct node*)malloc(sizeof(struct node));

    printf("Reached till here...");
    getch();

    fflush(stdin);
    fscanf_s(fp, "%d %s", temp->num, temp->name);
    fread(&temp, sizeof(temp), 1, fp);
    printf("%d %s", temp->num, temp->name);
    //temp->num = e.num;
    //strcpy(temp->name, e.name);
    getch();
    temp->next = NULL;
    return temp;
}

struct node* getnode()
{
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));

    printf("Enter person's phone number--->");
    scanf_s("%d", &temp->num);

    printf("Enter person's name--->");
    scanf_s("%s", &temp->name);

    temp->next = NULL;
    return temp;
}

struct node* search(int id, int* flag)
{
    struct node* cur, * prev;
    *flag = 0;

    if (list == NULL)
        return NULL;

    for(prev = NULL, cur = list; (cur); prev = cur, cur = cur->next)
        if (cur->num == id)
        {
            *flag = 1;
            break;
        }
    return prev;
}

int insert(struct node* new1)
{
    struct node* prev;
    int flag, a = 1;

    prev = search(new1->num, &flag);

    if (list == NULL)
    {
        list = new1;
        return 0;
    }

    if (flag == 1)
        return -1;
    else
    {
        new1->next = prev->next;
        prev->next = new1;
    }

    return a;
}

void display()
{
    struct node* cur;
    int n = 0;

    if (list == NULL)
    {
        printf("List empty!");
        return;
    }

    printf("The phone records are--->");
    cur = list;
    for (cur = list; (cur); cur = cur->next)
    {
        printf("Record no. %d--->", n + 1);
        printf("Record no. %d--->", cur->name);
        printf("Person's name %s--->", cur->name);
        n++;
    }
}

int delnode(int id)
{
    struct node* prev, * temp;
    int flag = 0;

    if (list == NULL)
        return -1;

    prev = search(id, &flag);

    if (flag == 0)
        return -1;

    if (prev == NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
    else
    {
        temp = prev->next;
        prev->next = temp->next;
        free(temp);
    }

    return 0;
}

struct node* query(int id, char* flag, int toggle)
{
    struct node* cur, * prev;
    int x = 0;

    if (list == NULL)
        return NULL;

    if (toggle)
    {
        for(prev = NULL, cur = list; (cur); prev = cur, cur = cur->next)
            if (cur->num == id)
            {
                x = 1;
                break;
            }
    }
    else
    {
        for (prev = NULL, cur = list; (cur); prev = cur, cur = cur->next)
            if (!strcmp(cur->name, flag))
            {
                x = 1;
                break;
            }
    }
    if (x == 0)
    {
        printf("The phone number does not exist!");
        return NULL;
    }

    return cur;
}

void CopyToFile()
{
    FILE* fp;
    struct node* cur;
    fp = fopen("phone.txt", "w");

    cur = list;
    if (cur == NULL)
    {
        printf("The list is empty, nothing to write back...");
        return;
    }

    for (cur = list; (cur) ; cur = cur->next)
        fprintf(fp, "%d, %s", cur->num, cur->name);
    fclose(fp);
}

int main()
{
    int ch = 0, ans = 0;
    int val = 0;
    char str[15];
    struct node* new1, * new2;

    fp = fopen("phone.txt", "r");

    if (fp == NULL)
    {
        printf("File can't be opened!");
        return 0;
    }

    while (!feof(fp))
    {
        new1 = getrecord();

        if (insert(new1) == 1)
            printf("Can't insert error! Error...");
        else
            printf("Record entered...");
    }
    fclose(fp);

    do
    {
        printf("Menu");
        printf("1.Add a new phone record.");
        printf("2.Delete an existing record.");
        printf("3.Show all records");
        printf("4.Modify a particular record");
        printf("5.Exit");

        switch (ch)
        {
        case 1:
            new1 = getnode();
            val = insert(new1);
            if (val == -1)
                printf("Employee id already exists! Try again...");
            else
                printf("Employee details succesfully stored");
            break;

        case 2:
            printf("Enter the phone no. you want to delete--->");
            scanf("%d", &val);
            ans = delnode(val);

            if (ans == -1)
                printf("Record not found");
            else
                printf("Record deleted");
            break;

        case 3:
            display();
            break;
        
        case 4:
            printf("Search by phone number or name(1/2)?--->");
            scanf("%d", &ch);
            if (ch == 1)
            {
                printf("Enter the phone number you wish to search for--->");
                scanf("%d", &val);
                new2 = query(val, str, 0);
            }
            else
            {
                printf("Enter the person's name you want to search--->");
                scanf("%s", &str);
                new2 = query(val, str, 1);
            }
            if (new2)
            {
                printf("Enter the new name of the person--->");
                scanf("%s", &new2->name);
                printf("Enter the new number of the person--->");
                scanf("%d", &new2->num);
                printf("Record modified successfully!");
            }
            break;

        case 5:
            printf("Leaving Database, writin back to file...");
            CopyToFile();
            getch();
            free(list);
            break;
        default:
            break;
        }
    } while (1);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
