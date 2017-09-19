<?

 namespace System\Validators;


 class SBooleanValid {


    


   public function set( $text )
   {




     if(is_bool( $text ))
     {


       return true;


     } else {


       return false;


     }




   }



 }