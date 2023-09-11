//Include library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)


//Define constant	
#define EXIT "999"
#define MAX_COURSES 21
#define GRADUATE_CREDIT_HOUR 21

//Variable declaration
int totalNumOfStudent = 4, currentStudent = 0, currentCourse = 0, logInStatus = 0, adminLogInStatus = 0;

//Array declaration
char grades[][3] = { "A","A-","B+","B","B-","C+","C","F" };
double gradePoints[8] = { 4.00,3.75,3.50,3.25,3.00,2.50,2.00,0.00 };
char admin[][30] = { "Lim Kah Lok","L0001","Chan Choon Kit","L0002","Tan Bee Sian","L0003","Lee Soo Lin", "L0004", "Tan Lai Kien", "L0005" };

//Structure declaration
struct courseDetail {
	char courseCode[9];
	int creditHour;
	int semesterSession;
	char grade[3];
	double gradePoint;
	double quantityPoint;
};

struct studentDetail {
	char name[30];
	char id[10];
	char ic[18];
	int currentSemesterSession;
	int numOfCourse;
	int totalCreditHour;
	double totalQuantityPoint;
	double gpa[3];
	double cgpa;
	struct courseDetail course[MAX_COURSES];
};

//Create sample student data
struct studentDetail student[] = {
	[0] = { "Tan Yi Jia", "KPKL0001", "040101010101", 3, 6, 21, 65.00, {3.57,3.00,2.71}, 3.10,
	{
		{"AAA1003", 3, 1, "A", 4.00, 12.00},
		{"AAA1014", 4, 1, "B", 3.25, 13.00},
		{"ABA1003", 3, 2, "C", 2.00, 6.00},
		{"ABA1014", 4, 2, "A-", 3.75, 15.00},
		{"ACA1003", 3, 3, "B-", 3.00, 9.00},
		{"ACA1014", 4, 3, "C+", 2.50, 10.00}
	}
	},
	[1] = { "Lee Lap Yhin", "KPKL0002", "040202020202", 3, 6, 21, 0, {0,0,0}, 0,
	{
		{"AAA1001", 3, 1},
		{"AAA1002", 4, 1},
		{"AAA2001", 3, 2},
		{"AAA2002", 4, 2},
		{"AAA3001", 3, 3},
		{"AAA3002", 4, 3}
	}
	},
	[2] = {"Ng Zhe Wei", "KPKL0003", "050303030303", 2},
	[3] = {"Tan Zhong Yan", "KPKL0004", "020404040404", 1}
};

//Function prototype
void administratorMode();
void adminSignIn();
void adminSignInStudent();
void studentList();
void adminMenu();
void signUp();
void getStudentName();
void getStudentId();
void getStudentIc();
void getCurrentSemesterSession();
void signUpSucess();
void addNewCourse();
void getCourseCode();
void getCreditHour();
void getSemesterSession();
void getGrade();
void convertGradeToGradePoint();
void calculateQuantityPoint();
void editCourseDetail();
int chooseCourse();
void chooseDetail();
void viewResult();
void calculateGpa();
void calculateCgpa();

void studentMode();
int logIn();
void logOut();
void logo();
void bye();

