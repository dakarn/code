<?

function loadingFile()
{
	include('../sys/VKload.php');

	$vk  = new VKload('');
	$id  = intval($_POST['id']);
	$id1 = intval($_POST['id1']);

	$url  = $vk->getFile($id , $id1);
	$size = filesize($url);

	$success = '{"success": 1, "size": '.$size.', "url": "http://5.19.253.227/git/VKMusic/pub/'.$url.'"}';

	echo $success;
}
