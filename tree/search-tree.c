/**
 * @describe:
 * @author: hy0kle@gmail.com
 * */

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
tree_node_t *find(const node_value search, const tree_node_t *tree);
tree_node_t *find_min(const tree_node_t *tree);
tree_node_t *find_max(const tree_node_t *tree);
tree_node_t *insert(const node_value value, const tree_node_t *tree);
tree_node_t *delete(const node_value value);

int main(int argc, char *argv[])
{

    return 0;
}

