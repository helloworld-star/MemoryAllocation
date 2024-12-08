#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "common.h"

struct Node {
    uint8_t REG_ID; /*  */
    uint8_t data_len;
    struct Node* next;  /* 指向下一个节点的指针 */
};

struct HeaderNode {
    struct Node* next;
};

struct HeaderNode* createList() {
    struct HeaderNode* head = (struct HeaderNode*)malloc(sizeof(struct HeaderNode));
    head->next = NULL; 
    return head;
}

/* 添加节点到链表末尾  */
void appendNode(struct HeaderNode* head, uint8_t REG_ID, uint8_t data_len) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->REG_ID = REG_ID;
    newNode->data_len = data_len;
    newNode->next = NULL;

    struct Node* last = head->next;
    if(last == NULL) {
        head->next = newNode;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
}
