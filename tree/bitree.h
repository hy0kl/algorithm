#ifndef _BITREE_H
#define _BITREE_H

#include <stdlib.h>

/** define structure for binary nodes */
typedef struct _smt_str_t
{
    u_char *str;
    size_t  len;
    unsigned int count;
} smt_str_t;

typedef struct _bitree_node_t
{
    void                  *data;
    struct _bitree_node_t *left;
    struct _bitree_node_t *right;
} bitree_node_t;

/** define a structure for binary trees. */
typedef struct _bitree_t
{
    int     size;
    int     (*compare)(const void *key1, const void *key2);
    void    (*destroy)(void *data);
    bitree_node_t *root;
} bitree_t;

/** public interface */
void bitree_init(bitree_t *tree, void (*destroy)(void *data));
void bitree_destroy(bitree_t *tree);
int  bitree_insert_left(bitree_t *tree, bitree_node_t *node, const void *data);
int  bitree_insert_right(bitree_t *tree, bitree_node_t *node, const void *data);
void bitree_remove_left(bitree_t *tree, bitree_node_t *node);
void bitree_remove_right(bitree_t *tree, bitree_node_t *node);
int  bitree_merge(bitree_t *merge, bitree_t *left, bitree_t *right, const void *data);

#define bitree_size(tree)   ((tree)->size)
#define bitree_root(tree)   ((tree)->rott)
#define bitree_is_eob(node) (NULL == (node))
#define bitree_is_leaf(node)    (NULL == (node)->left && NULL == (node)->right)
#define bitree_data(node)   ((node)->data)
#define bitree_left(node)   ((node)->left)
#define bitree_right(node)  ((node)->right)

#endif
