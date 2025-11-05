#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n=== Student Record System ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add a new student
void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);  // read string with spaces
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d\nName: %s\nMarks: %.2f\n-------------------\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

// Function to search for a student
void searchStudent() {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("No record found for roll number %d\n", roll);

    fclose(fp);
}

// Function to delete a student record
void deleteStudent() {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("No record found for roll number %d\n", roll);
}