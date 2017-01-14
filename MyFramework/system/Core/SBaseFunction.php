<?

 namespace System\Core;


 abstract class SBaseFunction {




   public function redirect( $address ) 
   {


      header( 'Location: '.$address ); exit;


   }



   public function response( $text ) 
   {


     echo $text;


   }



   public function request( $path, $http , $otvet = 0 )
   {


      try {
      


        if(!empty($path))
        {

          if( !$otvet ) file_get_contents( $path ); else echo file_get_contents( $path );

        } else {

          throw new SHTTPException( 'Incorrect addres of request' );
      
        }



      } catch(SHTTPException $e) {


          (new SHTTPException) -> errormessage($e-> getFile() , $e -> getMessage(), $e -> getLine() ); 


      }

   }
  



   public function currentController( )
   {


     return str_replace( 'Controller','', SRoute::$controller) ;


   }


   public function currentAction( )
   {


     return str_replace( 'action','', SRoute::$action );


   }



 }
