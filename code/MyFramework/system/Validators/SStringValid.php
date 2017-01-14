<?

 namespace System\Validators;


 class SStringValid {


    


   public function set( $text )
   {




     if(is_string( $text ))
     {


       return true;


     } else {


       return false;


     }




   }



 }