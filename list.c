#include "list.h"

#include <stdbool.h>
#include <stdio.h>

// array for heads of lists.
static List head_array[LIST_MAX_NUM_HEADS];
int head_array_avail = LIST_MAX_NUM_HEADS;
static int head_array_index =0;

// array for the nodes.
static Node node_array[LIST_MAX_NUM_NODES];
int node_array_avail = LIST_MAX_NUM_NODES;
static int node_array_index = 0;


List* List_create(){
    if(head_array_avail > 0){ // if theres available lists
        List* newlist = &head_array[head_array_index];// creating a new list
        newlist->head = NULL; // assigning values
        newlist->tail = NULL;
        newlist->index = head_array_index;
        newlist->size = 0;
        head_array_index++;
        head_array_avail --;
        newlist->status= LIST_OOB_START;
        return newlist;
    }
    else{
        return NULL;

    }

};

// Returns the number of items in pList.
int List_count(List* pList){
    return pList->size;
};

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if (pList->size ==0){
        pList->currentpointer = NULL;
        return NULL;
    }
    else{
       pList->currentpointer = pList->head;
       return pList->currentpointer->data;

    }
};

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    if (pList->size ==0){
        pList->currentpointer = NULL;
        return NULL;
    }
    else{
        pList->currentpointer = pList->tail;
        return pList->currentpointer->data;
    }
};

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
    //Node* curr = pList->currentpointer;
    if(pList->currentpointer->next == NULL){ // a b C null , want to do a b c NULL
        // to do: current pointer moves forward, curr prev = c, curr next = NULL
        //pList->currentpointer->next = NULL;
        pList->tail = pList->currentpointer;
        pList->currentpointer = NULL;
        pList->status= LIST_OOB_END;
        return NULL;
    }
    else{
        pList->currentpointer = pList->currentpointer->next;
        return pList->currentpointer->data;
    }
};

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    //Node* curr = pList->currentpointer;
    if(pList->currentpointer->prev == NULL){ // null A b c, want to do NULL a b c
        // to do: move back current pointer, then current pointer prev points to NULL, currpointer next points to a
        pList->head = pList->currentpointer;
        pList->currentpointer= NULL;
        pList->status = LIST_OOB_START;
        return NULL;
    }
    else{
        pList->currentpointer = pList->currentpointer->prev;
        return pList->currentpointer->data;
    }
};

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
    return pList->currentpointer->data;
};

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem){
    // 4 cases??: 
    // -current pointer is before start of pList, in this case add  item to start 
    // -current pointer is after end, so add item to end
    // -current pointer is within boundaries of pList, like a B c, so do a b X c
    // - list is empty and this is the 1st item added
    if(node_array_avail>0){
        Node* newnode = &node_array[node_array_index];
        node_array_index ++; // creating a new node, so up the index 
        node_array_avail --; // and theres 1 less node avail
        newnode->data= pItem;
        if(pList->currentpointer == NULL && pList->status == LIST_OOB_START && pList->size!=0){ // in this case, current pointer is before the start of the list
            // create node, update head. we have NULL a b c, we want null X a b c
            newnode->prev = NULL;
            newnode->next = pList->head;
            pList->head->prev = newnode; // null x A b c
            pList->head= newnode;
            pList->currentpointer= newnode;
            pList->size ++;
            return 0;
        }
        else if( pList->currentpointer == NULL && pList->status == LIST_OOB_END &&pList->size!=0){ // current point is after the end of list
            // we have x y z NULL, we want x y z A null
            newnode->prev = pList->tail;
            newnode->next = NULL;
            pList->tail->next= newnode; // x y Z a null
            pList->tail = newnode;
            pList->currentpointer = newnode;
            pList->size ++;
            return 0;
        }
        else if(pList->currentpointer != NULL){ // so we have  null a B c null, or null A b c, or a b C null,
        // and want to insert after currpointer
            newnode->prev = pList->currentpointer; // a B x c 
            newnode->next = pList->currentpointer->next;
            if(pList->currentpointer->next == NULL){ // if x y Z null
                pList->tail = newnode;
            }
            else{
                pList->currentpointer->next->prev= newnode;
            }
            pList->currentpointer->next=newnode;
            pList->currentpointer= newnode;
            pList->size++;
            return 0;
        }
        else if(pList->size == 0){ // list empty, head = NULL, tail = NULL, curr= NULL
            newnode->prev = NULL;
            newnode->next = NULL;
            pList->head= newnode;
            pList->tail= newnode;
            pList->currentpointer=newnode;
            pList->size++;
            return 0;
        }
        else{
            return -1;
        }
    }
    else{
        return -1;
    }
};

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem){
    // 4 cases:
    // -current item is before the start of pList, so we add to start NULL a b c, we want null X a b c
    // -current item is beyond the end of the pList, so we add to end, x y z NULL, we want x y z A null
    // -current item is within bounds, so null A b c null, a B c, or null a b c NULL
    // size is 0 and this is the first item added.
    if(node_array_avail>0){
        Node* newnode = &node_array[node_array_index];
        node_array_index ++; // creating a new node, so up the index 
        node_array_avail --; // and theres 1 less node avail
        newnode->data= pItem;
        if(pList->currentpointer == NULL && pList->status == LIST_OOB_START && pList->size!=0){ // in this case, current pointer is before the start of the list
            // create node, update head. we have NULL a b c, we want null X a b c
            newnode->prev = NULL;
            newnode->next = pList->head;
            pList->head->prev = newnode; // null x A b c
            pList->head= newnode;
            pList->currentpointer= newnode;
            pList->size ++;
            return 0;
        }
        else if( pList->currentpointer == NULL && pList->status == LIST_OOB_END &&pList->size!=0){ // current point is after the end of list
            // we have x y z NULL, we want x y z A null
            newnode->prev = pList->tail;
            newnode->next = NULL;
            pList->tail->next= newnode; // x y Z a null
            pList->tail = newnode;
            pList->currentpointer = newnode;
            pList->size ++;
            return 0;
        }
        else if(pList->currentpointer != NULL){ // a B c, we want a X b c
            newnode->prev = pList->currentpointer->prev; 
            newnode->next = pList->currentpointer;
            if(pList->currentpointer->prev == NULL){ // if null A b c
                pList->head = newnode;
            }
            else{
                pList->currentpointer->prev->next= newnode;
            }
            pList->currentpointer->prev= newnode;
            pList->currentpointer= newnode;
            pList->size ++;
            return 0;
        }
        else if(pList->size == 0){ // list empty, head = NULL, tail = NULL, curr= NULL
            //Node* newnode = &node_array[node_array_index];
            newnode->prev = NULL;
            newnode->next = NULL;
            pList->head= newnode;
            pList->tail= newnode;
            pList->currentpointer=newnode;
            pList->size++;
            return 0;
        }
        else{
            return -1;
        }
    }
    else{
        return -1; // no nodes available
    }

}




// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    // must add item after tail. update tail and current item
    // case: x y Z null, we want x y z A null
    if(pList->size == 0 && node_array_avail>0){
        Node* newnode = &node_array[node_array_index];
        newnode = &node_array[node_array_index++];
        node_array_index ++; // creating a new node, so up the index 
        node_array_avail --; // and theres 1 less node avail
        newnode->data= pItem;
        newnode->prev = NULL;
        newnode->next = NULL;
        pList->head = newnode;
        pList->tail = newnode;
        pList->currentpointer= newnode;
        pList->size ++;
        return 0;
    }
    else if (node_array_avail>0) { // 
        Node* newnode = &node_array[node_array_index];
        node_array_index ++; // creating a new node, so up the index 
        node_array_avail --; // and theres 1 less node avail
        newnode->data= pItem;
        newnode->prev = pList->tail;
        newnode->next = NULL;
        pList->tail->next = newnode;
        pList->tail= pList->tail->next;
        pList->currentpointer= newnode;
        pList->size ++;
        return 0;
    }
    else{
        return -1; // otherwise, all nodes are in use and no nodes avail
    }
    
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    // must add item before head. update head and current item
    // case: null A b c, we want null X a b c
    if(pList->size == 0 && node_array_avail>0){
        Node* newnode = &node_array[node_array_index];
        newnode = &node_array[node_array_index++];
        node_array_index ++; // creating a new node, so up the index 
        node_array_avail --; // and theres 1 less node avail
        newnode->data= pItem;
        newnode->prev = NULL;
        newnode->next = NULL;
        pList->head = newnode;
        pList->tail = newnode;
        pList->currentpointer= newnode;
        pList->size ++;
        return 0;
    }
    else if (node_array_avail>0) { // otherwise, create a new node
        Node* newnode = &node_array[node_array_index];
        node_array_index ++; // creating a new node, so up the index 
        node_array_avail --; // and theres 1 less node avail
        newnode->data= pItem;
        newnode->next = pList->head;
        newnode->prev = NULL;
        pList->head->prev = newnode;
        pList->head = newnode;
        pList->currentpointer= newnode;
        pList->size ++;
        return 0;
    }else{
        return -1; // otherwise, all nodes are in use and no nodes avail
    }
    

}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    // cases: 
    // 1: if OOB, then return null, & if list empty return NULL
    // 2: if x y Z -> x y NULL
    // 3: null X null
    // 4: if null X y z -> null Y z
    // 5: x Y z -> x Z
    if(pList->currentpointer == NULL || pList->size == 0){ // case 1 
        return NULL;
    }
    else if (pList->currentpointer == pList->tail && pList->currentpointer != pList->head){ // case 2 x y Z null
        Node * temp = pList->currentpointer;
        pList->tail = pList->currentpointer->prev;
        pList->tail->next = NULL;
        pList->currentpointer = NULL;
        pList->size --;
        return temp->data;
    }
    else if(pList->currentpointer == pList->head){ 
        if(pList->currentpointer->next == NULL){ // case 3: null X null
            Node * temp = pList->currentpointer;
            pList->currentpointer= NULL;
            pList->head= NULL;
            pList->tail = NULL;
            pList->status = LIST_OOB_START;
            pList->size --;
            return temp->data;
        }
        else{ // case 4: null X y z
            Node * temp = pList->currentpointer; 
            pList->head = pList->currentpointer->next;
            pList->currentpointer= pList->head;
            pList->currentpointer->prev= NULL;
            pList->size --;
            return temp->data;
        }
    }
    else if(pList->currentpointer!= pList->head && pList->currentpointer!=pList->tail && pList->currentpointer!= NULL){
        Node * temp = pList->currentpointer;
        pList->currentpointer->next->prev = pList->currentpointer->prev;
        pList->currentpointer->prev->next = pList->currentpointer->next;
        pList->currentpointer = pList->currentpointer->next;
        pList->size --;
        return temp->data;
    }
    else{
        return NULL;
    }
}


// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if(pList->size == 0){
        return NULL;
    }
    else{
        Node * temp = pList->tail;
        pList->tail = pList->tail->prev;
        pList->tail->next = NULL;
        pList->size --;
        pList->currentpointer= pList->tail;
        return temp->data;
    }
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    pList2->currentpointer = pList2->head;
    while(pList2->currentpointer != NULL){
        pList1->tail->next = pList2->currentpointer;
        pList1->tail->next->prev = pList1->tail;
        pList1->tail = pList1->tail->next;
        pList2->currentpointer = pList2->currentpointer->next;
        pList1->size ++;
        //pList2->currentpointer->prev = NULL;
        pList2->size --;
        
        }
    //printf("l1: %d , l2: %d \n", pList1->size, pList2->size);
    pList2= NULL;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
void List_free(List* pList, FREE_FN pItemFreeFn){
    pList->currentpointer = pList->head;
    while(pList->currentpointer!= NULL){
        pList->currentpointer= pList->currentpointer->next;
        (*pItemFreeFn)(pList->currentpointer->prev);
        pList->size --;
    }
}


// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    if(pList->currentpointer == NULL && pList->size != 0){
        pList->currentpointer = pList->head;
    }
    else if(pList->size == 0){
        return NULL;
    }
    while(pList->currentpointer!= NULL){
        if(pComparator(pList->currentpointer->data, pComparisonArg) == 1){
            return pList->currentpointer->data;
        }
        pList->currentpointer= pList->currentpointer->next;
    }
    pList->status = LIST_OOB_END;
    return NULL;
}


