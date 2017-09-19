<?

 namespace System\Cache;

 use \System\Exception\SHTTPException;


 class SCache {


    
      private $type;

      private $cache;



    public function set( $name, $value )
    {


      $this -> cache -> set( $name, $value );


    }



    public function get( $name )
    {


      return $this -> cache -> get( $name );


    }



    public function open( $type )
    {


      $this -> type = $type;

      $class = '\\System\\Cache\\S'.ucfirst( $type ).'Cache';

       
      try {



        if(!class_exists( $class ))  throw new SHTTPException( 'Unknown driver for caching' );


        $this -> cache = new $class;


        return $this;



      } catch(SHTTPException $e) {


        (new SHTTPException) -> errormessage( $e-> getFile() , $e -> getMessage(), $e -> getLine() );


      }


     

    }



    public function close( $type )
    {




    }



 }