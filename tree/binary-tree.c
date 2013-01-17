#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <err.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

/**
 * @describe:
 * @author: hy0kle@gmail.com
 * */
typedef struct _smarty_str_t
{
    unsigned int count; /** 重复出现的次数 */
    size_t  len;
    u_char *data;
} smarty_str_t;

typedef struct _binary_tree_t
{
    smarty_str_t           node_data;
    struct _binary_tree_t *left;
    struct _binary_tree_t *right;
} binary_tree_t;

binary_tree_t *root = NULL;

binary_tree_t *create_new_node(u_char *data)
{
    assert(NULL != data);
    //printf("create_new_node data %s\n", data);

    size_t size = sizeof(binary_tree_t);
    size_t len  = strlen(data);

    binary_tree_t *node = (binary_tree_t *)malloc(size);
    if (NULL == node)
    {
        fprintf(stderr, "Can NOT malloc() for node, need size:%lu \n", size);
        exit(1);
    }

    size = sizeof(u_char) * len + 1;
    node->node_data.data = (u_char *)malloc(size);
    if (NULL == node->node_data.data)
    {
        fprintf(stderr, "Can NOT malloc() for node->node_data.data, need size:%lu \n", size);
        exit(1);
    }
    node->node_data.len   = len;
    node->node_data.count = 1;
    snprintf(node->node_data.data, size, "%s", data);

    node->left  = NULL;
    node->right = NULL;

    return node;
}

binary_tree_t *insert(binary_tree_t **tree, u_char *src_data)
{
    assert(NULL != src_data);

    if (NULL == *tree)
    {
        *tree = create_new_node(src_data);
        //printf("insert data: %s\n", src_data);
        //printf("tree->node_data.data: %s\n", (*tree)->node_data.data);
        return *tree;
    }

    size_t src_len = strlen(src_data);
    int n = (*tree)->node_data.len > src_len ? src_len : (*tree)->node_data.len;
    int cmp_ret = strncmp((*tree)->node_data.data, src_data, n);
    //printf("tree->node_data.data: %s\n", (*tree)->node_data.data);

    if (0 == cmp_ret)
    {
        (*tree)->node_data.count++;
        return *tree;
    }
    else if (cmp_ret < 0)
    {
        return insert(&((*tree)->left), src_data);
    }
    else
    {
        return insert(&((*tree)->right), src_data);
    }
}

/** 
 * l: left
 * d: root
 * r: right
 * */
void ldr_print(binary_tree_t *tree)
{
    if (NULL != tree)
    {
        ldr_print(tree->left);
        printf("data: %s\t", tree->node_data.data);
        printf("count:%d\n", tree->node_data.count);
        ldr_print(tree->right);
    }
}

void rdl_print(binary_tree_t *tree)
{
    if (NULL != tree)
    {
        rdl_print(tree->right);
        printf("data: %s\t", tree->node_data.data);
        printf("count:%d\n", tree->node_data.count);
        rdl_print(tree->left);
    }
}

void dlr_print(binary_tree_t *tree)
{
    if (NULL != tree)
    {
        printf("data: %s\t", tree->node_data.data);
        printf("count:%d\n", tree->node_data.count);
        dlr_print(tree->left);
        dlr_print(tree->right);
    }
}

u_char *test_data[] = {
    "5",
    "7",
    "1",
    "9",
    NULL,
};

int main(int argc, char *argv[])
{
    int i = 0;
    binary_tree_t *tmp_root = NULL;
    root = create_new_node("6");
    
    tmp_root = root;

    for (; test_data[i]; i++)
    {
        printf("input data: %s\n", test_data[i]);
        insert(&tmp_root, test_data[i]);
    }

    printf("---left root right\n");
    ldr_print(root);
    
    printf("\n\n");
    printf("---right root left\n");
    rdl_print(root);

    printf("\n\n");
    printf("---root left right\n");
    dlr_print(root);

    return 0;
}

