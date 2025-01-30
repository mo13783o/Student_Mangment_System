/*
 ============================================================================
 Name        : Student_Management_System.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct student
{
	int ID ;
	char name [50];
	int age ;
	float GPA;
};


struct node
{
	struct student data ;
	struct node *next;
};
struct node *head=NULL;

void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void deleteStudent(int id);
void searchHighestGPA(void);


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	bool running = true;
	while (running)
	{


		printf("1. Add Student\n");
		printf("2. Display Students\n");
		printf("3. Search Student by ID\n");
		printf("4. Update Student Information\n");
		printf("5. Delete Student\n");
		printf("6. Calculate Average GPA\n");
		printf("7. Search Student with Highest GPA\n");
		printf("8. Exit\n");
		int choose;
		printf (" Enter your choose ");
		scanf ("%d", &choose);


		switch (choose)
		{
		case 1:
		    {

		        struct student s;


		        printf("Enter ID: ");
		        scanf("%d", &s.ID);

		        printf("Enter Name: ");
		        scanf(" %[^\n]", s.name);

		        printf("Enter Age: ");
		        scanf("%d", &s.age);

		        printf("Enter GPA: ");
		        scanf("%f", &s.GPA);


		        addStudent(&s);
		        printf ("\n---------------------------------------------\n");
		    }
		    break;


		case 2 :
			displayStudents();
		    printf ("\n---------------------------------------------\n");
			break;

		case 3:
			printf ("Enter the student to search");
			int Id;
			scanf ("%d", &Id);
			searchStudentByID(Id);
		    printf ("\n---------------------------------------------\n");

			break;

		case 4:
			printf ("Enter the student id to update the information ");
			int num;
			scanf ("%d" ,&num);
			updateStudent (num);
		    printf ("\n---------------------------------------------\n");
			break;

		case 5:
		{
			int deleted_id;
			printf (" Enter The ID to delete ");
			scanf ("%d" , &deleted_id );
			deleteStudent(deleted_id);
			 printf ("\n---------------------------------------------\n");
		}
			break;
		case 6:
		{
			float avareg =calculateAverageGPA();
			printf("The Average GPA is %f ", avareg);
			 printf ("\n---------------------------------------------\n");
		}
			break;
		case 7 :
			searchHighestGPA();
			 printf ("\n---------------------------------------------\n");
			break;
		case 8:
			running = false;
			break;
		default:
			printf ("you choose the wrong number ");
			break;
		}

	}





	return 0;
}
void addStudent(const struct student *const ptr) {


    struct node *current = head;
    while (current != NULL) {
        if (current->data.ID == ptr->ID) {
            printf("Error: Student ID %d already exists.\n", ptr->ID);
            return;
        }
        current = current->next;
    }


    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }


    newNode->data = *ptr;
    newNode->next = NULL;


    if (head == NULL) {

        head = newNode;
    } else {

        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }


}


void displayStudents(void)
{
	struct node *ptr = head;
	if (ptr == NULL) {
		printf("No students found.\n");
		return;
	}


	while(ptr != NULL)
	{
		printf ("[ ID =%d , ",ptr->data.ID);
		printf ("Name =%s , ",ptr->data.name);
		printf ("Age =%d , ",ptr->data.age);
		printf ("GPA =%0.5f , ]\n",ptr->data.GPA);

		ptr = ptr->next;
	}



}
void searchStudentByID(int iD)
{

	struct node *current = NULL;
	int pos = 0;

	if(head==NULL)
	{
		printf("there are no student");
		return;
	}


	current = head;
	while(current != NULL)
	{
		if(current->data.ID == iD)
		{
			printf ("[ ID =%d , ",current->data.ID);
			printf ("Name =%s , ",current->data.name);
			printf ("Age =%d , ",current->data.age);
			printf ("GPA =%0.5f , ]",current->data.GPA);

			return;
		}
		current = current->next;
		pos++;
	}

	printf("%d does not exist in the list\n", iD);
}
void updateStudent(int id) {
    if (head == NULL) {
        printf("There are no students.\n");
        return;
    }

    struct node *current = head;
    struct node *temp = head;
    int newID;


    while (current != NULL) {
        if (current->data.ID == id) {
            printf("Enter New ID: ");
            scanf("%d", &newID);


            while (temp != NULL) {
                if (temp->data.ID == newID && temp != current) {
                    printf("Error: Student ID %d already exists.\n", newID);
                    return;
                }
                temp = temp->next;
            }


            current->data.ID = newID;
            printf("Enter New Name: ");
            scanf(" %[^\n]", current->data.name);

            printf("Enter New Age: ");
            scanf("%d", &current->data.age);

            printf("Enter New GPA: ");
            scanf("%f", &current->data.GPA);


            return;
        }
        current = current->next;
    }

    printf("The student was not found.\n");
}

float calculateAverageGPA(void) {
    struct node *current = head;
    int count = 0;
    float totalGPA = 0.0;

    if (head == NULL) {
        printf("There are no students.\n");
        return 0.0;
    }

    while (current != NULL) {
        totalGPA += current->data.GPA;
        count++;
        current = current->next;
    }

    return (count > 0) ? (totalGPA / count) : 0.0;
}
void deleteStudent(int id)
{
	int pos = 0;

	struct node *current = NULL;
	struct node *prev = NULL;

	struct node * delete_node = NULL;


	if(head==NULL)
	{
		printf("Linked List is empty");
		return;
	}


	if(head->data.ID == id)
	{
		delete_node = head;

		head = head->next;
		printf("%d found at position %d and deleted \n", id, pos);
		free(delete_node);
		return;
	}


	pos++;
	current = head->next;
	prev = head;
	while(current != NULL)
	{
		if(current->data.ID == id)
		{

			delete_node = current;
			prev->next = current->next;
			printf("%d found at position %d and deleted \n", id, pos);
			free(delete_node);
			return;
		}
		prev = current;
		current = current->next;
		pos++;
	}


	if(delete_node == NULL)
	{
		printf("%d not found in the List.",id);
	}
}

void searchHighestGPA(void)
{
    if (head == NULL)
    {
        printf("There are no students.\n");
        return;
    }

    struct node *current = head;
    float highestGPA = head->data.GPA;


    while (current != NULL) {
        if (current->data.GPA > highestGPA) {
            highestGPA = current->data.GPA;
        }
        current = current->next;
    }


    printf("Students with the highest GPA (%.2f):\n", highestGPA);
    current = head;
    while (current != NULL)
    {
        if (current->data.GPA == highestGPA)
        {
            printf("[ ID = %d, Name = %s, Age = %d, GPA = %.2f ]\n",
            current->data.ID, current->data.name, current->data.age, current->data.GPA);
        }
        current = current->next;
    }
}






















