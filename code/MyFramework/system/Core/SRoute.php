<?

 namespace System\Core;

 use System\Validators\SValidRoute;

 use System\Exception\SHTTPException;

 
 interface Route {


   public function validation( $request, $class );


 }


 class SRoute implements Route {


    public static $controller;
    public static $action;


   public function validation( $request, $valid )
   {


           $valid -> rules( $request );

           $result = $valid -> getResult( );

           try {




             if( $result == false ) throw new SHTTPException( 'The controller at the " /'.$_GET['controller'].'/'.$_GET['action'].' " is not found' );


             self::$controller = $result['controller'];

             self::$action = $result['action'];


             $action = new SAction;

             $action -> runController( '\\Application\\Controller\\'.$result['controller'], $result['action'] );  

             

           } catch(SHTTPException $e){

              (new SHTTPException) -> errormessage( $e-> getFile() , $e -> getMessage(), $e -> getLine() );

           }




   }

   



 }