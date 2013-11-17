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

#define GREEN    "\e[1;32m"
#define BLUE     "\e[1;34m"
#define YELLOW   "\e[1;33m"
#define RED      "\e[1;31m"

char *MAGENTA  = "\e[01;35m";
char *CYAN     = "\e[01;36m";
char *NORMAL   = "\e[0m";

/**
 * @describe:
 * @author: hy0kle@gmail.com
 * */
typedef struct _smarty_str_t
{
    unsigned int count; /** 重复出现的次数 */
    size_t  len;
    char *data;
} smarty_str_t;

typedef struct _binary_tree_t
{
    smarty_str_t           node_data;
    struct _binary_tree_t *left;
    struct _binary_tree_t *right;
} binary_tree_t;

binary_tree_t *root = NULL;

binary_tree_t *create_new_node(const char *data)
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

    size = sizeof(char) * len + 1;
    node->node_data.data = (char *)malloc(size);
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

binary_tree_t *insert(binary_tree_t **tree, const char *src_data)
{
    assert(NULL != src_data);

    if (NULL == *tree)
    {
        *tree = create_new_node(src_data);
        //printf("tree->node_data.data: %s\n", (*tree)->node_data.data);
        return *tree;
    }

    size_t src_len = strlen(src_data);
    int n = (*tree)->node_data.len > src_len ? src_len : (*tree)->node_data.len;
    int cmp_ret = strncmp(src_data, (*tree)->node_data.data, n);
    //printf("tree->node_data.data: %s\n", (*tree)->node_data.data);

    /** fix cmp result */
    if (0 == cmp_ret && src_len != (*tree)->node_data.len)
    {
        cmp_ret = src_len - (*tree)->node_data.len;
    }

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

void print_node(const binary_tree_t *node)
{
    assert(NULL != node);

    printf("|%sdata%s: %s%s%s\t", BLUE, NORMAL, MAGENTA, node->node_data.data, NORMAL);
    printf("|    %scount%s: %s%d%s\t |\n",
        BLUE, NORMAL, CYAN, node->node_data.count, NORMAL);

    return;
}

/**
 * l: left
 * d: root
 * r: right
 * */
void ldr_print(const binary_tree_t *tree)
{
    if (NULL != tree)
    {
        ldr_print(tree->left);
        print_node(tree);
        ldr_print(tree->right);
    }
}

void rdl_print(const binary_tree_t *tree)
{
    if (NULL != tree)
    {
        rdl_print(tree->right);
        print_node(tree);
        rdl_print(tree->left);
    }
}

void dlr_print(const binary_tree_t *tree)
{
    if (NULL != tree)
    {
        print_node(tree);
        dlr_print(tree->left);
        dlr_print(tree->right);
    }
}

const binary_tree_t *find(const binary_tree_t *tree, const char *src_data)
{
    if (NULL == tree)
    {
        return NULL;
    }

    size_t src_len = strlen(src_data);
    int n = tree->node_data.len > src_len ? src_len : tree->node_data.len;
    int cmp_ret = strncmp(src_data, tree->node_data.data, n);

    /** fix cmp result */
    if (0 == cmp_ret && src_len != tree->node_data.len)
    {
        cmp_ret = src_len - tree->node_data.len;
    }

    if (0 == cmp_ret)
    {
        return tree;
    }
    else if (cmp_ret < 0)
    {
        return find(tree->left, src_data);
    }
    else
    {
        return find(tree->right, src_data);
    }
}

static char *test_data[] = {
    "5",
    "7",
    "abc",
    "test",
    "t",
    "abs",
    "123",
    "test",
    "1",
    "9",
    NULL,
};

int main(int argc, char *argv[])
{
    int i = 0;
    const binary_tree_t *tmp_node = NULL;
    root = create_new_node("hy");

    for (; test_data[i]; i++)
    {
        printf("input data: %s\n", test_data[i]);
        insert(&root, test_data[i]);
    }
    printf("\n");

    printf("---%sleft root right%s---\n", RED, NORMAL);
    ldr_print(root);
    printf("---");

    printf("\n\n");
    printf("---%sright root left%s---\n", YELLOW, NORMAL);
    rdl_print(root);
    printf("---");

    printf("\n\n");
    printf("---%sroot left right%s---\n", GREEN, NORMAL);
    dlr_print(root);
    printf("---\n\n");

    static char *f_data[] = {
        "test",
        "hy0l",
        "gmail",
        "9",
        NULL,
    };
    printf("--- %sFind logic%s ---\n", MAGENTA, NORMAL);
    for (i = 0; f_data[i]; i++)
    {
        if (NULL == (tmp_node = find(root, f_data[i])))
        {
            printf("Can NOT find %s%s%s from tree.\n", RED, f_data[i], NORMAL);
        }
        else {
            printf("Find -> %s%s%s from tree :\n    ", RED, f_data[i], NORMAL);
            print_node(tmp_node);
        }
    }

    return 0;
}

