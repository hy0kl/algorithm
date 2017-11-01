<?php
/**
 * @describe: 经典猴子出圈游戏
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
/* vim:set ts=4 sw=4 et fdm=marker: */

