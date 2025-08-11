#ifndef STUDENT_H
#define STUDENT_H

#include "datatype.h"

extern struct Student students[];
extern int studentCount;

void loadStudentsFromFile();
void saveStudentsToFile();

void addStudentScreen();
void showStudentListScreen();
int  findStudentIndexById(const char* studentId);
void editStudentScreen();
void deleteStudentScreen();
void sortStudentMenu();
void searchStudentByName();

void runStudentManager();

#endif
