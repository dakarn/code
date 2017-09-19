<?

 namespace System\Helpers;

 class Session {




   public static function set( $key , $value )
   {


      $_SESSION[ $key ] = $value;

   }



   public static function delete( $key )
   {

      unset( $key );

   }



   public static function get( $value )
   {


      return $_SESSION[ $value ];

   }



 }