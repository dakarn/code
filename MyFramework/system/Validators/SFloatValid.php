<?

 namespace System\Validators;


 class SFloatValid {


    


   public function set( $text )
   {




     if(!filter_var( $text, FILTER_VALIDATE_FLOAT ))
     {


       return false;


     } else {


       return true;


     }




   }



 }