/**
 * @file manageStudents.c
 * @author  Yair Escott <yair.95@gmail.com>
 *
 * @brief System to manage student information
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <string.h>

/** best returns the best student based on the given critera*/
int best();
/** merge prints the list of inputed students sorted using mergesort*/
int merge();
/** merge prints the list of inputed students sorted using quicksort*/
int quick();
/** getInputs is the method used to get inputs and deal with them accordingly*/
int getInputs();

// -------------------------- const definitions -------------------------

/**
 * @def struct Student
 * @brief a struct which contains a student
 */
typedef struct Student
{
    int age;
    char ID[11];
    int grade;
    char city[43];
    char name[43];
    char country[43];
}student;
/**
 * @def MAXINPUT 60
 * @brief the max input allowed
 */
#define MAXINPUT 61

/**
 * @def ARGC 2
 * @brief the number of args main receives
 */
#define ARGC 2

/**
 * @def SPACE 32
 * @brief ASCII for space
 */
#define SPACE 32
/**
 * @def INPUTPLACE 1
 * @brief the place of the argument
 */
#define INPUTPLACE 1

/**
 * @def LIMIT 5500
 * @brief the num of line limit
 */
#define LIMIT 5500

/**
 * @def SMALLLETTEREND 122
 * @brief ASCII for z
 */
#define SMALLLETTEREND 122

/**
 * @def SMALLLETTERSTART 97
 * @brief ASCII for a
 */
#define SMALLLETTERSTART 97

/**
 * @def BIGLETTEREND 90
 * @brief ASCII for Z
 */
#define BIGLETTEREND 90

/**
 * @def BIGLETTERSTART 65
 * @brief ASCII for A
 */
#define BIGLETTERSTART 65

/**
 * @def VALIDINPUT 6
 * @brief num of inputs allowed
 */
#define VALIDINPUT 6

/**
 * @def DASH 45
 * @brief ASCII for -
 */
#define DASH 45

/**
 * @def MAXGRADE 100
 * @brief max grade allowed
 */
#define MAXGRADE 100

/**
 * @def MINGRADE 0
 * @brief min grade allowed
 */
#define MINGRADE 0

/**
 * @def MINAGE 18
 * @brief min age allowed
 */
#define MINAGE 18

/**
 * @def MAXAGE 120
 * @brief max age allowed
 */
#define MAXAGE 120

//number  of lines inputted
int gLineCounter = -1;
//keeps track of the amount of inputs that were OK
int gOkLines = 0;
//flag to check if the best student has been updated once
int gBestStudentFlag = 0;
//array to contain all students
struct Student arr_student[LIMIT];
//a struct to contain and update the best student
struct Student gbestStudent;
/**
 * @def INPUTMESSEGE "Enter student info. To exit press q, then enter\n"
 * @brief the message the user sees to know what to input
 */
#define INPUTMESSEGE "Enter student info. To exit press q, then enter\n"

/**
 * @def END_MESSEGE "best student info is: ID:%i,Name:%c,Grade:%i,Age:%i,Country:%c,City: %c\n"
 * @brief the messege sent when the best student is found
 */
#define END_MESSEGE "best student info is: %s,%s,%d,%d,%s,%s\n"

/**
 * @def END_MESSEGE_QUICK_MERGE "ID:%i,Name:%c,Grade:%i,Age:%i,Country:%c,City: %c\n"
 * @brief printed when the students are sorted with quicksort
 */
#define END_MESSEGE_QUICK_MERGE "%s,%s,%d,%d,%s,%s\n"

/**
 * @def USAGE_ARG_ERROR "ERROR: the argument should be :best, merge, or quick\n"
 * @brief an error for when the argument does not match any correct arguments
 */
#define USAGE_ARG_ERROR "USAGE: the argument should be :best, merge, or quick\n"

/**
 * @def USAGE_NUM_ERROR "ERROR: only one argument should be inputted\n"
 * @brief an error for when a wrong number of arguments in inputted
 */
#define USAGE_NUM_ERROR "USAGE: one argument should be inputted\n"

/**
 * @def ID_ERROR "ERROR: ID needs to contain a number with 10 digits starting in one "
 * @brief ID input error
 */
#define ID_ERROR "ERROR: ID needs to contain a number with 10 digits starting in one"

/**
 * @def ID_ERROR_CONT "other than 0 \n in line %i"
 * @brief continuation -the line was too long
 */
#define ID_ERROR_CONT "other than 0 \nin line %i\n"

