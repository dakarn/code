<?


 function loadingFile()
 {

   include( '../sys/VKload.php' );


   $vk = new VKload( '' );

   
   $id = intval($_POST['id']); $id1 = intval($_POST['id1']); 
  

   $url = $vk->getFile( $id , $id1 );

   $success = '{"success": 1,"url": "http://localhost/git/VKMusic/pub/'.$url.'"}';

   echo $success;



 }