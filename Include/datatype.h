#ifndef DATATYPE_H
#define DATATYPE_H
#include <stdbool.h>

#define MAX_STUDENTS 100
#define MAX_CLASSES 50

// 1. Date
struct Date {
    int month, day, year;
};

// 2. Student
struct Student {
    char studentId[11];
    char classroomId[11];
    char name[20];
    struct Date dateOfBirth;
    bool gender;
    char email[30];
    char phone[20];

};

// 3. Classroom
struct Classroom {
    char classroomId[11];
    char teacherId[10];
    char classroomName[10];
    int studentCount;
    char studentIds[MAX_STUDENTS][11];
};

// 4. Teacher
struct Teacher {
    char teacherId[15];
    char classroomId[15];
    char name[20];
    struct Date dateOfBirth;
    bool gender;
    char email[30];
    char phone[20];
    char password[20];
    int classCount;
    char classroomIds[MAX_CLASSES][11];
};

#endif // DATATYPE_H
