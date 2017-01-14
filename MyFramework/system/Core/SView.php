<?

 namespace System\Core;

 use System\Exception\SHTTPException;



 class SView {



    public static $list_variable = [];



   public function widgetRender( $class )
   {



      $class = '\\'.str_replace( '.' , '\\', $class );


      
      try {



         if(!class_exists( $class )) throw new SHTTPException('This widget was not found'); 
      

         $class = new $class( );


       } catch(SHTTPException $e) {


        (new SHTTPException) -> errormessage($e-> getFile() , $e -> getMessage(), $e -> getLine() );


      }

     


   }


   public static function addVariable( $name , $value )
   {


     self::$list_variable [$name] = $value;


   }


   public function __construct( $view , array $variable = array() )
   {


      foreach(self::$list_variable as $key=>$value)
      {

       $$key=$value; 

      } 
      


      foreach($variable as $key=>$value)
      {

       $$key=$value; 

      } 


     



      try 
      {


        if(!file_exists( 'application/views/'.$view.'.php' )) throw new SHTTPException('Specified file type Views is not found'); 

        include_once('application/views/'.$view.'.php');


      } catch(SHTTPException $e) {


        (new SHTTPException) -> errormessage($e-> getFile() , $e -> getMessage(), $e -> getLine() );


      }


   }



 }