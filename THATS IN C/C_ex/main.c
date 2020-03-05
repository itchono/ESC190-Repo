// Edited by Mingo

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
    // Done
    LinkedEmployee** employees = calloc(MAX_COUNT, sizeof(LinkedEmployee*));

    FILE* fin = fopen(fn, "r");

    char buffer[(MAX_FIELD+1)*MAX_EID]; // line buffer

    fgets(buffer, (MAX_FIELD+1)*MAX_EID, fin); // purge first line by force reading --> advance to next position

    int i = 0; // index of employee

    while(fgets(buffer, (MAX_FIELD+1)*MAX_EID, fin) != NULL) {
        employees[i] = malloc(sizeof(struct Employee)); // object

        // Twist the edges of spacetime to use strtok
        employees[i] -> id = atoi(strtok(buffer, "\t"));
        // metal note: strtok takes in NULL on subsequent calls for tokens. Generally it sucks so don't use it
        strcpy(employees[i] -> firstname, strtok(NULL, "\t"));
        strcpy(employees[i] -> lastname, strtok(NULL, "\t"));
        employees[i] -> gender = (strtok(NULL, "\t"))[0]; // TBD does this even work and if not then what is the point of life
        strcpy(employees[i] -> department, strtok(NULL, "\t"));
        strcpy(employees[i] -> position, strtok(NULL, "\t"));
        employees[i] -> supervisor_id = atoi(strtok(NULL, "\t"));
        employees[i] -> supervisor = NULL;
        i++;
    }

    fclose(fin);

    return employees;
}

LinkedEmployee** index_employees(LinkedEmployee** employees){
    // Done
    LinkedEmployee** employee_index = calloc(MAX_COUNT, sizeof(LinkedEmployee*));

    for (int i = 0; i < MAX_COUNT; i++) {

        int j = 0;
        // traverse fully through the existing employee list for a match
        while (employees[j] != NULL) {
            if (employees[j]->id == i) employee_index[i] = employees[j]; // if match, directly assign pointer
            j++;
        }
    }
    return employee_index;
}

void link_employees(LinkedEmployee** employees, LinkedEmployee** employee_index){
    // Connects to supervisor
    // Done

    int i = 0;
    while (employees[i] != NULL) {
        // while loop to traverse existing employees
        if (employees[i]->supervisor_id != 0 && employee_index[employees[i]->supervisor_id] != NULL) {
            employees[i]->supervisor = employee_index[employees[i]->supervisor_id];
            // add corresponding supervisor ID if they exist
        } 
        i++;
    }
}
        
void print_supervisory_chain(LinkedEmployee employee){
    // lists people based on chain of command (back of arrow = highest in command)
    // Done

    if (employee.supervisor != NULL) {

        // call next person, sort of like a post-order traversal
        print_supervisory_chain(*(employee.supervisor));
        printf(" -> ");
        
    }
    printf("%s %s",
        employee.firstname, 
        employee.lastname);
}

void clear_memory(LinkedEmployee** employees, LinkedEmployee** employee_index){
    // Purges memory back to zero to have sustainable programming
    // Done

    int j = 0;
    // traverse fully through the existing employee list
    while (employees[j] != NULL) {
        free(employees[j]);
        j++;
    }
    // this is guaranteed to free all referneces for employee_index too

    free(employees);
    free(employee_index); // finally, free the double pointers
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

    return 0;
}
