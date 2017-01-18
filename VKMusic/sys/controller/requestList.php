<?

 function requestList( )
 {

   include( '../sys/VKload.php' );


   $vk = new VKload( $_POST['title'] );

   $js = $vk->getMusic( );

   $json = json_encode( $js );

   $count = $vk->getCount()[1]; 


   if( $count == 0 )
   {

       $success = '{"success": 0,"message": "По вашему запросу ничего не найдено!"}';
       echo $success;

  } else {

       $success = '{"success": 1,"count": '.$count.', "list":';
       
       echo $success.$json.'}';

  } 

   

 }