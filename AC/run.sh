#!/bin/sh

program="./src/acsmx"
data_path="./test"

$program $data_path/simple.txt abc test
$program $data_path/gpl.txt copy software free gpl -nocase
$program $data_path/ir.htm 论文 课题 领域 学术

$program $data_path/filter.txt sb "free Tibet" "free  Tibet" 西藏 胡 -nocase

#$program $data_path/Bible.txt grievous continually ungirded
