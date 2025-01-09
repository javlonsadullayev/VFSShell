#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char name[128];
    int is_file;
    int created_at; 
    struct Node *parent;
    struct Node *child;
    struct Node *next;
} Node;

Node *root;
Node *current;

// utils
void init();
void prompt();
Node *create_node(char name[], int is_file);
void insert_node(Node *node);
void print_node(Node *node);

// commands
void mkdir(char name[]);
void touch(char name[]);
void ls();

int main() {
    
    init();

    char command[64]; 
    char arg[128]; 

    while (1) {
        prompt();

        scanf("%s", command);

        if (strcmp(command, "mkdir") == 0) {
            scanf("%s", arg);
            mkdir(arg);
        } else if (strcmp(command, "touch") == 0) {
            scanf("%s", arg);
            touch(arg);
        } else if (strcmp(command, "ls") == 0) {
            ls();
        }
    }

    return 0;
}

void init() {
    Node *node = malloc(sizeof(Node));

    strcpy(node->name, "root");
    node->is_file = 0;
    node->created_at = time(NULL);
    node->parent = NULL;
    node->child = NULL;
    node->next = NULL;

    root = node;
    current = root;
}

void prompt() {
    printf("➜ %s ", current->name);
}

Node *create_node(char name[], int is_file) {
    Node *node = malloc(sizeof(Node));

    strcpy(node->name, name);
    node->is_file = is_file;
    node->created_at = time(NULL);
    node->parent = NULL;
    node->child = NULL;
    node->next = NULL;

    return node;
}

void insert_node(Node *node) {
    if (current->child == NULL) {
        current->child = node;
    }
    else {
        Node *temp = current->child;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void print_node(Node *node) {
    if (node->is_file) {
        printf("%s\n", node->name);
    } else {
        printf("%s/\n", node->name);
    }
}

void mkdir(char name[]) {
    Node *node = create_node(name, 0);

    insert_node(node);
}

void touch(char name[]) {
    Node *node = create_node(name, 1);

    insert_node(node);
}

void ls() {

    if (current->child != NULL) {
        Node *temp = current->child;
        print_node(temp);

        while (temp->next != NULL) {
            print_node(temp->next);
            temp = temp->next;
        }
    }
}
