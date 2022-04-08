/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Daniela A Cisneros Sande LOGIN 1: d.cisneross
 * AUTHOR 2: Candela Iglesias Lorenzo LOGIN 2: candela.iglesias
 * GROUP: 4.1
 * DATE: 31 / 03 / 22
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SMAX 25
#define SNULL -1

typedef int tPosS;

typedef struct {
    tUserId bidder;
    tProductPrice productPrice;
} tItemS;

typedef struct {
    tItemS data[SMAX];
    tPosS top;
} tStack;

void createEmptyStack(tStack *stack);

bool isEmptyStack(tStack stack);

bool push(tItemS d, tStack *stack);

void pop(tStack *stack);

tItemS peek(tStack stack);

#endif
