<?

 namespace System\Validators;


 class SIntValid {



   public function set( $text )
   {


     if(is_int( $text ) || is_numeric( $text ))
     {


       return true;


     } else {


       return false;


     }


   }





 }