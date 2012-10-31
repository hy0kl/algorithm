<?php
class machinePatrol
{
    static public $api = 'http://localhost:8668/?format=json';
    static public $time_out = 5;

    static public function getPatrol($para = array())
    {
        $res = array(
            'error' => 1,
        ); 

        if (isset($para['word']) && strlen($para['word']))
        {
            $json = machinePatrol::_getJson(machinePatrol::$api, $para);
            if (strlen($json))
            {
                $res = json_decode($json, true);
            }
        }

        return $res;
    }

    static protected function _getJson($api, $post = array())
    {
        $json = '';

        if (!(is_array($post) && count($post) && isset($post['word']) && strlen($post['word'])))
        {
            return $json; 
        }

        $post_data = '';
        foreach ($post as $k => $v)
        {
            $post_data .= "{$k}={$v}&";
        }

        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $api);
        /**
         *     Note: Passing an array to CURLOPT_POSTFIELDS will encode the data as multipart/form-data, while passing a URL-encoded string will encode the data as application/x-www-form-urlencoded. 
         *         */
        curl_setopt($ch, CURLOPT_POST, 1);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $post_data);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        //curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_TIMEOUT, machinePatrol::$time_out);
        $json = curl_exec($ch);
        //echo $json . "\n";
        if (curl_errno($ch)) 
        {
            $json = '';
        }
        curl_close($ch);

        return $json;
    }
}

$para = array(
    'word' => 'test for 这是有一些敏感词,比如: 西单. 行房, sb',
    //'word' => '这行没有敏感词',
);
//machinePatrol::$time_out = 1;
print_r(machinePatrol::getPatrol($para));
