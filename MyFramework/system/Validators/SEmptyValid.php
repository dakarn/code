<?

 namespace System\Validators;


 class SEmptyValid {


    


   public function set( $text )
   {




     if(empty($text))
     {


       return false;


     } else {


       return true;


     }




   }



 }