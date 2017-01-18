<?

 function requestList( )
 {

   include( '../sys/VKload.php' );


   $vk = new VKload( $_POST['title'] );

   $success = '{"success": 1,"list":';

   $json = json_encode( $vk->getMusic( ) );

   echo $success.$json.'}';

 }