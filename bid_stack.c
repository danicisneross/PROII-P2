/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Daniela A Cisneros Sande LOGIN 1: d.cisneross
 * AUTHOR 2: Candela Iglesias Lorenzo LOGIN 2: candela.iglesias
 * GROUP: 4.1
 * DATE: 31 / 03 / 22
 */

#include "bid_stack.h"

void createEmptyStack(tStack *stack) {
    stack->top = SNULL;
}

bool isEmptyStack(tStack stack) {
    return (stack.top == SNULL);
}

bool push(tItemS d, tStack *stack) {
    if (stack->top == SMAX - 1)
        return false;
    else {
        stack->top++;
        stack->data[stack->top] = d;
        return true;
    }
}

void pop(tStack *stack) {
    stack->top--;
}

tItemS peek(tStack stack) {
    return stack.data[stack.top];
}