#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Include/datatype.h"
#include "../Include/function.h"
#include "../Include/classroom.h"

#define CLASSROOM_FILE_PATH "Data/classroom.bin"

struct Classroom classes[MAX_CLASSES];
int classCount = 0;

// ===== File I/O =====
void loadClassesFromFile() {
    FILE *f = fopen(CLASSROOM_FILE_PATH, "rb");
    if (!f) {
        classCount = 0;
        return;
    }
    fread(&classCount, sizeof(int), 1, f);
    fread(classes, sizeof(struct Classroom), classCount, f);
    fclose(f);
}

void saveClassesToFile() {
    FILE *f = fopen(CLASSROOM_FILE_PATH, "wb");
    if (!f) {
        printf("Cannot open file to save classroom data!\n");
        return;
    }
    fwrite(&classCount, sizeof(int), 1, f);
    fwrite(classes, sizeof(struct Classroom), classCount, f);
    fclose(f);
}

// ===== Tìm lớp theo ID =====
int findClassroomIndexById(const char* classId) {
    for (int i = 0; i < classCount; i++) {
        if (strcmp(classes[i].classroomId, classId) == 0)
            return i;
    }
    return -1;
}

// ===== Thêm lớp học =====
void addClassroomScreen() {
    while (1) {
        struct Classroom c;

        // Classroom ID
        while (1) {
            printf("Enter class ID (exactly 9 characters): ");
            fgets(c.classroomId, sizeof(c.classroomId), stdin);
            c.classroomId[strcspn(c.classroomId, "\n")] = '\0';
            if (strlen(c.classroomId) != 9) {
                printf("Invalid class ID length!\n");
                continue;
            }
            if (findClassroomIndexById(c.classroomId) != -1) {
                printf("Class ID already exists!\n");
                continue;
            }
            break;
        }

        // Class name
        while (1) {
            printf("Enter class name: ");
            fgets(c.classroomName, sizeof(c.classroomName), stdin);
            c.classroomName[strcspn(c.classroomName, "\n")] = '\0';
            if (strlen(c.classroomName) == 0) {
                printf("Class name cannot be empty!\n");
                continue;
            }
            capitalizeName(c.classroomName);
            break;
        }

        // Teacher ID
        printf("Enter teacher ID: ");
        fgets(c.teacherId, sizeof(c.teacherId), stdin);
        c.teacherId[strcspn(c.teacherId, "\n")] = '\0';

        // Student count ban đầu = 0
        c.studentCount = 0;

        // Thêm vào mảng
        classes[classCount++] = c;
        saveClassesToFile();
        printf("Classroom added successfully!\n");

        printf("Press 0 to return, any key to add more: ");
        int back;
        if (scanf("%d", &back) == 1 && back == 0) {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }
}

// ===== Hiển thị danh sách lớp học =====
void showClassroomListScreen() {
    if (classCount == 0) {
        printf("No classrooms available.\n");
        return;
    }
    printf("+-----------+----------------------+--------------+\n");
    printf("| Class ID  | Class Name           | Teacher ID   |\n");
    printf("+-----------+----------------------+--------------+\n");
    for (int i = 0; i < classCount; i++) {
        printf("| %-9s | %-20s | %-12s |\n",
               classes[i].classroomId,
               classes[i].classroomName,
               classes[i].teacherId);
    }
    printf("+-----------+----------------------+--------------+\n");
}

// ===== Sửa lớp học =====
void editClassroomScreen() {
    char id[10];
    printf("Enter class ID to edit: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findClassroomIndexById(id);
    if (index == -1) {
        printf("Class not found.\n");
        return;
    }

    // Name
    printf("Enter new class name: ");
    fgets(classes[index].classroomName, sizeof(classes[index].classroomName), stdin);
    classes[index].classroomName[strcspn(classes[index].classroomName, "\n")] = '\0';
    capitalizeName(classes[index].classroomName);

    // Teacher ID
    printf("Enter new teacher ID: ");
    fgets(classes[index].teacherId, sizeof(classes[index].teacherId), stdin);
    classes[index].teacherId[strcspn(classes[index].teacherId, "\n")] = '\0';

    saveClassesToFile();
    printf("Classroom updated successfully!\n");
}

// ===== Xóa lớp học =====
void deleteClassroomScreen() {
    char id[10];
    printf("Enter class ID to delete: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findClassroomIndexById(id);
    if (index == -1) {
        printf("Class not found.\n");
        return;
    }

    for (int i = index; i < classCount - 1; i++) {
        classes[i] = classes[i + 1];
    }
    classCount--;
    saveClassesToFile();
    printf("Classroom deleted successfully!\n");
}

// ===== Menu sắp xếp =====
void sortClassroomMenu() {
    printf("Sorting classrooms - (not implemented yet)\n");
}

// ===== Tìm kiếm theo tên =====
void searchClassroomByName() {
    printf("Searching classrooms - (not implemented yet)\n");
}

// ===== Chạy menu quản lý lớp học =====
void runClassroomManager() {
    int choice;
    loadClassesFromFile();
    while (1) {
        printf("\n==== CLASSROOM MANAGER ====\n");
        printf("1. Add classroom\n");
        printf("2. Show classroom list\n");
        printf("3. Edit classroom\n");
        printf("4. Delete classroom\n");
        printf("5. Sort classrooms\n");
        printf("6. Search classroom by name\n");
        printf("0. Back to main menu\n");
        choice = getUserChoice();

        if (choice == 1) addClassroomScreen();
        else if (choice == 2) showClassroomListScreen();
        else if (choice == 3) editClassroomScreen();
        else if (choice == 4) deleteClassroomScreen();
        else if (choice == 5) sortClassroomMenu();
        else if (choice == 6) searchClassroomByName();
        else if (choice == 0) break;
        else printf("Invalid choice.\n");
    }
}
