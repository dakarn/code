<?

  $action = $_POST['action'];

  if( file_exists( '../sys/controller/'.$action.'.php' ) )
  {

     include('../sys/controller/'.$action.'.php');

     if( function_exists( $action ) )
     {

        $action();       

     }


  }
