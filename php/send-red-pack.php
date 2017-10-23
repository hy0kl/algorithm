<?php
/**
 * @describe: 微信随机红包的实现
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
/**
 * 算法的思路: 在一个从 0 到 $money 的环上,随机出 $number 个不重复的数
 * 然后将这些数排序,遍历它们,依次相减即可解决
 * */
function generate_conf($money, $number) {
    assert($money > 1);
    assert($number > 0);

    $conf = array();
    $cntr = array();

    for ($i = 0; count($cntr) < $number - 1; $i++) {
        $rand = mt_rand(1, $money);
        if ($rand == $money || isset($cntr[$rand])) {
            continue;
        } else {
            $cntr[$rand] = 1;
        }
    }
    $cntr[$money] = 1;
    ksort($cntr, SORT_NUMERIC);
    //print_r($cntr);
    $iter = 0;
    foreach ($cntr as $rd => $val) {
        $conf[] = $rd - $iter;
        $iter = $rd;
    }

    return $conf;
}

print_r(generate_conf(100, 3));
/* vim:set ts=4 sw=4 et fdm=marker: */

