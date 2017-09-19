<?


 namespace System\Cache;



 class SMemCache {


     private $mem;


   public function __construct( $ip, $port )
   {


     $this -> mem = new Memcache;

     $this -> mem -> connect( $ip, $port);
 

   }



   public function close(  )
   {


    
     $this -> mem -> close( );

     
 

   }


   public function get( $name )
   {


    
     return $this -> mem -> get( $name );

     
   }



   public function remove( $name )
   {


    
     $this -> mem -> delete( $name );

     
   }



   public function set( $name, $value )
   {


    
     $this -> mem -> add( $name, $value, false, 0 );

     
 

   }



 }