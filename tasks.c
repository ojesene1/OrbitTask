#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h" 

typedef struct Task{
    char *name;
    int complete;
    int priority;
    int task_id;
    struct Task *next;

    //Date
    int day, month, year;
} Task;

int addTask(TaskManager *manager, char *task_name, int id, int priority, int day, int month, int year, int isComplete){
    Task *newTask = malloc(sizeof(Task));
    if(newTask == NULL || task_name == NULL){
        printf("Add Task Failure.\n");
        return 0;
    }
    newTask->name = strdup(task_name);
    newTask->complete = isComplete;
    newTask->priority = priority;
    if(id <= 0){
        newTask->task_id = manager->next_id;
        manager->next_id++;
        manager->size++;
    }
    else{ 
        newTask->task_id = id;
    }
    

    newTask->day = day;
    newTask->month = month;
    newTask->year = year;

    newTask->next = newTask ;

    if (manager->tail == NULL){
        manager->tail = newTask;
        return 1;
    }

    // Circular tail pointer makes insertion O(1) complexity.
    newTask->next = manager->tail->next;
    manager->tail->next = newTask;    //updates the tail pointer to point to the newest node (task id start - 1 2 3 4 - task id tail)
    manager->tail = newTask; //tail should be the last node in the list
    return 1;

}

int deleteTask(TaskManager *manager, int del_task_id){
    if (manager->tail == NULL){
        printf("There are no list items to delete.\n");
        return 0;
    }
    Task *temp = manager->tail->next;
    Task *prev = manager->tail;
    do{
        if(temp->task_id == del_task_id){
            prev->next = temp->next;

            if(temp == manager->tail && temp->next == temp){ // Need extra case for when the tail deletion is the last node in the list
                free(temp->name);
                free(temp);
                manager->tail = NULL;   // Sets the tail ptr to null
                return 1;
            }
            if (temp == manager->tail) {
                manager->tail = prev;
            }
            
            free(temp->name); //needed because we allocated name earlier with strdup()
            free(temp);
            manager->size--;
            return 1;
        }
        prev = prev->next;
        temp = temp->next;
    }while(temp != manager->tail->next);

    return 0;
}

int completeTask(TaskManager *manager, int complete_task_id){
    if(manager->tail == NULL){
        printf("There are no list items to complete.\n");
        return 0;
    }
    
    Task *temp = manager->tail->next;
    do{
        if(temp->task_id == complete_task_id){
            temp->complete = !temp->complete;
            return 1;
        }
        temp = temp->next;
    }while(temp != manager->tail->next);

    return 0;
}

int printList(TaskManager *manager, int sort){
    if(manager->tail == NULL){
        printf("To-Do List is EMPTY!\nGO FIND SOMETHING TO DO!!\n");
        return 0;
    }

    Task *temp = manager->tail->next;
    if(sort == 1){
        printf("\n== HIGH PRIORITY TASKS ==");
        printf("\n------------------------------");
        do{
            if(temp->priority == HIGH){ //PRINTING THE HIGH PRIO TASKS
                printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " "));
                printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            }
            temp = temp->next;
        } while(temp != manager->tail->next);

        printf("\n\n== MEDIUM PRIORITY TASKS ==");
        printf("\n------------------------------");
        do{
            if(temp->priority == MEDIUM){ //PRINTING THE MED PRIO TASKS
                printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " "));
                printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            }
            temp = temp->next;
        } while(temp != manager->tail->next);

        printf("\n\n== LOW PRIORITY TASKS ==");
        printf("\n------------------------------");
        do{
            if(temp->priority == LOW){ //PRINTING THE LOW PRIO TASKS
                printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " "));
                printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            }
            temp = temp->next;
        } while(temp != manager->tail->next);
    }
    else if(sort == 2){
        printf("\n=== COMPLETED TASKS ===");
        printf("\n------------------------------");
        do{
            if(temp->complete){
                printf("\n[%d] %s", temp->task_id, temp->name);
                printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            }
            temp = temp->next;
        } while(temp != manager->tail->next);
        
        printf("\n\n=== INCOMPLETE TASKS ===");
        printf("\n------------------------------");
        do{
            if(!temp->complete){
                printf("\n[%d] %s", temp->task_id, temp->name);
                printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            }
            temp = temp->next;
        } while(temp != manager->tail->next);
    }
    
    return 1;
}

void freeList(TaskManager *manager){
    if(manager->tail == NULL){
        printf("List already Empty Gang...\n");
    }
    else{
        Task *cur;
        Task *prev = manager->tail->next;
        Task *head = manager->tail->next; //holds the head ptr so we make sure this address is cleared.

        do{
            cur = prev->next;
            free(prev->name);
            free(prev);
            prev = cur;
        } while(cur != head);

        manager->tail = NULL;
        manager->size = 0;
        manager->next_id = 1;
    }
}

