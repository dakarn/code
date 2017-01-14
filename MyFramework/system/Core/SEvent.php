<?

 namespace System\Core;



 class SEvent {



     private $events = [ 'formCreate', 'runWidget', 'loggerWrite' ];

     public static $listEvents = [];



   public function onEvent( $event , $functions )
   {



      $functions();



   }



   public function listEvent( )
   {



      return $this -> events;



   }




   private function run( )
   {




   }


 }