#include <stdio.h>
#include <stdlib.h>

/*

  A05 Test
  By Colin McCormack

*/

#define MIN_NAME_CHARS 3
#define MAX_NAME_CHARS 10
#define MIN_NAME_CHAR 'a'
#define MAX_NAME_CHAR 'z'
#define MIN_DAY 1
#define MAX_DAY 30
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_YEAR 1980
#define MAX_YEAR 2000
#define MIN_SALARY 20000
#define MAX_SALARY 500000

#define MAX_DIGITS 6
//Max digits is the amount of digits for a salary

#define INVALID_STRING printf ("\n Employee #%i is invalid so you will need to retry...\n", i+1);
//Invalid employee message

typedef struct {
	int day;
	int month;
	int year;
} dateType;

typedef struct {
	char lName[MAX_NAME_CHARS + 1];
	char mName[MAX_NAME_CHARS + 1];
	char fName[MAX_NAME_CHARS + 1];
	char gender;
	dateType dob;
	int salary;
} empType;

/*

  Get the index of the next non space character

*/

int getIndex(char *s, int i) {

  while (s[i] == ' ')
    i++; 

  return i;

}


/*

  Parse a string

*/

int getString(char *target, char *s, int *i, int min, int max, char minC, char maxC) {

  *i = getIndex(s, *i);

  int j = 0;

  while (s[*i] >= minC && s[*i] <= maxC && s[*i] && j < max)
    target[j++] = s[(*i)++];

  //printf ("Setting %c is a invalid char at index %i\n", s[*i], j);

  target[j] = 0;

  if (j < min) { printf ("Error : Not enough charachters : %i < %i\n", j, min); return 1; }

  *i = getIndex(s, *i);

  if ((s[*i] != ',') && (s[*i] != '\n')) { printf ("Error : No comma (not csv)\n"); return -1; }

  (*i)++;

  //printf ("Parsed %s\n", target);

  return 0;
    
}

/*

  Parse and validate a gender

*/

int getGender(char *target, char *s, int *i, char opt1, char opt2, char opt3) {

  *i = getIndex(s, *i);

  *target = s[*i];

  if (*target != opt1 && *target != opt2 && *target != opt3) { printf ("Error : Invalid char for gender\n"); return 1; }

  //go past gender char
  (*i)++;

  *i = getIndex(s, *i);

  if ((s[*i] != ',') && (s[*i] != '\n')) { printf ("Error : No comma (not csv)\n"); return -1; }

  (*i)++;

  return 0;

}

/*

  Handler : Check if the char is a number

*/

int isNum (char c) {

  return (c >= '0' && c <= '9');

}

/*

  Parser and validate integer

*/

int getInt(int *target, char *s, int *i, int min, int max) {

  char holder[MAX_DIGITS + 1];

  *i = getIndex(s, *i);

  int j = 0;

  while (isNum(s[*i]))
    holder[j++] = s[(*i)++];

  if (j == 0) { printf ("Error : Target is of an invalid length (zero) \n"); return 0; }

  holder[j] = 0;

  *target = atoi(holder);

  if (*target < min || *target > max) { printf ("Error : Target is of an invalid length\n"); return 0; }

  *i = getIndex(s, *i);

  if ((s[*i] != ',') && (s[*i] != '\n')) { printf ("Error : No comma (not csv)\n"); return -1; }

  (*i)++;

  return 0;

}

/*

  Parse employee string (check each feild)
    return 1 if succesful

*/

int parseEmp(char *s, empType *emp) {

  int i = 0;

  if (getString(emp->lName, s, &i, MIN_NAME_CHARS, MAX_NAME_CHARS, MIN_NAME_CHAR, MAX_NAME_CHAR) != 0) return 0;
  if (getString(emp->mName, s, &i, MIN_NAME_CHARS, MAX_NAME_CHARS, MIN_NAME_CHAR, MAX_NAME_CHAR) != 0) return 0;
  if (getString(emp->fName, s, &i, MIN_NAME_CHARS, MAX_NAME_CHARS, MIN_NAME_CHAR, MAX_NAME_CHAR) != 0) return 0;

  if (getGender(&(emp->gender), s, &i, 'M', 'N', 'F') != 0) return 0;

  if (getInt(&(emp->dob.day), s, &i, MIN_DAY, MAX_DAY) != 0) return 0;
  if (getInt(&(emp->dob.month), s, &i, MIN_MONTH, MAX_MONTH) != 0) return 0;
  if (getInt(&(emp->dob.year), s, &i, MIN_YEAR, MAX_YEAR) != 0) return 0;

  if (getInt(&(emp->salary), s, &i, MIN_SALARY, MAX_SALARY) != 0) return 0;

  return 1;

}

/*

  Get employees from user

*/

void getEmps(empType *emps, int n){
	char s[400];
	int i;
	
	i = 0;
	while (i < n){
		printf ("Enter your employee string below for employee #%i...\n", i+1);
		gets(s);
    fflush(stdin);
		if(parseEmp(s,&emps[i])) i++;	// we got a valid employee!
		else INVALID_STRING
	}
}

/*

  Compare and determine if swap is needed


*/

int ifSwapNeeded(empType *emp1, empType *emp2) {

	//abstraction to simplify code
  dateType *date1 = &(emp1->dob);
  dateType *date2 = &(emp2->dob);

  // Check if the year for the first date is less
  if (date1->year > date2->year)
      return 1;

  if (date1->year < date2->year)
      return 0;

  // Check if the months need to be swapped
  if (date1->month > date2->month)
      return 1;
      
  if (date1->month < date2->month)
      return 0;

	// Check if the days need to be swapped
  if (date1->day > date2->day)
      return 1;

  if (date1->month < date2->month)
      return 0;

  return 0;
}

/*

	Swap : Swap the two functions by swapping the entire structures

*/

void swap(empType *emp1, empType *emp2) {
  empType temp = *emp1;
  *emp1 = *emp2;
  *emp2 = temp;
}

/*

  Sort : Bubble sort O(n^2)

*/

void sortEmpsByDOB (empType *emps, int n){
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n-i-1; j++) 
			if (ifSwapNeeded(&(emps[j]), &(emps[j+1])))
				swap(&emps[j], &emps[j+1]);
	
}

/*

  Print employees with standard output format (one line csv)

*/

void outputEmps(empType *emps, int n) {
    for (int i = 0; i < n; i++) {
        printf ("Emp: %i\n", i+1);
        printf ("%s,%s,%s,%c,%i,%i,%i,%i\n", 
		emps[i].fName, emps[i].mName, emps[i].lName, emps[i].gender,
                emps[i].dob.day, emps[i].dob.month, emps[i].dob.year, emps[i].salary);
    }
}


int main(){
	empType emps[100];
	int numEmps = 3;
	
	getEmps(emps, numEmps);
  printf ("\nYour employees by insertion order :\n");
	outputEmps (emps, numEmps);
	sortEmpsByDOB (emps, numEmps);
  printf ("\nYour employees by date :\n");
	outputEmps(emps, numEmps);
	return 0;
}
