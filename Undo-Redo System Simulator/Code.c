#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char action[50];
    char value;
} Operation;

Operation undoStack[MAX], redoStack[MAX];
int topUndo = -1, topRedo = -1;

char text[100] = "";
int textLen = 0;

// Push to Undo stack
void pushUndo(char *action, char value) {
    topUndo++;
    strcpy(undoStack[topUndo].action, action);
    undoStack[topUndo].value = value;
}

// Push to Redo stack
void pushRedo(char *action, char value) {
    topRedo++;
    strcpy(redoStack[topRedo].action, action);
    redoStack[topRedo].value = value;
}

// Pop undo
Operation popUndo() {
    return undoStack[topUndo--];
}

// Pop redo
Operation popRedo() {
    return redoStack[topRedo--];
}

// Clear redo stack whenever new action is done
void clearRedo() {
    topRedo = -1;
}

void typeChar(char c) {
    text[textLen++] = c;
    text[textLen] = '\0';
    pushUndo("TYPE", c);
    clearRedo();
}

void deleteChar() {
    if (textLen == 0) return;
    char removed = text[textLen - 1];
    textLen--;
    text[textLen] = '\0';
    pushUndo("DELETE", removed);
    clearRedo();
}

void undo() {
    if (topUndo == -1) {
        printf("\nNothing to undo!\n");
        return;
    }

    Operation op = popUndo();

    if (strcmp(op.action, "TYPE") == 0) {
        textLen--;
        text[textLen] = '\0';
        pushRedo("TYPE", op.value);
    } 
    else if (strcmp(op.action, "DELETE") == 0) {
        text[textLen++] = op.value;
        text[textLen] = '\0';
        pushRedo("DELETE", op.value);
    }
}

void redo() {
    if (topRedo == -1) {
        printf("\nNothing to redo!\n");
        return;
    }

    Operation op = popRedo();

    if (strcmp(op.action, "TYPE") == 0) {
        text[textLen++] = op.value;
        text[textLen] = '\0';
        pushUndo("TYPE", op.value);
    } 
    else if (strcmp(op.action, "DELETE") == 0) {
        textLen--;
        text[textLen] = '\0';
        pushUndo("DELETE", op.value);
    }
}

int main() {
    int choice;
    char c;

    while (1) {
        printf("\n\n--- UNDO REDO SIMULATOR ---\n");
        printf("Text: %s\n", text);
        printf("1. Type Character\n");
        printf("2. Delete Character\n");
        printf("3. Undo\n");
        printf("4. Redo\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter character: ");
                scanf(" %c", &c);
                typeChar(c);
                break;

            case 2:
                deleteChar();
                break;

            case 3:
                undo();
                break;

            case 4:
                redo();
                break;

            case 5:
                exit(0);
        }
    }
}
