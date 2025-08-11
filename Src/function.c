#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../Include/datatype.h"
#include "../Include/function.h"
#include "../Include/student.h"
#include "../Include/teacher.h"
#include "../Include/classroom.h"

// ===== Hiển thị tiêu đề hệ thống =====
void showSystemTitle() {
    printf("\n=====================================\n");
    printf("        STUDENT MANAGER    \n");
    printf("=====================================\n");
}

// ===== Menu chính của chương trình =====
void showManagerMenu() {
    printf("\n========= MAIN MENU =========\n");
    printf("1. Student Manager\n");
    printf("2. Teacher Manager\n");
    printf("3. Classroom Manager\n");
    printf("0. EXIT\n");
    printf("==============================\n");
}

// ===== Xóa bộ đệm nhập =====
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ===== Lấy lựa chọn từ người dùng =====
int getUserChoice() {
    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

// ===== Kiểm tra định dạng email =====
int isValidEmail(const char* email) {
    const char* at = strchr(email, '@');
    const char* dot = strrchr(email, '.');
    return at && dot && at < dot && at != email && dot[1] != '\0';
}

// ===== Kiểm tra số điện thoại =====
int isValidPhone(const char* phone) {
    int len = strlen(phone);
    if (len < 10 || len > 11) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

// ===== Kiểm tra ngày sinh hợp lệ =====
int isValidDateOfBirth(int day, int month, int year) {
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    if (year > now->tm_year + 1900) return 0;
    if (year == now->tm_year + 1900) {
        if (month > now->tm_mon + 1) return 0;
        if (month == now->tm_mon + 1 && day > now->tm_mday) return 0;
    }
    if (month < 1 || month > 12 || day < 1 || day > 31) return 0;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;
    if (month == 2) {
        int leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 28 + leap) return 0;
    }
    return 1;
}

// ===== Viết hoa chữ cái đầu mỗi từ =====
void capitalizeName(char* name) {
    int len = strlen(name);
    int newWord = 1;
    for (int i = 0; i < len; i++) {
        if (isalpha(name[i])) {
            if (newWord) {
                name[i] = toupper(name[i]);
                newWord = 0;
            } else {
                name[i] = tolower(name[i]);
            }
        } else {
            newWord = 1;
        }
    }
}

// ===== Hàm chạy menu tổng =====
void runManagerMenu() {
    int choice;
    showSystemTitle();
    while (1) {
        showManagerMenu();
        choice = getUserChoice();

        if (choice == 1) {
            runStudentManager();
        }
        else if (choice == 2) {
            runTeacherManager();
        }
        else if (choice == 3) {
            runClassroomManager();
        }
        else if (choice == 0) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}
