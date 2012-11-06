<?php
define('WORK_PATH', dirname(__FILE__));
require(WORK_PATH . '/machinePatrol.php');

define('DATA_PATH', dirname(WORK_PATH) . '/src/data');
define('KEYWORDS_FILE', DATA_PATH . '/mf.keyword.txt');

$fp = fopen(KEYWORDS_FILE, 'r');
if (! $fp)
{
    echo 'Can open file: [' .  KEYWORDS_FILE . "]\n";
    exit();
}

while (! feof($fp))
{
    $line = fgets($fp, 1024);
    $post = array(
        'word' => $line,  
    );

    $response = machinePatrol::getPatrol($post);
    print_r($response);
}

fclose($fp);
