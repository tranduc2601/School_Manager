#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Include/datatype.h"
#include "../Include/function.h"
#include "../Include/teacher.h"

#define TEACHER_FILE_PATH "Data/teacher.bin"

struct Teacher teachers[MAX_CLASSES];
int teacherCount = 0;

// ===== File I/O =====
void loadTeachersFromFile() {
    FILE *f = fopen(TEACHER_FILE_PATH, "rb");
    if (!f) {
        teacherCount = 0;
        return;
    }
    fread(&teacherCount, sizeof(int), 1, f);
    fread(teachers, sizeof(struct Teacher), teacherCount, f);
    fclose(f);
}

void saveTeachersToFile() {
    FILE *f = fopen(TEACHER_FILE_PATH, "wb");
    if (!f) {
        printf("Cannot open file to save teacher data!\n");
        return;
    }
    fwrite(&teacherCount, sizeof(int), 1, f);
    fwrite(teachers, sizeof(struct Teacher), teacherCount, f);
    fclose(f);
}

// ===== Tìm giáo viên theo ID =====
int findTeacherIndexById(const char* teacherId) {
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].teacherId, teacherId) == 0)
            return i;
    }
    return -1;
}

// ===== Thêm giáo viên =====
void addTeacherScreen() {
    while (1) {
        struct Teacher t;

        // Teacher ID
        while (1) {
            printf("Enter teacher ID (max 14 chars): ");
            fgets(t.teacherId, sizeof(t.teacherId), stdin);
            t.teacherId[strcspn(t.teacherId, "\n")] = '\0';
            if (strlen(t.teacherId) == 0 || strlen(t.teacherId) > 14) {
                printf("Invalid teacher ID!\n");
                continue;
            }
            if (findTeacherIndexById(t.teacherId) != -1) {
                printf("Teacher ID already exists!\n");
                continue;
            }
            break;
        }

        // Classroom ID
        printf("Enter classroom ID: ");
        fgets(t.classroomId, sizeof(t.classroomId), stdin);
        t.classroomId[strcspn(t.classroomId, "\n")] = '\0';

        // Name
        while (1) {
            printf("Enter teacher name: ");
            fgets(t.name, sizeof(t.name), stdin);
            t.name[strcspn(t.name, "\n")] = '\0';
            if (strlen(t.name) == 0) {
                printf("Name cannot be empty!\n");
                continue;
            }
            capitalizeName(t.name);
            break;
        }

        // Date of birth
        while (1) {
            printf("Enter date of birth (dd mm yyyy): ");
            if (scanf("%d %d %d", &t.dateOfBirth.day, &t.dateOfBirth.month, &t.dateOfBirth.year) != 3) {
                printf("Invalid format!\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();
            if (!isValidDateOfBirth(t.dateOfBirth.day, t.dateOfBirth.month, t.dateOfBirth.year)) {
                printf("Invalid date!\n");
                continue;
            }
            break;
        }

        // Gender
        printf("Enter gender (1-Male, 0-Female): ");
        int genderInput;
        scanf("%d", &genderInput);
        clearInputBuffer();
        t.gender = genderInput ? 1 : 0;

        // Email
        while (1) {
            printf("Enter email: ");
            fgets(t.email, sizeof(t.email), stdin);
            t.email[strcspn(t.email, "\n")] = '\0';
            if (!isValidEmail(t.email)) {
                printf("Invalid email!\n");
                continue;
            }
            break;
        }

        // Phone
        while (1) {
            printf("Enter phone: ");
            fgets(t.phone, sizeof(t.phone), stdin);
            t.phone[strcspn(t.phone, "\n")] = '\0';
            if (!isValidPhone(t.phone)) {
                printf("Invalid phone!\n");
                continue;
            }
            break;
        }

        // Password
        printf("Enter password: ");
        fgets(t.password, sizeof(t.password), stdin);
        t.password[strcspn(t.password, "\n")] = '\0';

        // Class count (ban đầu = 0)
        t.classCount = 0;

        // Thêm vào mảng
        teachers[teacherCount++] = t;
        saveTeachersToFile();
        printf("Teacher added successfully!\n");

        printf("Press 0 to return, any key to add more: ");
        int back;
        if (scanf("%d", &back) == 1 && back == 0) {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }
}

// ===== Hiển thị danh sách giáo viên =====
void showTeacherListScreen() {
    if (teacherCount == 0) {
        printf("No teachers available.\n");
        return;
    }
    printf("+---------------+---------------+--------------------+--------------------+--------------+\n");
    printf("| Teacher ID    | Classroom ID  | Name               | Email              | Phone        |\n");
    printf("+---------------+---------------+--------------------+--------------------+--------------+\n");
    for (int i = 0; i < teacherCount; i++) {
        printf("| %-13s | %-13s | %-18s | %-18s | %-12s |\n",
               teachers[i].teacherId,
               teachers[i].classroomId,
               teachers[i].name,
               teachers[i].email,
               teachers[i].phone);
    }
    printf("+---------------+---------------+--------------------+--------------------+--------------+\n");
}

// ===== Sửa giáo viên =====
void editTeacherScreen() {
    char id[15];
    printf("Enter teacher ID to edit: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findTeacherIndexById(id);
    if (index == -1) {
        printf("Teacher not found.\n");
        return;
    }

    printf("Editing teacher: %s\n", teachers[index].name);

    // Name
    printf("Enter new name: ");
    fgets(teachers[index].name, sizeof(teachers[index].name), stdin);
    teachers[index].name[strcspn(teachers[index].name, "\n")] = '\0';
    capitalizeName(teachers[index].name);

    // Email
    while (1) {
        printf("Enter new email: ");
        fgets(teachers[index].email, sizeof(teachers[index].email), stdin);
        teachers[index].email[strcspn(teachers[index].email, "\n")] = '\0';
        if (!isValidEmail(teachers[index].email)) {
            printf("Invalid email!\n");
            continue;
        }
        break;
    }

    // Phone
    while (1) {
        printf("Enter new phone: ");
        fgets(teachers[index].phone, sizeof(teachers[index].phone), stdin);
        teachers[index].phone[strcspn(teachers[index].phone, "\n")] = '\0';
        if (!isValidPhone(teachers[index].phone)) {
            printf("Invalid phone!\n");
            continue;
        }
        break;
    }

    saveTeachersToFile();
    printf("Teacher updated successfully!\n");
}

// ===== Xóa giáo viên =====
void deleteTeacherScreen() {
    char id[15];
    printf("Enter teacher ID to delete: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findTeacherIndexById(id);
    if (index == -1) {
        printf("Teacher not found.\n");
        return;
    }

    for (int i = index; i < teacherCount - 1; i++) {
        teachers[i] = teachers[i + 1];
    }
    teacherCount--;
    saveTeachersToFile();
    printf("Teacher deleted successfully!\n");
}

// ===== Menu sắp xếp =====
void sortTeacherMenu() {
    printf("Sorting teachers - (not implemented yet)\n");
}

// ===== Tìm kiếm theo tên =====
void searchTeacherByName() {
    printf("Searching teachers - (not implemented yet)\n");
}

// ===== Chạy menu quản lý giáo viên =====
void runTeacherManager() {
    int choice;
    loadTeachersFromFile();
    while (1) {
        printf("\n==== TEACHER MANAGER ====\n");
        printf("1. Add teacher\n");
        printf("2. Show teacher list\n");
        printf("3. Edit teacher\n");
        printf("4. Delete teacher\n");
        printf("5. Sort teachers\n");
        printf("6. Search teacher by name\n");
        printf("0. Back to main menu\n");
        choice = getUserChoice();

        if (choice == 1) addTeacherScreen();
        else if (choice == 2) showTeacherListScreen();
        else if (choice == 3) editTeacherScreen();
        else if (choice == 4) deleteTeacherScreen();
        else if (choice == 5) sortTeacherMenu();
        else if (choice == 6) searchTeacherByName();
        else if (choice == 0) break;
        else printf("Invalid choice.\n");
    }
}
