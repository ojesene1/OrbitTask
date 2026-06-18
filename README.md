# 📝 C Circular Linked List To-Do List Manager

A command-line To-Do List application written in C using a **circular singly linked list**.  
This project demonstrates dynamic memory allocation, linked list operations, and low-level pointer management in C.

---

## 🚀 Features

- Add tasks dynamically
- Mark tasks as complete
- Delete tasks by ID
- Display all tasks
- Circular linked list structure
- Automatic task ID assignment
- Tracks completion status

---

## 🧠 Data Structure

This project uses a **circular singly linked list** where each node represents a task.

A `tail` pointer is used to efficiently manage the list.

### Task Node Structure

```c
typedef struct Task {
    char *name;
    int complete;
    int task_id;
    struct Task *next;
} Task;
```
## ⚙️ How It Works
- Each task is dynamically allocated using malloc
- Task names are stored using strdup
- The list is circular (last node points back to the first node)
- The tail pointer always points to the most recently added task
- Traversal continues until the list loops back to the head

## 🖥️ Example Output

```text
Make your very own To-Do List!

[1] Study C Programming [ ]
[2] Build Project [DONE]

1. Add a Task to the List!
2. Mark a Task as Complete!
3. Remove a Task from the List.
4. Print the Task List.
5. Quit Task Manager.
Choose your action:
```

## 🛠️ Compilation & Running
Compile
```text
gcc main.c -o todo
```
---
Run
```text
./todo
```
