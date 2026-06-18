#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task{
    char *name;
    int complete;
    int task_id;
    struct Task *next;
} Task;

int addTask(Task **tail, char *task_name, int task_id){
    Task *newTask = malloc(sizeof(Task));
    if(newTask == NULL || task_name == NULL){
        printf("Add Task Failure.\n");
        return 0;
    }
    newTask->name = strdup(task_name);
    newTask->complete = 0;
    newTask->task_id = task_id;
    newTask->next = newTask ;

    if (*tail == NULL){
        *tail = newTask;
        return 1;
    }
    //Using circular nexted list
    Task *ptr = *tail;
    do{
        ptr = ptr->next;
    } while(ptr->next != *tail);

    ptr->next = newTask;
    newTask->next = *tail;
    return 1;

}

int deleteTask(Task **tail, int del_task_id){
    if(*tail == NULL){
        printf("There are no list items to delete.\n");
        return 0;
    }
    Task *temp = (*tail)->next;
    Task *prev = *tail;
    do{
        if(temp->task_id == del_task_id){
            prev->next = temp->next;
            if(temp == *tail){
                free(*tail);
                *tail = prev->next;
                return 1;
            }
            free(temp);
            temp = NULL;
            return 1;
        }
        prev = prev->next;
        temp = temp->next;
    }while(temp != (*tail)->next);
    return 0;
}

int completeTask(Task *tail, int complete_task_id){
    if(tail == NULL){
        printf("There are no list items to complete.\n");
        return 0;
    }
    Task *temp = tail->next;
    do{
        if(temp->task_id == complete_task_id){
            temp->complete = 1;
            return 1;
        }
        temp = temp->next;
    }while(temp != tail->next);
    return 0;
}

int printList(Task *tail){
    if(tail == NULL){
        printf("To-Do List is EMPTY!\nGO FIND SOMETHING TO DO!!\n");
        return 0;
    }
    Task *temp = tail;
    do{
        printf("Task %d: %s\n", temp->task_id, temp->name);
        temp = temp->next;
    } while(temp != tail);
    return 1;
}

int main(){
    int choice;
    char name[100];
    int task_id = 1, comp_task_id;
    Task *tail = NULL;
    printf("Make your very own To-Do List!\n");
    while(1){
        printList(tail);
        printf("\n1. Add a Task to the List!");
        printf("\n2. Mark a Task as Complete!");
        printf("\n3. Remove a Task from the List.");
        printf("\n4. Print the Task List.");
        printf("\n5. Quit Task Manager.");
        printf("\nChoose your action: ");
        scanf("%d", &choice);
        getchar();  // consume the leftover '\n'

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
                scanf("%d", &comp_task_id);
                if(completeTask(tail, comp_task_id)){
                    printf("\nSuccessfully completed task %d!", comp_task_id);
                }
                else{
                    printf("\nInvalid Task id, try again.");
                }
                break;
            case 3:
                printf("\nType the id of the task you wish to Remove: ");
                scanf("%d", &comp_task_id);
                if(deleteTask(&tail, comp_task_id)){
                    printf("\nSuccessfully deleted task %d!", comp_task_id);
                }
                else{
                    printf("\nInvalid Task id, try again.");
                }
                break;
            case 4:
                printf("The task list is:");
                break;
            case 5: 
                exit(1);
                break;
            default:
                printf("Make a choice or Quit!");
                break;
        }
        printf("\n");
    }
}