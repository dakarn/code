<?

 namespace System\Core;

 use System\Exception\SHTTPException;



 abstract class SController extends SBaseFunction {





   public function __set( $name, $value )
   {


     SView::addVariable( $name, $value );

    
   }




   public function __get( $name )
   {


     return SView::$list_variable[$name];


   }



   public function renderFile( $file, $variable = array() )
   {



     try {



       if(!file_exists($file)) { throw new SHTTPException( 'File not found to connect' ); }

       include( ROOT.'/'.SYS.'/'.$file );



     } catch(SHTTPException $e) {


       (new SHTTPException) -> errormessage( $e-> getFile() , $e -> getMessage(), $e -> getLine() );


     }




   }



   public function onBegin( ) { }


   public function onEnd( ) { }


 }


?>