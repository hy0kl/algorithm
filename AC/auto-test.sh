#/bin/sh

work_path=$(pwd)
i=0
while ((i < 10))
do
    #echo $i
    nohup php api/cli-test.php &
    i=$((i + 1))
done
