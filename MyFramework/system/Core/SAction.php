<?

  namespace System\Core;

  use System\Exception\SHTTPException;


  class SAction {




    public function runController( $contName, $action )
    {

 
       try {
         

          if(!class_exists( $contName )) throw new SHTTPException( 'Such a class is not found in the file' );
          

          $cont = new $contName;


          if(!method_exists( $contName, $action )) throw new SHTTPException( 'Such a action is not found in the controller' );


          $cont -> onBegin( );

          $cont -> $action( );

          $cont -> onEnd( );

       } catch(SHTTPException $e) {


          (new SHTTPException) -> errormessage( $e-> getFile() , $e -> getMessage(), $e -> getLine() );

 
      }

    }


    public function runDeafaultController( $contName, $action)
    {



      $this -> runController( $contName, $action );



    }


  }