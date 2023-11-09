#include "list.h"
#include <stdbool.h>
#include <stdio.h>

int list_counter = 1;

void test_List_create(List * list){
    if (list != NULL) {
            printf("    List %d: created successfully.\n", list_counter);
            list_counter++;
    } else {
        printf("    List %d: FAILED to create (lists exhausted).\n", list_counter);
        list_counter++;
    }

}

int main(){
    //////////////////////////////////////// TEST 1 ////////////////////////////////////////

    printf("TEST 1: testing List_create().\n");
    // initialize 11 lists, last one should fail since its over LIST_MAX_NUM_HEADS
    List* l1 = List_create();
    List* l2 = List_create();
    List* l3 = List_create();
    List* l4 = List_create();
    List* l5 = List_create();
    List* l6 = List_create();
    List* l7 = List_create();
    List* l8 = List_create();
    List* l9 = List_create();
    List* l10 = List_create();
    List* l11 = List_create();
    test_List_create(l1);
    test_List_create(l2);
    test_List_create(l3);
    test_List_create(l4);
    test_List_create(l5);
    test_List_create(l6);
    test_List_create(l7);
    test_List_create(l8);
    test_List_create(l9);
    test_List_create(l10);
    test_List_create(l11);



    //////////////////////////////////////// TEST 2 ////////////////////////////////////////
    // testing all edge cases for list_insert_before

    printf("\nTEST 2: Testing List_insert_before, List_next, List_first, and List_prev: \n");
    int i1 = 43;
    char i2 = 'n';
    long i3 = 1234;
    float i4 = 2.2;
    double i5 = 3334;
    int i6 = 27;
    char i7 = 'f';
    long i8 = 333;
    //float i9= 45.54;
    //double i10 = 0303;

    
    if(List_insert_before(l1, &i1) == 0){
        if(l1->currentpointer == l1->head && l1->currentpointer == l1->tail && l1->size ==1 && l1->currentpointer!=NULL){
            printf("    {} represents the current pointer.\n    SUCCESS: List 1 = [ {i1} ]\n");
        }
    }
    else{
        printf("FAIL :(\n");
    }
    if(List_insert_before(l1,&i2) == 0){
        if(l1->currentpointer == l1->head && l1->currentpointer!= l1->tail && l1->size ==2)
            printf("    SUCCESS: List 1 = [ {i2} -> i1 ]\n"); // l1 = [I2 <-> i1];
    }
    else{
        printf("FAIL :(\n");
    }
    List_next(l1);//l1 = [i2 <-> I1];
    printf("    ~~ Calling List_next on List 1: SUCCESS: List 1 = [ i2 -> {i1} ] ~~\n");
    if(List_insert_before(l1,&i3)==0){
        if(l1->currentpointer != l1->head && l1->currentpointer!= l1->tail && l1->size == 3 && l1->currentpointer->prev == l1->head && l1->currentpointer->next== l1->tail){
            printf("    SUCCESS: List 1 = [ i2 -> {i3} -> i1 ]\n");
        }
    }
    else{
        printf("FAIL :(\n");
    }
    List_next(l1);
    List_next(l1);
    printf("    ~~ Calling List_next on List 1: SUCCESS: List 1 = [ i2 -> i3 -> {i1} ] ~~\n");
    if(l1->currentpointer == NULL){
         printf("    ~~ Calling List_next on List 1: SUCCESS: List 1 = [ i2 -> i3 -> i1 -> {NULL} ] ~~\n");
    }
    else{
        printf("FAIL :(\n");
    }
    if(List_insert_before(l1,&i4)==0){
        if(l1->currentpointer->next == NULL && l1->size == 4 && l1->currentpointer == l1->tail){
            printf("    SUCCESS: List 1 = [ i2 -> i3 -> i1 -> {i4} ]\n");
        }
        else{printf("FAIL :(\n");}
    }
    else{
        printf("FAIL :(\n");
    }
    if(List_first(l1)== l1->head){
        printf("    ~~ Calling List_first on List 1: SUCCESS: List 1 = [ {i2} -> i3 -> i1 -> i4 ]\n");
    }
    List_prev(l1);
    printf("    ~~ Calling List_prev on List 1: SUCCESS: List 1 = [ {NULL} -> i2 -> i3 -> i1 -> i4 ] ~~\n");

    if(List_insert_before(l1, &i5)==0){
        if(l1->head == l1->currentpointer && l1->currentpointer->prev== NULL && l1->size == 5){
            printf("    SUCCESS: List 1 = [ {i5} -> i2 -> i3 -> i1 -> i4 ]\n");
        }
    }

    

    //////////////////////////////////////// TEST 3 ////////////////////////////////////////
    // testing all edge cases for list_insert_after

    printf("\nTEST 3: Testing List_insert_after and List_last \n");
    if(List_insert_after(l2, &i1)==0){
        if(l2->currentpointer == l2->head && l2->currentpointer == l2->tail && l2->size ==1 && l2->currentpointer!=NULL){
            printf("    {} represents the current pointer.\n    SUCCESS: List 2 = [ {i1} ]\n");
        }
    }
    else{
        printf("FAIL :(\n");
    }
    if(List_insert_after(l2, &i2)==0){
        if(l2->currentpointer == l2->tail && l2->currentpointer->prev == l2->head && l2->size==2 && l2->currentpointer->next == NULL){
            printf("    SUCCESS: List 2 = [ i1 -> {i2} ]\n");
        }
    }
    else{
        printf("FAIL :(\n");
    }
    List_prev(l2); //l2 = [I1 -> i2];
    printf("    ~~ Calling List_prev on List 1: SUCCESS: List 2 = [ {i1} -> i2 ] ~~\n");

    if(List_insert_after(l2, &i3)==0){ // i1 -> {i3} ->i2
        if(l2->currentpointer->next == l2->tail && l2->currentpointer->prev == l2->head && l2->size == 3){
            printf("    SUCCESS: List 2 = [ i1 -> {i3} -> i2 ]\n");
        }
    }
    else{
        printf("FAIL :(\n");
    }
    List_prev(l2);
    List_prev(l2);
    printf("    ~~ Calling List_prev on List 2: SUCCESS: List 2 = [ {i1} -> i3 -> i2 ] ~~\n");
    printf("    ~~ Calling List_prev on List 2: SUCCESS: List 2 = [ {NULL} -> i1 -> i3 -> i2 ] ~~\n");

    if(List_insert_after(l2, &i4)==0){
        if(l2->head == l2->currentpointer && l2->size ==4 && l2->currentpointer->prev == NULL){
            printf("    SUCCESS: List 2 = [ {i4} -> i1 -> i3 -> i2 ] \n");
        }
    }
   if(List_last(l2)== l2->tail){
        printf("    ~~ Calling List_last on List 2: SUCCESS: List 2 = [ i4 -> i1 -> i3 -> {i2} ]\n");
    }
    List_next(l2);
    printf("    ~~ Calling List_next on List 2: SUCCESS: List 2 = [ i4 -> i1 -> i3 -> i2 -> {NULL} ] ~~\n");

    if(List_insert_after(l2, &i5)==0){
        if(l2->currentpointer== l2->tail && l2->size == 5 && l2->currentpointer->next == NULL){
            printf("    SUCCESS: List 2 = [ i4 -> i1 -> i3 -> i2 -> {i5} ] \n");
        }
    }

    //////////////////////////////////////// TEST 4 ////////////////////////////////////////
    printf("\nTEST 4: Testing List_append and List_prepend:\n");

    if(List_append(l1, &i6)==0){
        if(l1->tail == l1->currentpointer && l1->size == 6){
            printf("    List_append SUCCESS List 1 = [ i5 -> i2 -> i3 -> i1 -> i4 -> {i6} ]\n");
        }
    }
    if(List_append(l3, &i7)==0){
        printf("    List_append SUCCESS on empty List 3. List 3 = [ {i1} ]\n");
    }

    if(List_prepend(l1, &i7)==0){
        if(l1->head == l1->currentpointer && l1->size == 7){
            printf("    List_prepend SUCCESS List 1 = [ {i7} -> i5 -> i2 -> i3 -> i1 -> i4 -> i6 ]\n");
        }
    }
    if(List_prepend(l4, &i1)==0){
        printf("    List_prepend SUCCESS on empty List 4. List 4 = [ {i1} ]\n");
    }
    List_next(l4);
    printf("    ~~ Calling List_next on List 4: SUCCESS: List 4 = [ i1 -> {NULL} ] ~~\n");
    if(List_prepend(l4, &i8) == 0 && l4->currentpointer == l4->head ){
        printf("    List_prepend SUCCESS on List 4. List 4 = [ {i2} -> i1 ]\n");
    }

    //////////////////////////////////////// TEST 5 ////////////////////////////////////////
    printf("\nTEST 5: Testing List_count and List_curr:\n");
    if(List_curr(l1)== l1->currentpointer->data && l1->currentpointer->data == &i7){
        printf("    List_curr(List 1) SUCCESS!\n");
    }
    if(List_count(l1)==7){
        printf("    List_count(List 1) SUCCESS!\n");
    }

    //////////////////////////////////////// TEST 6 ////////////////////////////////////////
    printf("\nTEST 6: Testing List_trim and List_remove:\n");
    if(List_curr(l4) == List_remove(l4) && l4->size == 1){
        printf("    List_remove(List 4) SUCCESS List 4 = [ {i1} ]\n");
    }

    if(List_curr(l4) == List_remove(l4) && l4->size == 0){
        printf("    List_remove(List 4) SUCCESS List 4 = [   ]\n");
    }

    if(List_last(l1) == List_trim(l1) && l1->size == 6 && l1->currentpointer == l1->tail){
        printf("    List_trim(List 1) SUCCESS List 1 = [ i7 -> i5 -> i2 -> i3 -> i1 -> {i4} ]\n");
    }

    //////////////////////////////////////// TEST 7 ////////////////////////////////////////
    printf("\nTEST 7: Testing List_concat\n");
    List_concat(l1, l2);
    if(l1->size == 11 && l2->size == 0){
        printf("    List_concat(List 1, List 2) SUCCESS: List 1 = [ i7 -> i5 -> i2 -> i3 -> i1 -> {i4} -> *i4 -> *i1 -> *i3 -> *i2 -> *i5 ]\n");
        printf("        NOTE: To avoid confusion from similar item names, * represents an item from List 2. Thank you.\n");
    }

    //////////////////////////////////////// TEST 8 ////////////////////////////////////////
    //printf("\nTEST 8: Testing List_free\n");

    //////////////////////////////////////// TEST 9 ////////////////////////////////////////
    //printf("\nTEST 9: Testing List_search\n");
    


}