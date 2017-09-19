<?

  $action = $_POST['action'];

  try
  {

    if( file_exists( '../sys/controller/'.$action.'.php' ) )
    {


       include('../sys/controller/'.$action.'.php');


       if( function_exists( $action ) )
       {

         $action(); 
      

       } else {


         throw new Exception( '{ "success": 0 , "message": "Not found action!" }' );

       }


     } else {

       throw new Exception( '{ "success": 0 , "message": "Access Denied!" }' );

     }


  } catch( Exception $e ){

     echo $e->getMessage();

  }


     


 
