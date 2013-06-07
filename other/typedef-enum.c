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

typedef enum
{
    GameSceneLayerTagGame = 1,
    GameSceneLayerTagInput,
    
} GameSceneLayerTags;

typedef enum
{
    GameSceneNodeTagBullet = 1,
    GameSceneNodeTagBulletSpriteBatch,
    GameSceneNodeTagBulletCache,
    GameSceneNodeTagShip,
    
} GameSceneNodeTags;

int main(int argc, char *argv[])
{
    printf("GameSceneNodeTags->GameSceneNodeTagBulletSpriteBatch: %d\n", GameSceneNodeTagBulletSpriteBatch);

    GameSceneNodeTags node_tag = GameSceneNodeTagShip;
    printf("node_tag: %d\n", node_tag);

    return 0;
}

