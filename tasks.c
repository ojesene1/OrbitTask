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

    // Circular tail pointer makes insertion O(1) complexity.
    newTask->next = (*tail)->next;
    (*tail)->next = newTask;    //updates the tail pointer to point to the newest node (task id start - 1 2 3 4 - task id tail)
    *tail = newTask; //tail should be the last node in the list
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

            if(temp == *tail && temp->next == temp){ // Need extra case for when the tail deletion is the last node in the list
                free(temp->name);
                free(temp);
                *tail = NULL;   // Sets the tail ptr to null
                return 1;
            }
            if (temp == *tail) {
                *tail = prev;
            }
            
            free(temp->name); //needed because we allocated name earlier with strdup()
            free(temp);
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
    Task *temp = tail->next;
    do{
        printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " ")); //Now uses conditional operator with the complete member
        temp = temp->next;
    } while(temp != tail->next);
    return 1;
}

void freeList(Task *tail){
    if(tail == NULL){
        printf("List already Empty Gang...\n");
        return;
    }
    Task *cur;
    Task *prev = tail->next;

    do{
        cur = prev->next;
        free(prev->name);
        free(prev);
        prev = cur;
    } while(cur != tail->next);
}