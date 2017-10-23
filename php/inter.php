<?php
/**
 * @describe: 已排序数据求交集
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
function inter($a, $b) {
    $cnt_a = count($a);
    $cnt_b = count($b);

    /** 外层循环使用小数据集 */
    if ($cnt_a > $cnt_b) {
        $f_loop = $b;
        $s_loop = $a;
        $f_cnt = $cnt_b;
        $s_cnt = $cnt_a;
    } else {
        $f_loop = $a;
        $s_loop = $b;
        $f_cnt = $cnt_a;
        $s_cnt = $cnt_b;
    }

    $inter_set = array();

    for ($i = 0; $i < $f_cnt;) {
        $k = 0; 
        for (/***/; $k < $s_cnt && $i < $f_cnt;/***/) {
            /** 如果相等,放入交集容器,同时将两个数组比较元素向前移动1位 */
            if ($f_loop[$i] == $s_loop[$k]) {
                $inter_set[] = $s_loop[$k];
                $i++;
                $k++;
            } elseif ($f_loop[$i] > $s_loop[$k]) {
                /** 如果外层元素大,将内层元素向前移动1位 */
                $k++;
            } elseif ($f_loop[$i] < $s_loop[$k]) {
                /** 如果内层元素大,将外层元素向前移动1位 */
                $i++;
            }
        }
    }

    return $inter_set;
}

$a = [1, 2, 34, 56, 78, 90, 110];
$b = [2, 56, 67, 89];

$inter_set = inter($a, $b);
print_r($inter_set);
/* vim:set ts=4 sw=4 et fdm=marker: */

