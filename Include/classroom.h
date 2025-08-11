//
// Created by 2601m on 09/08/2025.
//

#ifndef CLASSROOM_H
#define CLASSROOM_H

#endif //CLASSROOM_H
#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "datatype.h"

// Biến toàn cục
extern struct Classroom classes[MAX_CLASSES];
extern int classCount;

// File I/O
void loadClassesFromFile();
void saveClassesToFile();

// Màn hình chức năng
void addClassroomScreen();
void showClassroomListScreen();
void editClassroomScreen();
void deleteClassroomScreen();
void sortClassroomMenu();
void searchClassroomByName();

// Hàm tìm kiếm
int findClassroomIndexById(const char* classId);

// Hàm chạy menu lớp học
void runClassroomManager();

#endif
