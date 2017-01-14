<?


 namespace System\Lang;


 use System\Exception\SParamException;


 class SLang {



    private static $locale;

    private static $file;
 
    



   public static function get( $word )
   {


      


      try {



         if(!file_exists( 'application/language/'.self::$locale.'/'.self::$file ))
         {

            throw new SParamException( 'Translation file " '.self::$file.' " is not found' );

         }


         include( 'application/language/'.self::$locale.'/'.self::$file );


         if(!isset( $$word )) throw new SParamException( 'Not found such a linguistic variable in the dictionary' );

         return $$word;


      } catch( SParamException $e ) {


        (new SParamException) -> errormessage( $e-> getFile() , $e -> getMessage(), $e -> getLine() );
     
      }


   }



   public static function fileLib( $file )
   {


     self::$file = $file;


   }



   public static function locale( $locale )
   {


     self::$locale = $locale;

     return new SLang;


   }



 }