/**
 * @def NAME_ERROR "ERROR: Name should only contain letters, spaces and '-' \n in line %i"
 * @brief name input error
 */
#define NAME_ERROR "ERROR: Name should only contain letters, spaces and '-'\nin line %i\n"

/**
 * @def COUNTRY_ERROR "ERROR: Country should only contain letters, spaces and '-' \n in line %i"
 * @brief country input error
 */
#define COUNTRY_ERROR "ERROR: Country should only contain letters, spaces and '-' \nin line %i\n"

/**
 * @def CITY_ERROR "ERROR: City should only contain letters, spaces and '-' \n in line %i"
 * @brief city input error
 */
#define CITY_ERROR "ERROR: City should only contain letters, spaces and '-' \nin line %i\n"

/**
 * @def LONG_STRING_ERROR "ERROR: a variable has more that 42 chars\n in line %i"
 * @brief input too long for the subsections
 */
#define LONG_STRING_ERROR "ERROR: the input is faulty\nin line %i\n"

/**
 * @def INPUT_ERROR "ERROR: no student was added\n"
 * @brief error when no student was added
 */
#define INPUT_ERROR "ERROR: no student was added\n"

/**
 * @def GRADE_ERROR " ERROR: the grade should be an integer between 0 and 100 and should not start"
 * @brief grade input error
 */
#define GRADE_ERROR "ERROR: the grade should be an integer between 0 and 100 and should not start"

/**
 * @def GRAE_ERROR_CONT "with 0 unless it is 0\n in line %i"
 * @brief continuation -the line was too long
 */
#define GRADE_ERROR_CONT "with 0 unless it is 0\nin line %i\n"

/**
 * @def AGE_ERROR " ERROR: the age should be an integer between 18 and 120\n in line %i"
 * @brief age input error
 */
#define AGE_ERROR "ERROR: the age should be an integer between 18 and 120\nin line %i\n"

/**
 * @def SMALL_INPUT_ERROR "ERROR: the amount of arguments in the input is faulty\n in line %i"
 * @brief to little arguments in input error
 */
#define SMALL_INPUT_ERROR "ERROR: the amount of arguments in the input is faulty\nin line %i\n"

// ------------------------------ functions -----------------------------
/**
 * @brief The main function. sends the user in his/her desired direction
 * @return 1 if failed 0 if succeeded
 */
int main(int argc, char* argv[])
{
    if(argc == ARGC)
    {
        if(!strcmp(argv[INPUTPLACE], "best"))
        {
            return best();
        }
        if(!strcmp(argv[INPUTPLACE], "quick"))
        {
            return quick();
        }
        if(!strcmp(argv[INPUTPLACE], "merge"))
        {
            return merge();
        }
        else
        {
            printf("%s", USAGE_ARG_ERROR);
            return 1;
        }
    }
    else
    {
        printf("%s", USAGE_NUM_ERROR);
        return 1;
    }
}
/**
 * @brief checks that the ID is OK
 * @return 0 if failed 1 if succeeded
 */
int idChecker(const char ID[])
{
    if(ID[0] != '0' && strlen(ID) == 10)
    {
        for (unsigned int i = 0; i < strlen(ID); ++i)
        {
            if (ID[i] < 48 || ID[i] > 57)
            {
                printf(ID_ERROR);
                printf(ID_ERROR_CONT, gLineCounter);
                return 0;
            }
        }
        return 1;
    }
    else
    {
        printf(ID_ERROR);
        printf(ID_ERROR_CONT, gLineCounter);
        return 0;
    }
}

/**
 * @brief checks that the city, country and name are OK
 * @return 0 if failed 1 if succeeded
 */
