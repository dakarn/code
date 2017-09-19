<?

 namespace System\Cache;



 class SMemoryCache {


     private $cache = [];


   public function set( $name , $value )
   {


     $this -> cache[$name] = $value;


   }



   public function listCache( )
   {



      return $this -> cache;

   }


   public function get( $name )
   {


     return isset( $this -> cache  [ $name ] ) ? $this -> cache [ $name ]: false;


   }



   public function remove( $name , $value )
   {


      unset( $this -> cache  [ $name ] );


   }




 }