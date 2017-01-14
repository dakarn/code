<?

 namespace Application\Model;

 use \System\Database\SDBConnection as DB;



 class ReadUser {




  public function getUser( )
  {

    return DB::init( ) -> Builder( )

      -> select() 
      -> from( 'user' )
      -> limit( 1 )
      -> run( );




  }


   public function get( )
  {

    return DB::init( ) -> Builder( )

      -> select() 
      -> from( 'user' )
      -> limit( 1 )
      -> run( );




  }


 }