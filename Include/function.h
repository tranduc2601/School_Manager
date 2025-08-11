#ifndef FUNCTION_H
#define FUNCTION_H

void showSystemTitle();
void showManagerMenu();
void clearInputBuffer();
int getUserChoice();
int isValidEmail(const char* email);
int isValidPhone(const char* phone);
int isValidDateOfBirth(int day, int month, int year);
void capitalizeName(char* name);
void runManagerMenu();

// Các prototype của các module khác
void runStudentManager();
void runTeacherManager();
void runClassroomManager();

#endif