void main() {
	//variable declaration
	int choice;
	system("COLOR F0");
	logo();
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*              WELCOME TO             *\n");
	printf("*           CGPA CALCULATOR !         *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	Sleep(1000);
	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*           CGPA CALCULATOR           *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*       [1] Administrator Mode        *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*       [2] Student Mode              *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*      [999] Exit                     *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%d", &choice);
		if (choice == 1) {
			administratorMode();
		}
		else if (choice == 2) {
			studentMode();
		}
		else if (choice == 999) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*              Thank You!             *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
			bye();
			logo();
			printf("\n* * * * * * * * * * * * * * * * * * * *\n");
			printf("*             System Close!           *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			break;
		}
		else {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*           Invalid choice!           *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
	} while (choice != 999);

	system("pause");
}

void administratorMode() {
	int choice;
	adminSignIn();
	if (adminLogInStatus == 1) {
		do {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*         ADMINISTRATOR MODE          *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*       [1] Sign in for student       *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*       [2] Sign up for student       *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*       [3] Show Student List         *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*      [999] Exit                     *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf(" > ");
			rewind(stdin);
			scanf("%d", &choice);
			if (choice == 1) {
				adminSignInStudent();
				if (logInStatus == 1) {
					adminMenu();
				}
			}
			else if (choice == 2) {
				signUp();
			}
			else if (choice == 3) {
				studentList();
			}
			else if (choice == 999) {
				adminLogInStatus = 0;
				system("cls");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				printf("*              Thank You!             *\n");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				Sleep(1000);
			}
			else {
				system("cls");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				printf("*           Invalid choice!           *\n");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				Sleep(1000);
			}
		} while (choice != 999);
	}
}

void adminSignIn() {
	char lectureId[10];
	int temp;

	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*            ADMIN SIGN IN            *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*          Input: Lecture ID          *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              Ex. L0001              *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              Exit [999]             *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%s", &lectureId);

		for (temp = 1; temp <= 9; temp += 2) {
			if (strcmp(lectureId, admin[temp]) == 0) {
				adminLogInStatus = 1;
				break;
			}
		}
		if ( strcmp(lectureId,"999")==0) {
			break;
		}
		if (adminLogInStatus == 0) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*         Invalid lecture ID!         *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
		else {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("* Welcome %-20s        *\n", admin[temp - 1]);
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
	} while (adminLogInStatus != 1);
}


void adminSignInStudent() {
	char studentId[10], temp;
	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*             SIGN IN MENU            *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*          Input: Student ID          *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              Exit [999]             *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%s", studentId);
		for (temp = 0; temp < totalNumOfStudent; temp++) {
			if (strcmp(studentId, student[temp].id) == 0) {
				currentStudent = temp;
				logInStatus = 1;
				break;
			}
		}
		if (strcmp(studentId, EXIT) == 0) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*              Thank You!             *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
		else if (temp == totalNumOfStudent) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*         Invalid Student ID.         *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}

		else
			break;
	} while (strcmp(studentId, EXIT) != 0);
}

void studentList() {
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*    Student Name     * Student ID*    Student IC   *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	for (int temp = 0; temp < totalNumOfStudent; temp++) {
		printf("*%-20s * %-10s* %-15s *\n", student[temp].name, student[temp].id, student[temp].ic);
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

	}
	system("pause");
}

void adminMenu() {
	int choice;
	do {
		system("cls");
		printf("    Student Name: %s\n", student[currentStudent].name);
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*      [1]  Add New Course            *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*      [2]  Edit Course Detail        *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*      [3]  Get Result                *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*     [999] Sign Out                  *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			addNewCourse();
			break;
		case 2:
			if (student[currentStudent].numOfCourse > 0) {
				editCourseDetail();
			}
			else {
				system("cls");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				printf("*          No course to edit!         *\n");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				Sleep(1000);
			}
			break;

		case 3:
			if (student[currentStudent].numOfCourse > 0) {
				viewResult();
			}
			else {
				system("cls");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				printf("*             No Result!              *\n");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				Sleep(1000);
			}

			break;
		case 999:
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*             Signed Out!             *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
			break;
		default:
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*           No This Choice!           *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
	} while (choice != 999);
}

void signUp() {
	getStudentName();
	getStudentId();
	getStudentIc();
	getCurrentSemesterSession();
	signUpSucess();
	totalNumOfStudent++;
}

void getStudentName() {
	//input: Student Name
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*              SIGN UP MENU           *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*          Input: Student Name        *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*                Ex.Edwin             *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	rewind(stdin);
	gets(student[totalNumOfStudent].name);
}

void getStudentId() {
	//input: student ID
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*             SIGN UP MENU            *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*          Input: Student ID          *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*              Ex.KPKL0001            *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	rewind(stdin);
	scanf("%s", student[totalNumOfStudent].id);
}

void getStudentIc() {
	//input: Student IC
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*             SIGN UP MENU            *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*          Input: Student IC          *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*           Ex.050730101125           *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	rewind(stdin);
	scanf("%s", student[totalNumOfStudent].ic);
}

void getCurrentSemesterSession() {
	//input: Current Semester Session
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*             SIGN UP MENU            *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*   Input: Student Current Semester   *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*                 Ex.2                *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	rewind(stdin);
	scanf("%d", &student[totalNumOfStudent].currentSemesterSession);
}

void signUpSucess() {
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*           Sign Up Sucess!           *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	Sleep(1000);
}

