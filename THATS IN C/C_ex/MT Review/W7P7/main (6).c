#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_COUNT 100 // number of employees to load
#define MAX_EID 200 // maximum value of employee_id
#define MAX_FIELD 25  // max of 25 characters per field
#define NUM_FIELDS 7  // each employee has 7 fields/attributes

typedef struct Employee{
    int id;
    char firstname[MAX_FIELD];
    char lastname[MAX_FIELD];
    char gender;
    char department[MAX_FIELD];
    char position[MAX_FIELD];
    int supervisor_id;
    struct Employee* supervisor;
}LinkedEmployee;

LinkedEmployee** get_employees(char* fn){
    LinkedEmployee** employees = calloc(MAX_COUNT, sizeof(LinkedEmployee*));

    int i = 0;

    FILE* f = fopen(fn, "r");

    char buffer[(MAX_FIELD+1)*7]; // line buffer

    fgets(buffer, 1000, f); // skip first line

    while(fgets(buffer, (MAX_FIELD+1)*7, f) != NULL) {
        employees[i] = malloc(sizeof(LinkedEmployee));

        employees[i]->id = atoi(strtok(buffer, "\t"));
        strcpy(employees[i]->firstname, strtok(NULL, "\t"));
        strcpy(employees[i]->lastname, strtok(NULL, "\t"));
        employees[i]->gender = *(strtok(NULL, "\t"));
        strcpy(employees[i]->department, strtok(NULL, "\t"));
        strcpy(employees[i]->position, strtok(NULL, "\t"));
        employees[i]->supervisor_id = atoi(strtok(NULL, "\n"));
        employees[i] ->supervisor = NULL;

        i++;
    }
    fclose(f);

    return employees;
}

LinkedEmployee** index_employees(LinkedEmployee** employees){
    LinkedEmployee** employee_index = calloc(MAX_EID, sizeof(LinkedEmployee*)); // pre-filled with zeroes.

    while (*employees != NULL) {
        employee_index[(*employees)->id] = *employees;
        employees++; // advance pointer to next employee
    }
    // Complete this function
    return employee_index;
}

void link_employees(LinkedEmployee** employees, LinkedEmployee** employee_index){
    while (*employees != NULL) {
        (*employees)->supervisor = employee_index[(*employees)->supervisor_id];
        employees++;
    }
}
        
void print_supervisory_chain(LinkedEmployee employee){

    if (employee.supervisor != NULL) {
        print_supervisory_chain(*employee.supervisor);
        printf(" -> ");
    }
    printf("%s %s",
        employee.firstname, 
        employee.lastname);
}

void clear_memory(LinkedEmployee** employees, LinkedEmployee** employee_index){
    LinkedEmployee** stepper = employees;
    
    while (*stepper != NULL) {
        free(*stepper);
        stepper++; // advance pointer to next employee
    }
    free(employees);
    free(employee_index);
}

int main()
{
    LinkedEmployee** employees = get_employees("employee.txt");
    printf("Printing first 10 employees (id: first last)\n");
    for(int i=0; i<10; i++)
        printf("%d: %s %s\n", 
            employees[i]->id, 
            employees[i]->firstname, 
            employees[i]->lastname);

    printf("\n");
    LinkedEmployee** employee_index = index_employees(employees);
    int test_ids[5] = {1, 2, 24, 25, 27};
    for(int i=0; i<5; i++){
        int id = test_ids[i];
        printf("Employee id %d should be in position %d of employee_index\n", id, id);
        printf("    employee_index[%d] is: %d, %s %s\n", id, 
                employee_index[id]->id, 
                employee_index[id]->firstname, 
                employee_index[id]->lastname);
    }
    
    link_employees(employees, employee_index);

    printf("\nTesting printing of supervisory chain\n");
    print_supervisory_chain(*employee_index[32]);
    printf("\n");
    print_supervisory_chain(*employee_index[38]);
    printf("\n");
    print_supervisory_chain(*employee_index[13]);
    printf("\n");

    clear_memory(employees, employee_index);

    return 0;
}
