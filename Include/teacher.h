#ifndef TEACHER_H
#define TEACHER_H

#include "datatype.h"

// Biến toàn cục
extern struct Teacher teachers[MAX_CLASSES]; // số lượng giáo viên tạm lấy bằng MAX_CLASSES
extern int teacherCount;

// File I/O
void loadTeachersFromFile();
void saveTeachersToFile();

// Màn hình chức năng
void addTeacherScreen();
void showTeacherListScreen();
void editTeacherScreen();
void deleteTeacherScreen();
void sortTeacherMenu();
void searchTeacherByName();

// Hàm tìm kiếm
int findTeacherIndexById(const char* teacherId);

// Hàm chạy menu giáo viên
void runTeacherManager();

#endif