void addNewCourse() {
	currentCourse = student[currentStudent].numOfCourse;
	getCourseCode();
	getCreditHour();
	getSemesterSession();
	getGrade();
	convertGradeToGradePoint();
	calculateQuantityPoint();
	student[currentStudent].numOfCourse++;
	calculateGpa();
	calculateCgpa();
}

void getCourseCode() {
	//input: course code
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*            ADD NEW COURSE           *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*          Input: Course Code         *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*              Ex.AACS001             *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	rewind(stdin);
	scanf("%s", student[currentStudent].course[currentCourse].courseCode);
}

void getCreditHour() {
	//input: credit hour
	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*            ADD NEW COURSE           *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*         Input: Credit Hour          *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*                 Ex.3                *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%d", &student[currentStudent].course[currentCourse].creditHour);
		if (student[currentStudent].course[currentCourse].creditHour <= 0) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*         Invalid Credit Hour!        *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*    Credit Hour must more than 0 !   *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
	} while (student[currentStudent].course[currentCourse].creditHour <= 0);

}

void getSemesterSession() {
	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*            ADD NEW COURSE           *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*      Input: Semester of Course      *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*                 Ex.2                *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%d", &student[currentStudent].course[currentCourse].semesterSession);
		if (student[currentStudent].course[currentCourse].semesterSession > student[currentStudent].currentSemesterSession || student[currentStudent].course[currentCourse].semesterSession <=0) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*          Invalid Semester  !        *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf(">> %s is currently in semester %d <<\n", student[currentStudent].name, student[currentStudent].currentSemesterSession);
			Sleep(1000);
		}
	} while (student[currentStudent].course[currentCourse].semesterSession > student[currentStudent].currentSemesterSession || student[currentStudent].course[currentCourse].semesterSession <= 0);

}

void getGrade() {
	//local variable for temporary use
	int temp;
	//loop to avoid invalid input
	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*            ADD NEW COURSE           *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*             Input: Grade            *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*                 Ex.A                *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");

		printf(" > ");
		rewind(stdin);
		scanf("%s", student[currentStudent].course[currentCourse].grade);
		//convert the first letter to capital letter to avoid error
		student[currentStudent].course[currentCourse].grade[0] = toupper(student[currentStudent].course[currentCourse].grade[0]);
		for (temp = 0; temp < 8; temp++) {
			if (strcmp(grades[temp], student[currentStudent].course[currentCourse].grade) == 0) {
				break;
			}
		}
		if (temp == 8) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*            Invalid Grade            *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
		else {
			break;
		}
	} while (1);
}

void convertGradeToGradePoint() {
	//get the grade point according to the index
	for (int temp = 0; temp < 8; temp++) {
		if (strcmp(student[currentStudent].course[currentCourse].grade, grades[temp]) == 0) {
			student[currentStudent].course[currentCourse].gradePoint = gradePoints[temp];
		}
	}
}

void calculateQuantityPoint() {
	//Formula: Grade point * Credit hour
	student[currentStudent].course[currentCourse].quantityPoint = student[currentStudent].course[currentCourse].gradePoint * student[currentStudent].course[currentCourse].creditHour;
}

void editCourseDetail() {
	do {
		currentCourse = chooseCourse();
		if (currentCourse != 999) {
			chooseDetail();
		}
	} while (currentCourse != 999);
}

int chooseCourse() {
	//local variable for choice
	int choice;
	do {
		//print the list of courses
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("* No. *  Course * Credit*  Sem  Grade\n");
		printf("*     *         *  Hour *       *     *\n");
		for (int temp = 0; temp < student[currentStudent].numOfCourse; temp++) {
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*  %-2d * %-8s*   %-2d  *   %-2d  *  %-2s *\n", temp + 1, student[currentStudent].course[temp].courseCode, student[currentStudent].course[temp].creditHour, student[currentStudent].course[temp].semesterSession, student[currentStudent].course[temp].grade);
		}
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              Exit [999]             *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("No. of Course to edit\t> ");
		rewind(stdin);
		scanf("%d", &choice);
		if (choice == 999) {
			break;
		}
		else if (choice > student[currentStudent].numOfCourse) {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*           Invalid Choice!           *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
	} while (choice != 999 && choice > student[currentStudent].numOfCourse);
	return (choice == 999 ? choice : --choice);
}

void chooseDetail() {
	//local variable for choice
	int choice;
	do {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              EDIT MENU              *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*         [1]  Course Code            *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*         [2]  Credit Hour            *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*         [3]  Semester Session       *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*         [4]  Grade                  *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*        [999] Exit                   *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf(" > ");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			getCourseCode();
			break;
		case 2:
			getCreditHour();
			break;
		case 3:
			getSemesterSession();
			break;
		case 4:
			getGrade();
			convertGradeToGradePoint();
			break;
		case 999:
			break;
		default:
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*           Invalid Choice!           *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
		}
	} while (choice != 999);
	calculateQuantityPoint();
	calculateGpa();
	calculateCgpa();
}

