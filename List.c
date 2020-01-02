/* -----------------------------

Balaram Behera
bbehera@ucsc.edu
CSE 101 - PA5
12/6/2019

File: List.c

------------------------------ */


#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        //free((*pN)->data);
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Creates and returns a new empty List.
List newList() {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->index = -1;
    L->length = 0;
    return (L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }

    return (L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }

    return (L->index);
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling front() on empty List\n");
        exit(1);
    }

    return (L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling back() on empty List\n");
        exit(1);
    }

    return (L->back->data);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling get() on empty List\n");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling get() on List with undefined cursor\n");
        exit(1);
    }

    return (L->cursor->data);
}

// equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("List Error: calling equals() on NULL List reference(s)\n");
        exit(1);
    }

    if (A->length != B->length) {
        return 0;
    }

    Node Na = A->front;
    Node Nb = B->front;
    while (Na != NULL) {
        if (Na->data != Nb->data) {
            return 0;
        }
        Na = Na->next;
        Nb = Nb->next;
    }

    return 1;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    while (L->length > 0) {
        moveFront(L);
        delete(L); // just delete the front element till the lest is empty
    }
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }

    if (L->length > 0) { // if list is non-empty
         L->cursor = L->front;  // point cursor to front
         L->index = 0;          // set index to first index
    }
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }

    if (L->length > 0) { // if list is non-empty
         L->cursor = L->back;       // point cursor to back
         L->index = L->length - 1;  // set index to last index
    }
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front
// of L; if cursor is defined and at front, cursor becomes undefined; if cursor
// is undefined do nothing.
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }

    if (L->index == 0) {    // cursor is at front
        // set cursor to undefined
        L->cursor = NULL;
        L->index = -1;
    } else if (L->index >= 0) {
        L->cursor = L->cursor->prev;    // "decrement" the element cursor is
                                        // pointing to
        L->index--;                     // decrement index
    }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back
// of L; if cursor is defined and at back, cursor becomes undefined; if cursor
// is undefined do nothing.
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }

    if (L->index == L->length - 1) {    // cursor is at back
        // set cursor to undefined
        L->cursor = NULL;
        L->index = -1;
    } else if (L->index >= 0) {
        L->cursor = L->cursor->next;    // "increment" the cursor to next element
        L->index++;                     // increment index
    }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before
// front element.
void prepend(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }

    // initialize a Node with the corresponding data
    Node N = newNode(data);

    if (L->length == 0) { // if List is empty
        L->front = L->back = N; // List is made up of just N, so both
                                // front and back point to it
    } else { // else if List is non-empty
        N->next = L->front; // link the current List to N
        L->front->prev = N; // link the front to N
        L->front = N;       // set front point at N
    }

    if (L->index >= 0) {    // if a cursor is pointing to an element then it
                            // would technically be pushed one index
        L->index++; // increment index
    }

    L->length++; // increment legnth cause we added an element
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after
// back element.
void append(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }

    // initialize a Node with the corresponding data
    Node N = newNode(data);

    if (L->length == 0) { // if the List is empty
        L->front = L->back = N; // List is made up of just N, so both
                                // front and back point to it
    } else { // else if the List is non-empty
        N->prev = L->back;  // link N to back of List
        L->back->next = N;  // link back to N
        L->back = N;        // set back point at N now
    }

    L->length++; // increment the length
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling insertBefore() on empty List\n");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling insertBefore() on List with undefined cursor\n");
        exit(1);
    }

    Node N = newNode(data); // initialize Node with corresponding data

    if (L->index == 0) { // if cursor is the first element of List
        N->next = L->cursor;        // link N to cursor which points to front
        L->cursor->prev = N;        // link cursor to N, in turn linking to front
        L->front = L->cursor->prev; // set front point to "new front"
    } else { // otherwise
        N->prev = L->cursor->prev;  // link N to cursor's previous
        N->next = L->cursor;        // link N to cursor
        L->cursor->prev->next = N;  // link cursor's previous to N
        L->cursor->prev = N;        // link cursor
    }

    L->index++; // increment index because it's inserted before, thus
                // pushing the cursor one more index

    L->length++; // increment length due to new addition to List
}

// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling insertAfter() on empty List\n");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling insertAfter() on List with undefined cursor\n");
        exit(1);
    }

    Node N = newNode(data); // initialize Node with corresponding data

    if (L->index == L->length - 1) { // if cursor is the back element
        N->prev = L->cursor;        // link N to cursor which points to back
        L->cursor->next = N;        // link cursor to N, in turn linking back to N
        L->back = L->cursor->next;  // set back to "new back"
    } else { // otherwise
        N->next = L->cursor->next;  // link N to cursor's next
        N->prev = L->cursor;        // link N to cursor
        L->cursor->next->prev = N;  // link cursor's next to N
        L->cursor->next = N;        // link cursor to N
    }

    // no need to increment index because insertion is happening after cursor

    L->length++; // increment length due to new addition to List
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling deleteFront() on empty List\n");
        exit(1);
    }

    Node N = L->front; // save the front Node in N

    // if the cursor is pointing to the front, we set it to undefined
    if (L->index == 0) {
        L->cursor = NULL;
    }

    if (L->length == 1) { // if List has only one element
        L->front = L->back = NULL; // set both front and back to NULL
    } else { // if List has more than one element
        L->front = L->front->next;      // set the front to its next
        L->front->prev->next = NULL;    // delete link from the old front to the List
        L->front->prev = NULL;          // delete link from new front to old front
    }

    // since we are deleting a Node in the back the cursor gets pushed back
    // one, and if the cursor is now undefined, index is set to -1 too
    if (L->index >= 0) {
        L->index--; // decrement index
    }

    L->length--; // decrement the length due to deletion

    freeNode(&N); // free the deleted front Node
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling deleteBack() on empty List\n");
        exit(1);
    }

    Node N = L->back; // save the back Node in N

    if (L->index == L->length - 1) { // if the cursor is pointing to the back
        L->cursor = NULL;   // set it to undefined
        L->index = -1;      // set index to -1
    }

    if (L->length == 1) { // if List has only one element
        L->front = L->back = NULL; // set both front and back to NULL
    } else { // otherwise
        L->back = L->back->prev;    // set back to its previous
        L->back->next->prev = NULL; // delete old back's link to List
        L->back->next = NULL;       // delete link from new back to old back
    }

    L->length--; // decrement length due to deletion

    freeNode(&N); // free the deleted back Node
}

// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        printf("List Error: calling delete() on empty List\n");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling delete() on List with undefined cursor\n");
        exit(1);
    }

    Node N = L->cursor;

    // remove all links to cursor from List
    if (L->length == 1) { // if the List has only one element
        L->front = L->back = NULL; // set both front and back to NULL
    } else if (L->index == 0) { // if the cursor is pointing to front
        L->front = L->cursor->next; // set front to cursor's next
        L->front->prev = NULL;      // delete front's link to cursor
        L->cursor->next = NULL;     // delete cursor's link to List
    } else if (L->index == L->length - 1) { // if the cursor is pointing to the back
        L->back = L->cursor->prev;  // set back to cursor's previous
        L->back->next = NULL;       // delete back's link to cursor
        L->cursor->prev = NULL;     // delete cursor's link to List
    } else { // otherwise
        L->cursor->prev->next = L->cursor->next; // link cursor's previos to next
        L->cursor->next->prev = L->cursor->prev; // link cursor's next to previos
        L->cursor->next = NULL; // delete link to rest of List
        L->cursor->prev = NULL; // dlete link to other side of List
    }

    L->cursor = NULL;   // delete cursor itself
    L->index = -1;      // set index to -1

    L->length--; // decrement length due to deletion

    freeNode(&N); // free deleted cursor Node
}


// Other operations -----------------------------------------------------------

// copyList()
// Returns a new List representing the same integer sequence as L. The
// cursor in the new list is undefined, regardless of the state of the
// cursor in L. The List L is unchanged.
List copyList(List L) {
    if (L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }

    List cL = newList();
    Node N = L->front;
    while (N != NULL) {
        append(cL, N->data);
        N = N->next;
    }
    return cL;
}

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }
    if (out == NULL) {
        printf("List Error: calling printList() with NULL file reference\n");
        exit(1);
    }

    Node N = L->front;
    while (N != NULL) { // loop through List
        fprintf(out, "%d", N->data); // prints to file
        N = N->next; // iterate
        if (N != NULL) {
            fprintf(out, " ");
        }
    }
}
