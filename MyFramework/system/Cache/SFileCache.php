<?

 namespace System\Cache;



 class SFileCache {


    private $fp;


   public function __construct( )
   {

     $this -> fp = fopen( 'cache/cache.dat', 'a+' );


   }


   public function close( )
   {


     fclose( $this -> fp );

   }




   public function get( )
   {




   }



   public function set( )
   {




   }



   public function remove( )
   {




   }


 }