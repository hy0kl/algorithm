#!/bin/bash
#set -x
abs_path=$(pwd)

# global vars
#start_time=$(date +"%Y-%m-%d:%H:%M:%S")
time_str=$(date +"%Y-%m-%d")
env_dir="data lua conf log"
pro_name="ac-mf"

Usage="$0 <runtype:start|stop>"
if [ $# -lt 1 ];
then
    echo "$Usage"
    exit 1
fi
runtype=$1

if [ "$runtype" != "start" ] && [ "$runtype" != "stop" ]
then
    echo "$Usage"
    exit 1
fi

# check evn dir
for dir in $env_dir
do
    if [ -d $dir ]
    then
        echo "'$dir' diretory is exists."
        # delete old file for space, befor 90 days.
        find "$dir" -type f -mtime +90 -exec rm {} \;
    else
        echo "'$dir' is NOT exists, create it ..."
        mkdir -p $dir
    fi
done

# global functions {
work_pids=""
function get_work_pids()
{
    work_pids=$(ps aux | grep $pro_name | grep -v grep | awk '{print $2}' | xargs)
}


# delete old file for space, befor 30 days.
#find "$work_path/data/" -type f -mtime +30 -exec rm {} \;

# stop process
if [ "stop" == "$runtype" ]; then
    echo "Stop process, please wait a moment. :)"

    get_work_pids
    kill_pids=$work_pids

    #no process need to quit
    if [ "$kill_pids" == "" ]; then
       echo "No process need to quit..."
       exit 0
    fi

    kill -s SIGKILL $kill_pids
    echo "kill SIGKILL: $kill_pids"

    exit 0
fi

# start
if [ "start" == "$runtype" ]; then
    get_work_pids
    if [ "$work_pids" == "" ]; then
        echo "It is no process working, so let it start to work."
    else
        echo "It has process working now, please stop it before start it."
        exit -1
    fi

    $abs_path/$pro_name -p "$abs_path"

    exit 0;
fi

