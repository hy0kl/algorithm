/**
 * @describe: 链表
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
#include <stdio.h>
#include <stdlib.h>

#define EXIT_WITH_MALLOC    11

/** 单链表 */
typedef struct list_node_s list_node_t;

struct list_node_s {
    //void        *data;
    int          number;
    list_node_t *next;
};

typedef struct {
    list_node_t *head;
    list_node_t *tail;
    size_t       elts;  /** 当前元素的个数 */
} list_t;

list_t *
list_create()
{
    list_t *l = malloc(sizeof(list_t));
    if (NULL == l) {
        printf("Can create list, need size: %lu\n", sizeof(list_t));
        exit(EXIT_WITH_MALLOC);
    }

    l->head = NULL;
    l->tail = NULL;
    l->elts = 0;

    return l;
}

void *
list_push(list_t *l, int number)
{
    list_node_t *node = malloc(sizeof(list_node_t));
    if (NULL == node) {
        printf("Can malloc for node, need size: %lu\n", sizeof(list_node_t));
        exit(EXIT_WITH_MALLOC);
    }

    node->number = number;
    node->next   = NULL;
    l->elts++;

    /** 从表头插入 */
    if (NULL == l->tail) {
        l->head = node;
        l->tail = node;
    } else {
        node->next = l->head;
        l->head = node;
    }

    return node;
}

list_t *
list_revert(list_t *l)
{
    if (NULL == l->head || NULL == l->head->next) {
        return l;
    }

    list_node_t *prev = l->head;
    list_node_t *curt = l->head->next;
    list_node_t *next = NULL;

    while (curt != NULL) {
        next = curt->next;
        curt->next = prev;
        prev = curt;
        curt = next;
    }

    l->head->next = NULL;
    l->tail = l->head;  /** 头尾互换 */
    l->head = prev;

    return l;
}

void
print_list(list_t *l)
{
    list_node_t *node = l->head;
    while (node != NULL) {
        printf("list.node->number = %d\n", node->number);
        node = node->next;
    }
}

int main(int argc, char *argv[])
{
    list_t *l = list_create();

    list_push(l, 110);
    list_push(l, 128);
    list_push(l, 1024);

    print_list(l);
    printf("list size: %lu\n", l->elts);

    printf("revert list >>>\n");
    list_revert(l);
    print_list(l);

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

