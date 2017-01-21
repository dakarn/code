<?

 function requestList( )
 {


   include( '../sys/VKload.php' );


   $offset = abs( intval( $_POST['offset'] ) );


   $vk = new VKload( $_POST['title'] );

   $js = $vk->getMusic( $offset );


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