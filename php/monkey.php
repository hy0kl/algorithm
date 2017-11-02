<?php
/**
 * @describe: 经典猴子出圈游戏 约瑟夫环
 * @see: https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
function out_of_game($total, $cond)
{
    assert($total > 0);
    assert($cond > 0);

    $circle = array();
    for ($i = 0; $i < $total; $i++) {
        $circle[] = $i + 1;
    }

    $number = 0;
    while (1) {
        if (count($circle) == 1) {
            break;
        }

        foreach ($circle as $index => $v) {
            $number++;
            if (0 == $number % $cond) {
                unset($circle[$index]);
            }
        }
    }

    return array_pop($circle);
}

echo 'The monkey King is: ', out_of_game(10, 3), PHP_EOL;

// 数学法
// 编号从0开始,如果编号要从1开始,结果要加1
function josephus($n, $k) {
    $s = 0;
    for ($i = 2; $i <= $n; $i++) {
        $s = ($s + $k) % $i;
    }

    return $s;
}
echo 'The monkey King is(begin with 0): ', josephus(10, 3), PHP_EOL;
/* vim:set ts=4 sw=4 et fdm=marker: */

