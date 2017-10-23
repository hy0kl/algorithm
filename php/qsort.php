<?php
/**
 * @describe:
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
function qsort($arr) {
//快排

    if (count($arr) < 1) {
        return $arr;
    }

    $tmp = $arr[0];
    $left_arr  = array();
    $right_arr = array();

    for ($i = 1; $i < count($arr); $i++) {
        if ($arr[$i] > $tmp) {
            $right_arr[] = $arr[$i];
        } else {
            $left_arr[] = $arr[$i];
        }
    }

    return array_merge(qsort($left_arr), array($tmp), qsort($right_arr));
}

$input  = [9, 12, 3, 45, 89, 1, 234, 127, 1024];
$output = qsort($input);
print_r($output);
/* vim:set ts=4 sw=4 et fdm=marker: */

