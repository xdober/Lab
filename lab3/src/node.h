#ifndef _NODE_H
#define _NODE_H

#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
/*
 * some func about node
 * */
typedef struct Node_t{ 
	int row; 
	char name[32];
	char value[32]; 
	struct Node_t *children; 
	struct Node_t *next; 
}Node;

Node *initNode(char* name,char* value);

void addChild(Node* f,Node* c);

void printTree(Node* r,int count);
#endif
