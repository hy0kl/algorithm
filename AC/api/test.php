<?php
define('WORK_PATH', dirname(__FILE__));
require(WORK_PATH . '/machinePatrol.php');
$post_data = array(
    'word' => '',
);
if (isset($_POST) && count($_POST) && isset($_POST['word']))
{
    $post_data = $_POST;
}
?>

<div class="webui">
<form action="<?php echo $_SERVER['SCRIPT_NAME'];?>" method="post">
<div>
    <textarea name="word" rows="20" cols="60"><?php echo htmlspecialchars($post_data['word']); ?></textarea>
</div>
<input type="submit" /> <input type="reset" />
</form>
</div>

<div class="response">
<?php
$response = machinePatrol::getPatrol($post_data);
if (0 == $response['error'] && count($response['stat']))
{
    echo '<pre>';
    print_r($response['stat']);
    echo '</pre>';
}
?>
</div>
