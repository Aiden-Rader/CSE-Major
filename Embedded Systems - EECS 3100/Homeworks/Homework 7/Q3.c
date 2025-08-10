/********************************************************************
 main.c
 Author: Aiden Rader
 Date Created: 7/2/2025
 Last Modified: 7/3/2025
 Section Number: 041
 Instructor: Devinder Kaur
 Homework Number: 7
	Question 3:
	Given the following struct declaration for a student, complete the subroutine which
	(a) calculates each student’s grade as 'P' or 'F' depending on whether the score is
	higher than or equal to 75, and (b) returns the average class score.
********************************************************************/

#define SIZE 64

struct Student
{
	unsigned long id;
	unsigned long score;
	unsigned char grade; // you will enter ‘P’ or ‘F’ };
};

typedef struct Student STyp;

unsigned long Grades(STyp class[SIZE])
{
	// Define total and average variables
	unsigned long total = 0;
	unsigned long average = 0;

	// Calculate total and average given class
	for (int i = 0; i < SIZE; i++)
	{
		if (class[i].score >= 75)
		{
			class[i].grade = 'P';
		}
		else
		{
			class[i].grade = 'F';
		}
		total += class[i].score;
	}
	average = total / SIZE;
	return average;
}

int main(void)
{
	STyp myClass[SIZE];

	// Fill out an array of dummy scores
	for (int i = 0; i < SIZE; i++)
	{
		myClass[i].id = i;
		myClass[i].score = 70 + i % 10; // scores from 70 to 79
	}

	unsigned long avg = Grades(myClass); // Call actual calculator function

	while (1)
	{
		// Stay here forever
	}
}
