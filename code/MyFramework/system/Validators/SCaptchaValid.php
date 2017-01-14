<?

 namespace System\Validators;


 class SCaptchaValid {



   public function set( $text )
   {


     if( $text == $_SESSION['captcha'] )
     {


       return true;


     } else {


       return false;


     }


   }





 }