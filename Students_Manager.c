/* Alon Berla 208544064 and Ilia Simhovich 323637793 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 40

typedef struct {
	char name[LEN];
	unsigned grade;
} Student;

typedef struct {
	char    name[LEN];
	unsigned grade;
} ExcellentStudent;

void menu(Student** arr, unsigned n, char** exe, unsigned nex);
Student** createArrayPointersToStudents(unsigned* n);
void checkalloc(const void* p);
void getStudentsFromUser(Student* p[], unsigned n);
void clear_buffer(void);
void removenl(char* s);
void print(const Student* a[], unsigned n);
void printStudent(const Student* s);
char** createArrayPointersToNames(unsigned* nex);
void getExcellentStudentsFromUser(char* arr[], unsigned nex);
void sort(Student** arr, unsigned n);
int binarySearchByName(Student* arr[], unsigned n, const char* key);
void printArrayStudents(const Student A[], unsigned n);

Student** createArrayPointersToStudents(unsigned* n) {
	printf("Please enter how many students do you have in the software department: ");
	(void)scanf("%d", n);
	clear_buffer();
	Student** arr = malloc(*n * (sizeof(Student*)));
	checkalloc(arr);
	return arr;
}

void checkalloc(const void* p) {
	if (p == NULL) 
	{
		printf("Allocation failed!\n");
		exit(1);
	}
}

void getStudentsFromUser(Student* p[], unsigned n) {
	unsigned i;
	unsigned g;
	printf("\nSoftware department:\n");
	printf("-----------------------\n"); 
	for (i = 0; i < n; i++)
	{
		p[i] = malloc(sizeof * p[i]);
		checkalloc(p[i]);
		printf("\nPlease insert name for student #%d: ", i + 1);
		fgets((*(p + i))->name, LEN, stdin);
		removenl((*(p + i))->name);
	
		while (1) {
			printf("Please insert grade for student #%d: ", i + 1);

			if (scanf("%u", &g) != 1) {
				printf("  Wrong input, please insert the grade again:\n");
				clear_buffer();      
				continue;            
			}
			if (g > 100) {
				printf("  Wrong input, please insert the grade again:\n");
				clear_buffer();      
				continue;            
			}
			clear_buffer();          
			break;
		}

		p[i]->grade = g;
	}
}

void clear_buffer(void) { // function that clears the buffer.
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
	}
}

void removenl(char* s) {
	while (*s != '\n' && *s != 0)
		s++;
	*s = 0;
}

void print(const Student* a[], unsigned n)
{
	unsigned i;
	for (i = 0; i < n; i++)
		printStudent(a + i);
}

void printStudent(const Student* s) {
	printf("%-10s %3d\n", s->name, s->grade);
}

char** createArrayPointersToNames(unsigned* nex) {
	printf("Please enter how many excellent students do you have from the whole college: ");
	(void)scanf("%d", nex);
	clear_buffer();
	char** arr = malloc(*nex * (sizeof(char*)));
	checkalloc(arr);
	return arr;
}

void getExcellentStudentsFromUser(char* arr[], unsigned nex) {
	unsigned i;
	printf("\nExcellent students from the whole college:\n");
	printf("---------------------------------------------\n");
	for (i = 0; i < nex; i++)
	{
		arr[i] = malloc(LEN);
		checkalloc(arr[i]);
		printf("\nPlease insert name for excellent student #%d: ", i + 1);
		fgets(arr[i], LEN, stdin);
		removenl(arr[i]);
	}
}

void sort(Student** arr, unsigned n) {
	for (unsigned i = 0; i + 1 < n; i++) {
		unsigned minIdx = i;
		for (unsigned j = i + 1; j < n; j++) {
			if (strcmp(arr[j]->name, arr[minIdx]->name) < 0) {
				minIdx = j;
			}
		}
		if (minIdx != i) {
			Student* tmp = arr[i];
			arr[i] = arr[minIdx];
			arr[minIdx] = tmp;
		}
	}
}

int binarySearchByName(Student* arr[], unsigned n, const char* key) {
	int low = 0;
	int high = (int)n - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;
		int cmp = strcmp(arr[mid]->name, key);

		if (cmp == 0) {
			return mid;
		}
		else if (cmp < 0) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}

void printArrayStudents(const Student A[], unsigned n) {
	for (unsigned i = 0; i < n; i++) {
		printStudent(&A[i]);
	}
}

void menu(Student** arr, unsigned n, char** exe, unsigned nex) {
	char choice;
	do {
		printf("\n======Menu========\n");
		printf("1 - Print all students from software dep:\n2 - Print the college excellent students:\n3 - Sort the students from software dep. by name:\n4 - Search and print excellent students from software dep:\n5 - Create and print a new array consists of excellent students from software dep:\nE/e - Exit this program:\n");
		printf("==================\n\n");
		if (scanf(" %c", &choice) != 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {}
			choice = 0;
		}

		switch (choice) {
		case '1':
			printf("\n"); 
			for (unsigned i = 0; i < n; i++) {
				printStudent(arr[i]);
				
			}
			printf("\n");
			break;

		case '2':
			printf("\n");
			for (unsigned i = 0; i < nex; i++) {
				printf("%-10s\n", exe[i]);

			}
			printf("\n");
			break;

		case '3':
			printf("\n");
			sort(arr, n);
			for (unsigned i = 0; i < n; i++) {
				printStudent(arr[i]);
			}
			printf("\n");
			break;

		case '4':
			printf("\n"); 
			sort(arr, n);
			for (unsigned i = 0; i < nex; i++) {
				int idx = binarySearchByName(arr, n, exe[i]);
				if (idx >= 0)
				{
					printf("%-10s\n", exe[i]);
				}
			}
			printf("\n");
			break;
		
		case '5':
			printf("\n");
			sort(arr, n);
			unsigned count = 0;
			for (unsigned i = 0; i < nex; i++) {
				if (binarySearchByName(arr, n, exe[i]) >= 0)
					count++;
			}
			Student* good = malloc(count * sizeof(Student));
			checkalloc(good);
			unsigned j = 0;
			for (unsigned i = 0; i < nex; i++) {
				int idx = binarySearchByName(arr, n, exe[i]);
				if (idx >= 0) {
					good[j++] = *arr[idx];
				}
			}
			printArrayStudents(good, j);
			free(good);
			printf("\n");
			break;

		case 'e': case 'E':
			printf("\nThis program will end now. goodbye.\n");
			for (unsigned i = 0; i < n; i++) {
				free(arr[i]);
			}
			break;

		default:
			printf("\nInvalid input\n");
		}
	} while (choice != 'e' && choice != 'E');
}

void main() {
	unsigned n;
	unsigned nex;
	Student** students_arr = (Student*)createArrayPointersToStudents(&n);
	char** exe_arr = createArrayPointersToNames(&nex);
	getStudentsFromUser(students_arr, n);
	getExcellentStudentsFromUser(exe_arr, nex);
	menu(students_arr, n, exe_arr, nex);
	free(students_arr);
	free(exe_arr);
} 