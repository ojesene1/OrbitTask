#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.c"

int main(){
    int choice;
    char name[100];
    int task_id = 1, comp_task_id;
    Task *tail = NULL;
    printf("Make your very own To-Do List!\n");
    while(1){
        printf("\n1. Add a Task to the List!");
        printf("\n2. Mark a Task as Complete!");
        printf("\n3. Remove a Task from the List.");
        printf("\n4. Print the Task List.");
        printf("\n5. Quit Task Manager.");
        printf("\n6. Empty the List.");
        printf("\nChoose your action: ");
        char buff1[10];
        fgets(buff1, sizeof(buff1), stdin);
        choice = atoi(buff1);

        switch(choice){
            case 1:
                printf("Type the name of the Task: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';   //remove the newline from the input
                if (addTask(&tail, name, task_id)){
                    printf("\nSuccessfully added task %d: %s!", task_id++, name);
                }
                else{
                    printf("\nInvalid Task name, try again.");
                }
                break;
            case 2:
                printf("\nType the id of the completed task: ");
                char buff2[10];
                fgets(buff2, sizeof(buff2), stdin);
                comp_task_id = atoi(buff2);    //mixing scanf will leave the newline for the fgets next call - leading to unexpected behaviour
                if(completeTask(tail, comp_task_id)){
                    printf("\nSuccessfully completed task %d!", comp_task_id);
                }
                else{
                    printf("\nInvalid Task id, try again.");
                }
                break;
            case 3:
                printf("\nType the id of the task you wish to Remove: ");
                char buff3[10];
                fgets(buff3, sizeof(buff3), stdin);
                comp_task_id = atoi(buff3);
                if(deleteTask(&tail, comp_task_id)){
                    printf("\nSuccessfully deleted task %d!", comp_task_id);
                }
                else{
                    printf("\nInvalid Task id, try again.");
                }
                break;
            case 4:
                printList(tail);
                break;
            case 5: 
                exit(1);
                break;
            case 6:
                freeList(tail);
                printf("List is EMPTY!");
                break;
            default:
                printf("Make a choice or Quit!");
                break;
        }
        printf("\n");
    }
}