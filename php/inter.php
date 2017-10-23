<?php
/**
 * @describe: 已排序数组求交集
 * @other: 变种算法,已排序数组求有序合集
 * @author: Jerry Yang(hy0kle@gmail.com)
 * 复杂度是 O(m + n), 没有指针回溯
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

    $i = 0;
    $k = 0;
    for (/***/; $i < $f_cnt; /***/) {
        for (/***/; $k < $s_cnt && $i < $f_cnt; /***/) {
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

function union($a, $b) {
    $cnt_a = count($a);
    $cnt_b = count($b);

    $total = $cnt_a + $cnt_b;

    if ($a[0] > $b[0]) {
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

    //print_r($f_loop);
    //print_r($s_loop);
    //print_r($f_cnt);
    //print_r($s_cnt);
    //exit;

    $union_set[] = $f_loop[0];

    $i = 1; // 首元素小的数组索引
    $k = 0;

    for ($t = 0; $t < $total; /***/) {
        /** 其中长数组多出来的元素,直接追加 */
        if ($i >= $f_cnt && $k < $s_cnt) {
            for (/***/; $k < $s_cnt; $k++) {
                $union_set[] = $s_loop[$k];
            }
            break;
        }

        if ($k >= $s_cnt && $i < $f_cnt) {
            for (/***/; $i < $f_cnt; $i++) {
                $union_set[] = $f_loop[$i];
            }
            break;
        }

        /** 一次比较,将两个元素同时压入 */
        if ($f_loop[$i] < $s_loop[$k]) {
            $union_set[] = $f_loop[$i++];
            $union_set[] = $s_loop[$k++];
        } else {
            $union_set[] = $s_loop[$k++];
            $union_set[] = $f_loop[$i++];
        }
        $t += 2;
    }

    return $union_set;
}

$a = [1, 2, 34, 56, 78, 90, 110, 120, 256, 1024];
$b = [2, 56, 67, 89, 90, 128];

echo '$a = ';
print_r($a);
echo '$b = ';
print_r($b);

$inter_set = inter($a, $b);
echo '$inter_set = ';
print_r($inter_set);

$union_set = union($a, $b);
echo '$union_set = ';
print_r($union_set);
/* vim:set ts=4 sw=4 et fdm=marker: */

