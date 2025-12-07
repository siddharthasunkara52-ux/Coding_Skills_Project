
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX 100

struct Student {
    char roll[20];
    char name[50];
    int age;
    char gender[10];
    char course[50];
    char branch[50];
    float marks;
    char phone[15];
    char email[50];
};

struct Student s[MAX];
int count = 0;

// PASSWORD INPUT 

void getPassword(char *password) {
    char ch;
    int i = 0;

    while (1) {
        ch = getch();

        if (ch == 13) { 
            password[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        }
        else {
            password[i++] = ch;
            printf("*");
        }
    }
}

// ADMIN LOGIN

int adminLogin() {
    char password[20];
    char correctPassword[] = "admin123";

    printf("\n=============================\n");
    printf("        ADMIN LOGIN          \n");
    printf("=============================\n");

    printf("Enter Password: ");
    getPassword(password);

    if (strcmp(password, correctPassword) == 0) {
        printf("\nLogin Successful!\n");
        return 1;
    } else {
        printf("\nIncorrect Password! Access Denied.\n");
        return 0;
    }
}

// SAVE TO CSV 

void saveToCSV() {
    FILE *fp = fopen("students.csv", "w");
    if (!fp) {
        printf("Error saving CSV file!\n");
        return;
    }

    fprintf(fp, "Roll,Name,Age,Gender,Course,Branch,Marks,Phone,Email\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%d,%s,%s,%s,%.2f,%s,%s\n",
                s[i].roll, s[i].name, s[i].age, s[i].gender,
                s[i].course, s[i].branch, s[i].marks,
                s[i].phone, s[i].email);
    }

    fclose(fp);
}

// LOAD FROM CSV 

void loadFromCSV() {
    FILE *fp = fopen("students.csv", "r");
    if (!fp) return;

    char line[300];
    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^,],%[^,],%d,%[^,],%[^,],%[^,],%f,%[^,],%s",
               s[count].roll,
               s[count].name,
               &s[count].age,
               s[count].gender,
               s[count].course,
               s[count].branch,
               &s[count].marks,
               s[count].phone,
               s[count].email);

        count++;
    }

    fclose(fp);
}

// ADD STUDENT

void addStudent() {
    if (count == MAX) {
        printf("Record Full!\n");
        return;
    }

    printf("Enter Roll No: ");
    scanf(" %[^\n]", s[count].roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s[count].name);

    printf("Enter Age: ");
    scanf("%d", &s[count].age);

    printf("Enter Gender: ");
    scanf(" %[^\n]", s[count].gender);

    printf("Enter Course: ");
    scanf(" %[^\n]", s[count].course);

    printf("Enter Branch: ");
    scanf(" %[^\n]", s[count].branch);

    printf("Enter Marks: ");
    scanf("%f", &s[count].marks);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", s[count].phone);

    printf("Enter Email: ");
    scanf(" %[^\n]", s[count].email);

    count++;
    saveToCSV();

    printf("Student Added Successfully!\n");
}

// DISPLAY STUDENTS (ASCII TABLE)

void displayStudents() {
    if (count == 0) {
        printf("No Records Found!\n");
        return;
    }

    int w[] = {15, 20, 3, 6, 10, 10, 7, 12, 26};
    int cols = 9;

    // Top
    printf("+");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < w[i] + 2; j++) printf("-");
        printf("+");
    }
    printf("\n");

    // Header
    printf("| %-15s | %-20s | %-3s | %-6s | %-10s | %-10s | %-7s | %-12s | %-26s |\n",
           "ROLL NO", "NAME", "AGE", "GENDER", "COURSE", "BRANCH", "MARKS", "PHONE", "EMAIL");

    // Mid
    printf("+");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < w[i] + 2; j++) printf("-");
        printf("+");
    }
    printf("\n");

    // Rows
    for (int i = 0; i < count; i++) {
        printf("| %-15s | %-20s | %-3d | %-6s | %-10s | %-10s | %-7.2f | %-12s | %-26s |\n",
               s[i].roll, s[i].name, s[i].age, s[i].gender,
               s[i].course, s[i].branch, s[i].marks,
               s[i].phone, s[i].email);
    }

    // Bottom
    printf("+");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < w[i] + 2; j++) printf("-");
        printf("+");
    }
    printf("\n");
}

//SEARCH STUDENT

void searchStudent() {
    char roll[20];
    int found = 0;

    printf("Enter Roll No to Search: ");
    scanf(" %[^\n]", roll);

    for (int i = 0; i < count; i++) {
        if (strcmp(s[i].roll, roll) == 0) {
            printf("\nStudent Found:\n");
            printf("Roll: %s\n", s[i].roll);
            printf("Name: %s\n", s[i].name);
            printf("Age: %d\n", s[i].age);
            printf("Gender: %s\n", s[i].gender);
            printf("Course: %s\n", s[i].course);
            printf("Branch: %s\n", s[i].branch);
            printf("Marks: %.2f\n", s[i].marks);
            printf("Phone: %s\n", s[i].phone);
            printf("Email: %s\n", s[i].email);

            found = 1;
            break;
        }
    }

    if (!found) printf("No Student Found!\n");
}

//UPDATE STUDENT

void updateStudent() {
    char roll[20];
    int found = 0;

    printf("Enter Roll No to Update: ");
    scanf(" %[^\n]", roll);

    for (int i = 0; i < count; i++) {
        if (strcmp(s[i].roll, roll) == 0) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s[i].name);

            printf("Enter New Age: ");
            scanf("%d", &s[i].age);

            printf("Enter New Gender: ");
            scanf(" %[^\n]", s[i].gender);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s[i].course);

            printf("Enter New Branch: ");
            scanf(" %[^\n]", s[i].branch);

            printf("Enter New Marks: ");
            scanf("%f", &s[i].marks);

            printf("Enter New Phone: ");
            scanf(" %[^\n]", s[i].phone);

            printf("Enter New Email: ");
            scanf(" %[^\n]", s[i].email);

            printf("Record Updated Successfully!\n");
            saveToCSV();
            found = 1;
            break;
        }
    }

    if (!found) printf("Student Not Found!\n");
}

//DELETE STUDENT 

void deleteStudent() {
    char roll[20];
    int found = 0;

    printf("Enter Roll No to Delete: ");
    scanf(" %[^\n]", roll);

    for (int i = 0; i < count; i++) {
        if (strcmp(s[i].roll, roll) == 0) {
            for (int j = i; j < count - 1; j++) {
                s[j] = s[j + 1];
            }
            count--;
            printf("Record Deleted Successfully!\n");
            saveToCSV();
            found = 1;
            break;
        }
    }

    if (!found) printf("Student Not Found!\n");
}

//MAIN

int main() {

    loadFromCSV();  // Load saved data

    if (!adminLogin()) {
        return 0;
    }

    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); return 0;
            default: printf("Invalid Choice!\n");
        }
    }
}