void viewResult() {
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*                         RESULT                          *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* Student Name                        * %-17s *\n", student[currentStudent].name);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* Student ID                          * %-17s *\n", student[currentStudent].id);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* Number of Courses                   * %-17d *\n", student[currentStudent].numOfCourse);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* Current Semester Session            * %-17d *\n", student[currentStudent].currentSemesterSession);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*                         RESULT                          *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*     Course Code     * Credit Hour *  Semester *  Grade  *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	for (int temp = 0; temp < student[currentStudent].numOfCourse; temp++) {
		switch (student[currentStudent].course[temp].semesterSession) {
		case 1:
			printf("*       %-13s *      %-2d     *     %-2d    *    %-2s   *\n", student[currentStudent].course[temp].courseCode, student[currentStudent].course[temp].creditHour, student[currentStudent].course[temp].semesterSession, student[currentStudent].course[temp].grade);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			break;
		case 2:
			printf("*       %-13s *      %-2d     *     %-2d    *    %-2s   *\n", student[currentStudent].course[temp].courseCode, student[currentStudent].course[temp].creditHour, student[currentStudent].course[temp].semesterSession, student[currentStudent].course[temp].grade);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			break;
		case 3:
			printf("*       %-13s *      %-2d     *     %-2d    *    %-2s   *\n", student[currentStudent].course[temp].courseCode, student[currentStudent].course[temp].creditHour, student[currentStudent].course[temp].semesterSession, student[currentStudent].course[temp].grade);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			break;
		}
	}
	system("pause");
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*                         RESULT                          *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	for (int temp = 1; temp <= student[currentStudent].currentSemesterSession; temp++) {
		printf("* GPA Sem %d                           * %-17.2lf *\n", temp, student[currentStudent].gpa[temp - 1]);
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	}
	printf("* CGPA                                * %-17.2lf *\n", student[currentStudent].cgpa);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
	if (student[currentStudent].totalCreditHour >= GRADUATE_CREDIT_HOUR && student[currentStudent].cgpa >= 2.00) {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*           GRADUATE STATUS           *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*               VALID!                *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
	}
	else {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*           GRADUATE STATUS           *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*             NOT VALID!              *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
	}
	system("pause");
}

void calculateGpa() {
	//local variable to calculate gpa
	int creditHour[MAX_COURSES], semesterSession[MAX_COURSES], totalCreditHour[3] = { 0,0,0 };
	double quantityPoint[MAX_COURSES], totalQuantityPoint[3] = { 0,0,0 };

	//push all value into array for easier calculation
	for (int temp = 0; temp < student[currentStudent].numOfCourse; temp++) {
		if (student[currentStudent].course[temp].quantityPoint == 0) {
			continue;
		}
		else {
			semesterSession[temp] = student[currentStudent].course[temp].semesterSession;
			quantityPoint[temp] = student[currentStudent].course[temp].quantityPoint;
			creditHour[temp] = student[currentStudent].course[temp].creditHour;
		}
	}

	//according to the semester session calculate gpa
	for (int temp = 0; temp < student[currentStudent].numOfCourse; temp++) {
		if (totalQuantityPoint)
			switch (semesterSession[temp]) {
			case 1:
				totalQuantityPoint[0] += quantityPoint[temp];
				totalCreditHour[0] += creditHour[temp];
				break;
			case 2:
				totalQuantityPoint[1] += quantityPoint[temp];
				totalCreditHour[1] += creditHour[temp];
				break;
			case 3:
				totalQuantityPoint[2] += quantityPoint[temp];
				totalCreditHour[2] += creditHour[temp];
				break;
			}
	}
	for (int temp = 0; temp < 3; temp++) {
		if (totalCreditHour[temp] != 0) {
			student[currentStudent].gpa[temp] = totalQuantityPoint[temp] / (double)totalCreditHour[temp];
		}
	}
}


