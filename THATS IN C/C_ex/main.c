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
    LinkedEmployee** employees;
    // Complete this function

    employees = calloc(MAX_COUNT, sizeof(LinkedEmployee*));

    FILE* fin = fopen(fn, "r");

    char buffer[(MAX_FIELD+1)*MAX_EID]; // line buffer

    fgets(buffer, (MAX_FIELD+1)*MAX_EID, fin); // purge first line

    int i = 0; // index of employee

    while(fgets(buffer, (MAX_FIELD+1)*MAX_EID, fin) != NULL) {
        //printf(buffer);

        employees[i] = malloc(sizeof(struct Employee)); // object

        employees[i] -> id = atoi(strtok(buffer, "\t"));
        strcpy(employees[i] -> firstname, strtok(NULL, "\t"));
        strcpy(employees[i] -> lastname, strtok(NULL, "\t"));
        employees[i] -> gender = (strtok(NULL, "\t"))[0]; // TBD does this even work and if not then what is the point of life
        strcpy(employees[i] -> department, strtok(NULL, "\t"));
        strcpy(employees[i] -> position, strtok(NULL, "\t"));
        strcpy(employees[i] -> supervisor_id, strtok(NULL, "\t"));

        //printf("%d", employees[i] -> id);

        i++;
    }

    fclose(fin);

    return employees;
}

LinkedEmployee** index_employees(LinkedEmployee** employees){
    LinkedEmployee** employee_index;
    // Complete this function

    return employee_index;
}

void link_employees(LinkedEmployee** employees, LinkedEmployee** employee_index){
    // Complete this function

    return;
}
        
void print_supervisory_chain(LinkedEmployee employee){
    // Complete this function

    return;
}

void clear_memory(LinkedEmployee** employees, LinkedEmployee** employee_index){
    // Complete this function
    
    return;
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
