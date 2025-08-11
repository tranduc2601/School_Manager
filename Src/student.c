#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../Include/datatype.h"
#include "../Include/function.h" // Các hàm tiện ích chung
#include "../Include/student.h"

// ===== Biến toàn cục cho sinh viên =====
struct Student students[MAX_STUDENTS];
int studentCount = 0;

// ===== File I/O =====
void loadStudentsFromFile() {
    FILE *f = fopen("Data/student.bin", "rb");
    if (f == NULL) {
        studentCount = 0;
        return;
    }
    if (fread(&studentCount, sizeof(int), 1, f) != 1) studentCount = 0;
    fread(students, sizeof(struct Student), studentCount, f);
    fclose(f);
}

void saveStudentsToFile() {
    FILE *f = fopen("Data/student.bin", "wb");
    if (f == NULL) {
        printf("Cannot open file to write student data!\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, f);
    fwrite(students, sizeof(struct Student), studentCount, f);
    fclose(f);
}

// ===== Chức năng quản lý sinh viên =====
int isStudentIdDuplicate(const char* id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, id) == 0) return 1;
    }
    return 0;
}

void addStudentScreen() {
    while (1) {
        struct Student s;
        printf("\n===== ADD STUDENT =====\n");

        // Nhập studentId
        while (1) {
            printf("Enter student ID (max 10 chars, unique): ");
            fgets(s.studentId, sizeof(s.studentId), stdin);
            s.studentId[strcspn(s.studentId, "\n")] = '\0';

            if (strlen(s.studentId) == 0 || strlen(s.studentId) > 10) {
                printf("Invalid student ID!\n");
                continue;
            }
            if (isStudentIdDuplicate(s.studentId)) {
                printf("Student ID already exists!\n");
                continue;
            }
            break;
        }

        // Nhập classroomId
        while (1) {
            printf("Enter class ID (9 chars): ");
            fgets(s.classroomId, sizeof(s.classroomId), stdin);
            s.classroomId[strcspn(s.classroomId, "\n")] = '\0';
            if (strlen(s.classroomId) != 9) {
                printf("Class ID must be exactly 9 characters!\n");
                continue;
            }
            break;
        }

        // Nhập tên
        while (1) {
            printf("Enter full name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            if (strlen(s.name) == 0) {
                printf("Name cannot be empty!\n");
                continue;
            }
            capitalizeName(s.name);
            break;
        }

        // Ngày sinh
        while (1) {
            printf("Enter date of birth (dd mm yyyy): ");
            if (scanf("%d %d %d", &s.dateOfBirth.day, &s.dateOfBirth.month, &s.dateOfBirth.year) != 3) {
                printf("Invalid date format!\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();
            if (!isValidDateOfBirth(s.dateOfBirth.day, s.dateOfBirth.month, s.dateOfBirth.year)) {
                printf("Invalid date!\n");
                continue;
            }
            break;
        }

        // Giới tính
        printf("Enter gender (1-Male, 0-Female): ");
        int g;
        scanf("%d", &g);
        s.gender = g ? 1 : 0;
        clearInputBuffer();

        // Email
        while (1) {
            printf("Enter email: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = '\0';
            if (!isValidEmail(s.email)) {
                printf("Invalid email format!\n");
                continue;
            }
            break;
        }

        // Số điện thoại
        while (1) {
            printf("Enter phone number: ");
            fgets(s.phone, sizeof(s.phone), stdin);
            s.phone[strcspn(s.phone, "\n")] = '\0';
            if (!isValidPhone(s.phone)) {
                printf("Phone must be 10-11 digits!\n");
                continue;
            }
            break;
        }

        // Thêm vào danh sách
        students[studentCount++] = s;
        saveStudentsToFile();
        printf("Added student successfully!\n");

        printf("Press 0 to go back, any key to add another: ");
        int back;
        if (scanf("%d", &back) == 1 && back == 0) {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }
}

void showStudentListScreen() {
    while (1) {
        printf("\n===== STUDENT LIST =====\n");
        if (studentCount == 0) {
            printf("No students found.\n");
        } else {
            printf("+------------+-----------+--------------------+--------------------+-------------+--------+\n");
            printf("| ID         | Class ID  | Name               | Email              | Phone       | Gender |\n");
            printf("+------------+-----------+--------------------+--------------------+-------------+--------+\n");
            for (int i = 0; i < studentCount; i++) {
                printf("| %-10s | %-9s | %-18s | %-18s | %-11s | %-6s |\n",
                       students[i].studentId,
                       students[i].classroomId,
                       students[i].name,
                       students[i].email,
                       students[i].phone,
                       students[i].gender ? "Male" : "Female");
            }
            printf("+------------+-----------+--------------------+--------------------+-------------+--------+\n");
        }
        printf("Press 0 to go back: ");
        int back;
        scanf("%d", &back);
        clearInputBuffer();
        if (back == 0) break;
    }
}

int findStudentIndexById(const char* id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, id) == 0) return i;
    }
    return -1;
}

void editStudentScreen() {
    while (1) {
        char id[11];
        printf("Enter student ID to edit: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';

        int idx = findStudentIndexById(id);
        if (idx == -1) {
            printf("Student not found!\n");
        } else {
            printf("Editing student: %s\n", students[idx].name);

            // Tên
            while (1) {
                printf("Enter new name: ");
                fgets(students[idx].name, sizeof(students[idx].name), stdin);
                students[idx].name[strcspn(students[idx].name, "\n")] = '\0';
                if (strlen(students[idx].name) == 0) {
                    printf("Name cannot be empty!\n");
                    continue;
                }
                capitalizeName(students[idx].name);
                break;
            }

            // Class ID
            while (1) {
                printf("Enter new class ID (9 chars): ");
                fgets(students[idx].classroomId, sizeof(students[idx].classroomId), stdin);
                students[idx].classroomId[strcspn(students[idx].classroomId, "\n")] = '\0';
                if (strlen(students[idx].classroomId) != 9) {
                    printf("Invalid class ID!\n");
                    continue;
                }
                break;
            }

            // Email
            while (1) {
                printf("Enter new email: ");
                fgets(students[idx].email, sizeof(students[idx].email), stdin);
                students[idx].email[strcspn(students[idx].email, "\n")] = '\0';
                if (!isValidEmail(students[idx].email)) {
                    printf("Invalid email!\n");
                    continue;
                }
                break;
            }

            // Phone
            while (1) {
                printf("Enter new phone: ");
                fgets(students[idx].phone, sizeof(students[idx].phone), stdin);
                students[idx].phone[strcspn(students[idx].phone, "\n")] = '\0';
                if (!isValidPhone(students[idx].phone)) {
                    printf("Invalid phone!\n");
                    continue;
                }
                break;
            }

            // Gender
            printf("Enter gender (1-Male, 0-Female): ");
            int g;
            scanf("%d", &g);
            students[idx].gender = g ? 1 : 0;
            clearInputBuffer();

            saveStudentsToFile();
            printf("Updated successfully!\n");
        }

        printf("Press 0 to go back, any key to continue: ");
        int back;
        if (scanf("%d", &back) == 1 && back == 0) {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }
}

void deleteStudentScreen() {
    while (1) {
        char id[11];
        printf("Enter student ID to delete: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';

        int idx = findStudentIndexById(id);
        if (idx == -1) {
            printf("Student not found!\n");
        } else {
            printf("Are you sure (Y/N)? ");
            char c;
            scanf(" %c", &c);
            clearInputBuffer();
            if (c == 'Y' || c == 'y') {
                for (int i = idx; i < studentCount - 1; i++) {
                    students[i] = students[i + 1];
                }
                studentCount--;
                saveStudentsToFile();
                printf("Deleted successfully!\n");
            }
        }
        printf("Press 0 to go back, any key to continue: ");
        int back;
        if (scanf("%d", &back) == 1 && back == 0) {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }
}

void sortStudentMenu() {
    while (1) {
        printf("1. Sort by ID\n");
        printf("2. Sort by Name\n");
        printf("3. Sort by Class ID\n");
        printf("0. Back\n");
        int c;
        scanf("%d", &c);
        clearInputBuffer();
        if (c == 0) break;

        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = i + 1; j < studentCount; j++) {
                int cmp = 0;
                if (c == 1) cmp = strcmp(students[i].studentId, students[j].studentId);
                else if (c == 2) cmp = strcmp(students[i].name, students[j].name);
                else if (c == 3) cmp = strcmp(students[i].classroomId, students[j].classroomId);

                if (cmp > 0) {
                    struct Student t = students[i];
                    students[i] = students[j];
                    students[j] = t;
                }
            }
        }
        saveStudentsToFile();
        printf("Sorted successfully!\n");
    }
}

void searchStudentByName() {
    char keyword[50];
    printf("Enter name to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, keyword) != NULL) {
            printf("%s | %s | %s\n",
                   students[i].studentId,
                   students[i].name,
                   students[i].email);
        }
    }
    printf("Done searching.\n");
}

void runStudentManager() {
    int c;
    loadStudentsFromFile();
    while (1) {
        printf("\n===== STUDENT MANAGER =====\n");
        printf("1. Add student\n");
        printf("2. Show list\n");
        printf("3. Edit\n");
        printf("4. Delete\n");
        printf("5. Sort\n");
        printf("6. Search\n");
        printf("0. Back\n");

        c = getUserChoice();
        if (c == 1) addStudentScreen();
        else if (c == 2) showStudentListScreen();
        else if (c == 3) editStudentScreen();
        else if (c == 4) deleteStudentScreen();
        else if (c == 5) sortStudentMenu();
        else if (c == 6) searchStudentByName();
        else if (c == 0) break;
    }
}
