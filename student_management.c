#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nRecord Added Successfully!\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("\nID: %d", s.id);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    int id, found = 0;
    struct Student s;

    FILE *fp = fopen("students.dat", "rb");

    printf("\nEnter Student ID to Search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id == id)
        {
            printf("\nRecord Found!");
            printf("\nID: %d", s.id);
            printf("\nName: %s", s.name);
            printf("\nMarks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}

void deleteStudent()
{
    int id;
    struct Student s;
    int found = 0;

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("\nEnter Student ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id != id)
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

void updateStudent()
{
    int id, found = 0;
    struct Student s;

    FILE *fp = fopen("students.dat", "rb+");

    printf("\nEnter Student ID to Update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id == id)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("\nRecord Updated Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n\n===== STUDENT MANAGEMENT SYSTEM =====");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            printf("\nThank You!\n");
            break;

        default:
            printf("\nInvalid Choice!");
        }

    } while (choice != 6);

    return 0;
}