void calculateCgpa() {
	//initialize the value of total quantity point and total credit hour
	student[currentStudent].totalQuantityPoint = 0, student[currentStudent].totalCreditHour = 0;
	for (int temp = 0; temp < student[currentStudent].numOfCourse; temp++) {
		if (student[currentStudent].course[temp].quantityPoint == 0) {
			continue;
		}
		else {
			//calculate total quantity point and total credit hour
			student[currentStudent].totalQuantityPoint += student[currentStudent].course[temp].quantityPoint;
			student[currentStudent].totalCreditHour += student[currentStudent].course[temp].creditHour;
		}

	}
	//Formula for calculate cgpa: total quantity point / total credit Hour
	student[currentStudent].cgpa = student[currentStudent].totalQuantityPoint / student[currentStudent].totalCreditHour;
}

void studentMode() {
	//local variable for choice
	int choice;
	logIn();
	if (logInStatus == 1) {
		do {
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("* Student Name: %-20s  *\n", student[currentStudent].name);
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*       [1] View Result               *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*      [999] Exit                     *\n");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf(" > ");
			scanf("%d", &choice);
			if (choice == 1) {
				if (student[currentStudent].numOfCourse > 0) {
					viewResult();
				}
				else {
					system("cls");
					printf("* * * * * * * * * * * * * * * * * * * *\n");
					printf("*             No Result!              *\n");
					printf("* * * * * * * * * * * * * * * * * * * *\n");
					Sleep(1000);
				}

			}
			else if (choice == 999) {
				logOut();
				break;
			}
			else {
				system("cls");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				printf("*           Invalid Choice!           *\n");
				printf("* * * * * * * * * * * * * * * * * * * *\n");
				Sleep(1000);
			}
		} while (choice != 999);
	}
}

int logIn() {
	//local variable for loop and validation
	int temp;
	char studentId[10], studentIc[18];
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*            STUDENT LOG IN           *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*          Input: Student ID          *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*             Ex.KPKL00001            *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*              Exit [999]             *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	rewind(stdin);
	scanf("%s", studentId);
	if (strcmp(studentId, "999") == 0) {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              Thank You!             *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		Sleep(1000);
		return 0;
	}

	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*            STUDENT LOG IN           *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*               Input: IC             *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*            Ex.040101010101          *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf("*              Exit [999]             *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n");
	printf(" > ");
	scanf("%s", studentIc);
	if (strcmp(studentIc, "999") == 0) {
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*              Thank You!             *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		Sleep(1000);
		return 0;
	}

	for (temp = 0; temp < totalNumOfStudent; temp++) {
		if (strcmp(student[temp].id, studentId) == 0 && (strcmp(student[temp].ic, studentIc) == 0)) {
			logInStatus = 1;
			currentStudent = temp;
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			printf("*      Hello, %-20s    *\n", student[temp].name);
			printf("* * * * * * * * * * * * * * * * * * * *\n");
			Sleep(1000);
			break;
		}
	}
	if (temp == totalNumOfStudent) {
		logInStatus = 0;
		system("cls");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		printf("*      Invalid Student ID or IC!      *\n");
		printf("* * * * * * * * * * * * * * * * * * * *\n");
		Sleep(1000);
	}
	return 0;
}

void logOut() {
	//invalid student
	currentStudent = -999;
}

void logo() {
	//icon
	system("cls");
	printf("          ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,            \n");
	printf("        @@@@@@&                             @@,            \n");
	printf("     *@@@   @@&                             @@,            \n");
	printf("   @@@@     @@&                             @@,            \n");
	printf(" @@@@@@@@@@@@@%%    @&                       @@,            \n");
	printf(" @@@            .@@@                        @@,            \n");
	printf(" @@@   @@@    @@@@                          @@,            \n");
	printf(" @@@    %%@@@@@@       *@@@@@@@@@@@@@@@@@@   @@,    @@@@    \n");
	printf(" @@@       @@                               @@,  .@@@ @@@@@\n");
	printf(" @@@                                        @@, @@@@@   @@@\n");
	printf(" @@@             @@@@                       @@,@@@  @@@@@@ \n");
	printf(" @@@   @@      @@@%%                         @@@@     @@@   \n");
	printf(" @@@    @@@(@@@@      (@@@@@@@@@@@@@@@@@@   @@@     @@@    \n");
	printf(" @@@      @@@(                            @@@     @@@      \n");
	printf(" @@@                                     @@@@,   @@@       \n");
	printf(" @@@              @@@                    @@ #@@@@@         \n");
	printf(" @@@           #@@@                     @@@ @@@@           \n");
	printf(" @@@   @@@@  @@@@      @@@@@@@@@@@@@    @@@@@@,            \n");
	printf(" @@@     .@@@@                              @@,			   \n");
	printf(" @@@                                        @@,            \n");
	printf(" @@@                                        @@,            \n");
	printf(" @@@                                        @@,            \n");
	printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             \n");
	Sleep(3000);
}

