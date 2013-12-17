/**
 * @describe:
 * @author: hy0kle@gmail.com
 * */
#include "common.h"

#define TEST_DATA_NUM 8
/**
 * 查找树 ADT 二叉查找树
 * */
typedef int node_value;
typedef struct _tree_node_t tree_node_t;
struct _tree_node_t
{
    node_value   element;
    tree_node_t *left;
    tree_node_t *right;
};

/**
 *  接口申明
 * */
tree_node_t *make_empty(tree_node_t *tree);
tree_node_t *find(const node_value search, tree_node_t *tree);
tree_node_t *find_min(tree_node_t *tree);
tree_node_t *find_max(tree_node_t *tree);
tree_node_t *insert(const node_value value, tree_node_t *tree);
tree_node_t *delete(const node_value value, tree_node_t *tree);

/** debug function */
void print_node(const tree_node_t *tree)
{
    assert(NULL != tree);

    printf("%stree->element%s = %s%d%s\n", GREEN, NORMAL, CYAN, tree->element, NORMAL);
    return;
}

/**
* l: left
* d: root
* r: right
*/
void ldr_print(const tree_node_t *tree)
{
    if (NULL != tree)
    {
        ldr_print(tree->left);
        print_node(tree);
        ldr_print(tree->right);
    }
}

int main(int argc, char *argv[])
{
    tree_node_t *root = NULL;
    node_value data[TEST_DATA_NUM] = {6, 2, 8, 1, 4, 9, 10, 11};
    root = insert(7, root);

    int i = 0;
    for (; i < TEST_DATA_NUM; i++)
    {
        insert(data[i], root);
    }

    logprintf("---left root right---");
    ldr_print(root);

    tree_node_t *tmp = find_min(root);
    logprintf("%sfind_min()%s = %d", YELLOW, NORMAL, tmp->element);

    tmp = find_max(root);
    logprintf("%sfind_max()%s = %d", YELLOW, NORMAL, tmp->element);

    return 0;
}

tree_node_t *make_empty(tree_node_t *tree)
{
    if (NULL != tree)
    {
        make_empty(tree->left);
        make_empty(tree->right);
        free(tree);
    }

    return NULL;
}

tree_node_t *find(const node_value search, tree_node_t *tree)
{
    if (NULL == tree)
    {
        return NULL;
    }
    else if (search < tree->element)
    {
        return find(search, tree->left);
    }
    else
    {
        return find(search, tree->right);
    }

    return tree;
}

/**
 * 递归实现
 * */
tree_node_t *find_min(tree_node_t *tree)
{
    if (NULL == tree)
    {
        return NULL;
    }
    else if (NULL == tree->left)
    {
        return tree;
    }
    else
    {
        return find_min(tree->left);
    }
}

/**
 * 迭代实现
 * */
tree_node_t *find_max(tree_node_t *tree)
{
    if (NULL != tree)
    {
        while (NULL != tree->right)
        {
            tree = tree->right;
        }
    }

    return tree;
}

/**
 * 暂不处理重复元素
 * */
tree_node_t *insert(const node_value value, tree_node_t *tree)
{
    if (NULL == tree)
    {
        size_t size = sizeof(tree_node_t);
        tree = malloc(size);
        if (NULL == tree)
        {
            logprintf("out of space! 申请内存失败! need size: %ld", size);
            exit(1);
        }

        tree->element = value;
        tree->left = NULL;
        tree->right= NULL;
    }
    else if (value < tree->element)
    {
        tree->left = insert(value, tree->left);
    }
    else if (value > tree->element)
    {
        tree->right = insert(value, tree->right);
    }
    else
    {
        /** 等于的情况不处理 */
        ;
    }

    return tree;
}

