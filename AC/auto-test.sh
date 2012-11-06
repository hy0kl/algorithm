#/bin/sh

work_path=$(pwd)
i=0
# 并发测试
# 使用了 libevent 的 ev_buf 后
# 并发能力有很大的提升
# 也从侧面验证内存管理方式为内存池
while ((i < 10))
do
    #echo $i
    nohup php api/cli-test.php &
    i=$((i + 1))
done