void bye() {
	//bye animation
	for (int temp = 0; temp < 3; temp++) {
		system("cls");
		printf("                                                 &(          \n");
		printf("                                               @@@@@       \n");
		printf("                                    @@@@@@@@%%    %%@@@@@@     \n");
		printf("                                  &@@@@@@@@@@@,     @@@@@@*  \n");
		printf("                                  @@@@@@@@@@@@%%       &@@@@@.\n");
		printf("                                  /@@@@@@@@@@@      *@@@@@@  \n");
		printf("                                    .@@@@@@&      @@@@@@(    \n");
		printf("                               %%@@@@@@@@@@@@@@@@@@@@@@       \n");
		printf("                            .@@@@@@@@@@@@@@@@@@@@@@(         \n");
		printf("                          &@@@@@@@@@@@@@@@@@@@@@@            \n");
		printf("                       .@@@@@@. ,@@@@@@@@@@@@@@@             \n");
		printf("                     &@@@@@&    ,@@@@@@@@@@@@@@@             \n");
		printf("                    /@@@@@(     ,@@@@@@@@@@@@@@@             \n");
		printf("                      /@@@@@@   ,@@@@@@@@@@@@@@@             \n");
		printf("                         @@@@@@(,@@@@@@@@@@@@@@@             \n");
		printf("                           /@@@@@@@@@@@@@@@@@@@@             \n");
		printf("                              ,.,@@@@@@@@@@@@@@@             \n");
		printf("                                ,@@@@@@%%#@@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                ,@@@@@@* @@@@@@@             \n");
		printf("                                 @@@@@@. %%@@@@@@             \n");
		Sleep(500);
		system("cls");
		printf("                                                                     \n");
		printf("                                                              @@@@@*\n");
		printf("                                    @@@@@@@@%%               @@@@@@  \n");
		printf("                                  &@@@@@@@@@@@,          /@@@@@,    \n");
		printf("                                  @@@@@@@@@@@@%%        @@@@@@       \n");
		printf("                                  /@@@@@@@@@@@      *@@@@@&         \n");
		printf("                                    .@@@@@@&      @@@@@@(           \n");
		printf("                               %@@@@@@@@@@@@@@@@@@@@@@              \n");
		printf("                            .@@@@@@@@@@@@@@@@@@@@@@#                \n");
		printf("                          &@@@@@@@@@@@@@@@@@@@@@@.                  \n");
		printf("                       ,@@@@@@. *@@@@@@@@@@@@@@@                    \n");
		printf("                     &@@@@@&    ,@@@@@@@@@@@@@@@                    \n");
		printf("                    /@@@@@(     ,@@@@@@@@@@@@@@@                    \n");
		printf("                      /@@@@@@   ,@@@@@@@@@@@@@@@                    \n");
		printf("                         @@@@@@(*@@@@@@@@@@@@@@@                    \n");
		printf("                           /@@@@@@@@@@@@@@@@@@@@                    \n");
		printf("                              ,.,@@@@@@@@@@@@@@@                    \n");
		printf("                                ,@@@@@@@@@@@@@@@                    \n");
		printf("                                ,@@@@@@%%#@@@@@@@                    \n");
		printf("                                ,@@@@@@* @@@@@@@                    \n");
		printf("                                ,@@@@@@* @@@@@@@                    \n");
		printf("                                ,@@@@@@* @@@@@@@                    \n");
		printf("                                ,@@@@@@* @@@@@@@                    \n");
		printf("                                ,@@@@@@* @@@@@@@                    \n");
		printf("                                ,@@@@@@* @@@@@@@                    \n");
		printf("                                 @@@@@@. %%@@@@@@                    \n");
		Sleep(500);
	}
}
