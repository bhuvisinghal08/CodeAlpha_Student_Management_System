#include <stdio.h>
#include <stdlib.h>
struct Student
{
    int rollNo;
    char name[50];
    char course[50];
    float marks;
};
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
int main()
{
    int choice;
    do
    {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
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
            printf("\nThank you. Program closed.\n");
            break;
        default:
            printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);
    return 0;
}
void addStudent()
{
    FILE *fp;
    struct Student s;
    fp = fopen("students.dat", "ab");
    if (fp == NULL)
    {
        printf("\nFile could not be opened.\n");
        return;
    }
    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Course Name: ");
    scanf(" %[^\n]", s.course);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("\nStudent record saved successfully.\n");
}
void displayStudents()
{
    FILE *fp;
    struct Student s;
    int count = 0;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }
    printf("\n========== STUDENT RECORDS ==========\n");
    while (fread(&s, sizeof(s), 1, fp))
    {
        count++;
        printf("\nStudent %d\n", count);
        printf("Roll Number : %d\n", s.rollNo);
        printf("Name        : %s\n", s.name);
        printf("Course      : %s\n", s.course);
        printf("Marks       : %.2f\n", s.marks);
    }
    fclose(fp);
    if (count == 0)
    {
        printf("\nNo records available.\n");
    }
}
void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }
    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;
            printf("\nStudent record found.\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Course      : %s\n", s.course);
            printf("Marks       : %.2f\n", s.marks);
            break;
        }
    }
    fclose(fp);
    if (found == 0)
    {
        printf("\nStudent with this roll number was not found.\n");
    }
}
void updateStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;
    fp = fopen("students.dat", "rb+");
    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }
    printf("\nEnter roll number to update: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;
            printf("\nEnter new name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new course: ");
            scanf(" %[^\n]", s.course);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            fseek(fp, -(long)sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("\nStudent record updated successfully.\n");
            break;
        }
    }
    fclose(fp);
    if (found == 0)
    {
        printf("\nStudent record not found.\n");
    }
}
void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }
    temp = fopen("temp.dat", "wb");
    if (temp == NULL)
    {
        printf("\nTemporary file could not be created.\n");
        fclose(fp);
        return;
    }
    printf("\nEnter roll number to delete: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    if (found == 1)
    {
        printf("\nStudent record deleted successfully.\n");
    }
    else
    {
        printf("\nStudent record not found.\n");
    }
}