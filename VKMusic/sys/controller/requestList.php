<?

 function requestList( )
 {

   include( '../sys/VKload.php' );


   $vk = new VKload( $_POST['title'] );

   $js = $vk->getMusic( abs( intval( $_POST['offset'] ) ) );

   $json = json_encode( $js );

   $count = $vk->getCount()[1]; 


   if( $count == 0 )
   {

       $success = '{"success": 0,"message": "�� ������ ������� ������ �� �������!"}';
       echo $success;

  } else {

       $success = '{"success": 1,"count": '.$count.', "list":';
       
       echo $success.$json.'}';

  } 

   

 }