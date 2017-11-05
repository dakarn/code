<?

function requestList( )
{
	include('../sys/VKload.php');

	$offset = abs(intval($_POST['offset']));
	$vk     = new VKload($_POST['title']);
	$js     = $vk->getMusic($offset);
	$count  = $vk->getCount()[1];

	if ($count == 0) {

	   $success = '{"success": 0,"message": "�� ������ ������� ������ �� �������!"}';
	   echo $success;

	} else {

       $json    = arraytojson( $js );
       $success = '{"success": 1,"count": '.$count.', "list":';
       echo $success.$json.'}';
    }


}

function arraytojson( $js )
{
	$str   = '[';
	$count = count ($js);

	for ($i = 0; $i < $count; $i++) {

		$str .= '{"artist": "'.$js[$i]['artist'].'","title": "'.$js[$i]['title'].'","length": '.$js[$i]['length'].',"id": '.$js[$i]['id'].',"id1": '.$js[$i]['id1'].'},';
	}

	$str  = substr($str, 0, strlen($str) - 1);
	$str .= ']';

	return $str;
}
