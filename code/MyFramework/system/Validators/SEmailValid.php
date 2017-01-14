<?

 namespace System\Validators;


 class SEmailValid {


    


   public function set( $text )
   {




     if(!filter_var( $text, FILTER_VALIDATE_EMAIL ))
     {


       return false;


     } else {


       return true;


     }




   }



 }