void editTask(TaskManager *manager, int task_id){
    if(manager->tail == NULL){
        printf("List is empty.\n");
    }
    else{
        Task *temp = manager->tail->next;
        int found = 0;
        do{
            if(temp->task_id == task_id){
                found = !found;
                break;
            }
            temp = temp->next;
        } while(temp != manager->tail->next);

        if(!found){
            printf("Task mentioned was not found. Sorry!");
        }
        else{
            while(found){
                int choice;
                printf("What would you like to change about %s?\n", temp->name);
                printf("1. Change task Name.\n");
                printf("2. Update task Priority.\n");
                printf("3. Update task Completion.\n");
                printf("4. Update task Due Date\n");
                printf("5. Exit Task Editing\n");
                printf("Your Choice: ");
                char buff1[10];
                fgets(buff1, sizeof(buff1), stdin);
                choice = atoi(buff1);
                
                switch(choice){
                    case 1: //CHANGE TASK NAME
                        printf("What would you like the new task name to be: ");
                        char name[100];
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = '\0';
                        free(temp->name);
                        temp->name = strdup(name);
                        printf("Edit Successful!");
                        break;

                    case 2://CHANGE TASK PRIORITY
                        printf("What should the new Priority be? (1 = LOW, 2 = MEDIUM, 3 = HIGH): ");
                        char buff2[10];
                        fgets(buff2, sizeof(buff2), stdin);
                        int priority = atoi(buff2);
                        if(priority != LOW && priority != MEDIUM && priority != HIGH){
                            printf("Wrong priority, try again.");
                            break;
                        }
                        temp->priority = priority;
                        printf("Priority updated!");
                        break;

                    case 3: //TOGGLE TASK COMPLETION
                        completeTask(manager, temp->task_id);
                        printf("Toggled Task Completion!");
                        break;
                    
                    case 4:
                        printf("Date: ");
                        char buff3[10];
                        fgets(buff3, sizeof(buff3), stdin);
                        int day = atoi(buff3);
                        printf("Month: ");
                        char buff4[10];
                        fgets(buff4, sizeof(buff4), stdin);
                        int month = atoi(buff4);
                        printf("Year: ");
                        char buff5[10];
                        fgets(buff5, sizeof(buff5), stdin);
                        int year = atoi(buff5);
                        temp->day = day, temp->month = month, temp->year = year;
                        printf("The new task date is %d/%d/%d.", temp->day, temp->month, temp->year);
                        break;

                    case 5: //EXIT TASK EDITING
                        printf("Exitting task editing...");
                        found = !found;
                        break;
                        
                    default: 
                        printf("Wrong choice, try again.");
                        break;
                }
                printf("\n");
            }
        }
    }
}

void searchTaskByName(TaskManager *manager, char* task_name){
    if (manager->tail == NULL){
        printf("\nList is still empty G.");
        return;
    }
    Task *temp = manager->tail->next;
    do{
        if(strcmp(task_name, temp->name) == 0){
            printf("\nFound it!");
            printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " "));
            printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            return;
        }
        temp = temp->next;
    } while(temp != manager->tail->next);
    printf("\nCouldn't find the task you inputted. Try inputting the exact name structure.");
}

void searchTaskById(TaskManager *manager, int task_id){
    if (manager->tail == NULL){
        printf("\nList is still empty G.");
        return;
    }
    Task *temp = manager->tail->next;
    do{
        if(task_id == temp->task_id){
            printf("\nFound it!");
            printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " "));
            printf("\nDue: %d/%d/%d", temp->day, temp->month, temp->year);
            return;
        }
        temp = temp->next;
    } while(temp != manager->tail->next);
    printf("\nCouldn't find the task you inputted. Try again.");
}

void saveTasks(TaskManager *manager){
    if(manager->tail == NULL){
        printf("No files saved to tasklist.txt.\n");
        return;
    }

    FILE *fptr;
    fptr = fopen("tasklist.txt", "w");
    if(fptr == NULL){
        printf("Unable to open tasklist.txt\n");
        return;
    }

    Task *temp = manager->tail->next;
    // Stores in form: size|next_id
    fprintf(fptr, "%d|%d", manager->size, manager->next_id);

    do{
        //Stores in form of task_id|task_name|task_priority|task_completion|due_day/due_month/due_year
        fprintf(fptr, "\n%d|%s|%d|%d|%d/%d/%d", temp->task_id, temp->name, temp->priority, temp->complete, 
                                                temp->day, temp->month, temp->year);
        temp = temp->next;
    } while(temp != manager->tail->next);
    
    printf("Saved tasks to tasklist.txt!\n");
    fclose(fptr);
}

void loadTasks(TaskManager *manager){
    FILE *fptr;
    fptr = fopen("tasklist.txt", "r");
    if(fptr == NULL){
        printf("Couldn't read from the tasklist.txt");
        return;
    }

    char line[150];
    if(fgets(line, sizeof(line), fptr)){
        int size, next_id;
        if(sscanf(line, "%d|%d", &size, &next_id)){
            manager->size = size;
            manager->next_id = next_id;
        }else { printf("Bad file format. Couldn't load tasks from tasklist.txt."); 
            return;}    
        char name[100];
        int id, priority, isComplete, day, month, year; 
        while(fgets(line, sizeof(line), fptr)){
            if(sscanf(line, "%d|%[^|]|%d|%d|%d/%d/%d", &id, name, &priority, &isComplete, &day, &month, &year)){
                addTask(manager, name, id, priority, day, month, year, isComplete);
            }else{ return; }
        }
        printf("Tasks Loaded from tasklist.txt!\n");
    }

    fclose(fptr);
}