int nameCountryCityChecker(char* name, char* country, char* city)
{
    if(strlen(name) != 0)
    {
        for(int i = 0; name[i] != '\0'; i++)
        {
            if ((name[i] <= SMALLLETTEREND && name[i] >= SMALLLETTERSTART) || (name[i] >=
                BIGLETTERSTART && name[i] <= BIGLETTEREND) || name[i] == SPACE || name[i] == DASH)
            {
                continue;
            }
            else
            {
                printf(NAME_ERROR, gLineCounter);
                return 0;
            }
        }
    }
    else
    {
        printf(SMALL_INPUT_ERROR, gLineCounter);
        return 0;
    }
    for(unsigned int i = 0; i < strlen(country); i++)
    {
        if(strlen(country) != 0)
        {
            if ((country[i] <= SMALLLETTEREND && country[i] >= SMALLLETTERSTART) || (country[i] >=
                BIGLETTERSTART && country[i] <= BIGLETTEREND) || country[i] == DASH)
            {
                continue;
            }
            else
            {
                printf(COUNTRY_ERROR, gLineCounter);
                return 0;
            }
        }
        else
        {
            printf(SMALL_INPUT_ERROR, gLineCounter);
            return 0;
        }
    }
    for(unsigned int i = 0; i < strlen(city); i++)
    {
        if(strlen(city) != 0)
        {
            if ((city[i] <= SMALLLETTEREND && city[i] >= SMALLLETTERSTART) || (city[i] >=
                BIGLETTERSTART && city[i] <= BIGLETTEREND) || city[i] == DASH)
            {
                continue;
            }
            else
            {
                printf(CITY_ERROR, gLineCounter);
                return 0;
            }
        }
        else
        {
            printf(SMALL_INPUT_ERROR, gLineCounter);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief checks that the grade is OK
 * @return 0 if failed 1 if succeeded
 */
int gradeChecker(int grade)
{
    if(grade > MAXGRADE || grade < MINGRADE)
    {
        printf(GRADE_ERROR);
        printf(GRADE_ERROR_CONT, gLineCounter);
        return 0;
    }
    return 1;
}

/**
 * @brief checks that the age is OK
 * @return 0 if failed 1 if succeeded
 */
int ageChecker(int age)
{
    if(age > MAXAGE || age < MINAGE)
    {
        printf(AGE_ERROR, gLineCounter);
        return 0;
    }
    return 1;
}

/**
 * @brief method that checks the students information was inputted correctly
 * @return 0 if failed 1 if succeeded
 */
int checkStudParams(struct Student stud)
{
    if(!idChecker(stud.ID))
    {
        return 0;
    }
    if(!ageChecker(stud.age))
    {
        return 0;
    }
    if(!gradeChecker(stud.grade))
    {
        return 0;
    }
    if(!nameCountryCityChecker(stud.name, stud.country, stud.city))
    {
        return 0;
    }
    return 1;
}

/**
 * @brief checks if the student is better than the current best */
void compareToBest(struct Student s1)
{
    if(((double) s1.grade / (double ) s1.age) > ((double) gbestStudent.grade / (double)
       gbestStudent.age))
    {
        gbestStudent = s1;
    }
}

/**
 * @brief method that return the best student out of the ones inputted
 * @return 1 if failed 0 if succeeded
 */
int best()
{
    struct Student new_student;
    char input[MAXINPUT];
    printf("%s", INPUTMESSEGE);
    while (fgets(input, MAXINPUT, stdin)!= NULL)
    {
        gLineCounter += 1;
        if(strcmp(input, "q\n") == 0)
        {
            if(gBestStudentFlag != 0)
            {
                printf(END_MESSEGE, gbestStudent.ID, gbestStudent.name, gbestStudent.grade,
                       gbestStudent.age, gbestStudent.country, gbestStudent.city);
                return 0;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(sscanf(input, "%11[^,],%43[^,],%d,%d,%43[^,],%s", new_student.ID,
               new_student.name, &new_student.grade, &new_student.age,
               new_student.country, new_student.city) != VALIDINPUT)
            {
                printf(LONG_STRING_ERROR, gLineCounter);
                printf("%s", INPUTMESSEGE);
                continue;
            }
            if(!checkStudParams(new_student))
            {
                printf("%s", INPUTMESSEGE);
                continue;
            }
            else
            {
                arr_student[gLineCounter] = new_student;
                if (!gBestStudentFlag)
                {
                    gbestStudent = arr_student[gLineCounter];
                    gBestStudentFlag = 1;
                }
                else
                {
                    compareToBest(arr_student[gLineCounter]);
                }
            }
        }
        printf("%s", INPUTMESSEGE);
    }
    return 0;
}

/**
 * @brief this method prints Student arrays */
void printArray(struct Student stud[], int array_size)
{
    int i;
    for (i = 0; i < array_size; i++)
    {
        printf(END_MESSEGE_QUICK_MERGE, stud[i].ID, stud[i].name, stud[i].grade,
               stud[i].age, stud[i].country, stud[i].city);
    }
}

/**
 * @brief the functional part of the mergesort algorithm
 */
void functionalMerge(struct Student *stud_arr, int left, int middle, int right)
{
    int i, j, t;
    int num1 = middle - left + 1;
    int num2 =  right - middle;
    struct Student LEFT[LIMIT];
    struct Student RIGHT[LIMIT];
    for (i = 0; i < num1; i++)
    {
        LEFT[i] = stud_arr[left + i];
    }
    for (j = 0; j < num2; j++)
    {
        RIGHT[j] = arr_student[middle + 1 + j];
    }
    /*i am merging the temporary arrays into the l...r array*/
    i = 0;
    j = 0;
    t = left;
    while (i < num1 && j < num2)
    {
        if ( ((double) LEFT[i].grade <= (double) RIGHT[j].grade))
        {
            stud_arr[t] = LEFT[i];
            i++;
        }
        else
        {
            stud_arr[t] = RIGHT[j];
            j++;
        }
        t++;
    }
    while (i < num1)
    {
        stud_arr[t] = LEFT[i];
        i++;
        t++;
    }
    while (j < num2)
    {
        stud_arr[t] = RIGHT[j];
        j++;
        t++;
    }
}

/**
 * @brief the mergesort algorithm */
void mergeSort(struct Student stud_arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right-left) / 2;
        mergeSort(stud_arr, left, middle);
        mergeSort(stud_arr, middle + 1, right);
        functionalMerge(stud_arr, left, middle, right);
    }
}

/**
 * @brief this method prints the sorted student array using mergesort
 * @return 1 if failed 0 if succeeded
 */
int merge()
{
    int imp = getInputs();
    if(imp == 1){
        printf("%s", INPUT_ERROR);
        return 1;
    }
    if(gOkLines > 0)
    {
        mergeSort(arr_student, 0, gOkLines-1);
        printArray(arr_student, gOkLines);
        return 0;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief this method switches 2 students in an array
 */
void switchStud(struct Student* a, struct Student* b)
{
    struct Student t = *a;
    *a = *b;
    *b = t;
}

/**
 * @brief the functional part of the quicksort algorithm
 * @return the index if the pivot who is in its correct place
 */
int partition (struct Student stud_arr[], int left, int right)
{
    char* pivot = stud_arr[right].name;
    int i = (left - 1);
    for (int j = left; j <= right - 1; j++)
    {
        if (strcmp(stud_arr[j].name, pivot)<0)
        {
            i++;
            switchStud(&stud_arr[i], &stud_arr[j]);
        }
    }
    switchStud(&stud_arr[i + 1], &stud_arr[right]);
    return (i + 1);
}

/**
 * @brief the quicksort algorithm- using partition- finds the pivots place then
 * recursively sorts the two halves of the array
 */
void quickSort(struct Student stud_arr[], int left, int right)
{
    if (left < right)
    {
        int par = partition(stud_arr, left, right);
        quickSort(stud_arr, left, par - 1);
        quickSort(stud_arr, par + 1, right);
    }
}

/**
 * @brief this method prints the sorted student array using quicksort
 * @return 1 if failed 0 if succeeded
 */
int quick()
{
    int imp = getInputs();
    if(imp == 1)
    {
        printf("%s", INPUT_ERROR);
        return 1;
    }
    if(gOkLines > 0)
    {
        quickSort(arr_student, 0, gOkLines-1);
        printArray(arr_student, gOkLines);
        return 0;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief a method that is used for the perpose of not reusing code to
 * retrieve student information from the user
 * @returns 1 fgets gets null and 0 if not
 */
int getInputs()
{
    struct Student new_student;
    char input[MAXINPUT];
    printf("%s", INPUTMESSEGE);
    while (fgets(input, sizeof(input), stdin)!=NULL)
    {
        gLineCounter += 1;
        if(strcmp(input, "q\n") == 0)
        {
            return 0;
        }
        else
        {
            if(sscanf(input, "%11[^,],%43[^,],%d,%d,%43[^,],%s", new_student.ID,
               new_student.name, &new_student.grade, &new_student.age,
               new_student.country, new_student.city) != VALIDINPUT)
            {
                printf(LONG_STRING_ERROR, gLineCounter);
                printf("%s", INPUTMESSEGE);
                continue;
            }
            if(!checkStudParams(new_student))
            {
                printf("%s", INPUTMESSEGE);
                continue;
            }
            else
            {
                gOkLines += 1;
                arr_student[gLineCounter] = new_student ;
            }
        }
        printf("%s", INPUTMESSEGE);
    }
    return 1;
}