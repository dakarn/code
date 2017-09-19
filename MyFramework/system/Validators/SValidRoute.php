<?

 namespace System\Validators;

 
 class SValidRoute {


   private $result = false;

   public $controller;

   public $action;



   public function getResult( )
   {

     return $this -> result;

   }



   public function rules( $request )
   {

      
     include_once('config/routes.dat');


     $requestes = explode( '/', $request);


     foreach( $routes as $key => $value )
     {


       $exp = explode( '/', $key);

      
       //foreach( $exp as $k => $v )
       //{



         //preg_match( '/\{(.*)\}/', $v, $rules );



         //if(isset( $rules[1] ))
         //{


          // if(preg_match( '/'.$value[ $rules[1] ].'/' ,  $requestes[1] )) echo $requestes[2];

         //}



       //}


       if($exp[0] == '{controller}' && $exp[1] == '{action}')
       { 



         $this -> controller = ucfirst($requestes[1]);


         $_GET['controller'] = strtolower( $this -> controller );


         $_GET['action'] = strtolower( $requestes[2] );



         if(file_exists( 'application/controller/'.$this -> controller.'Controller.php' ))
         {


           $contName = '\\Application\\Controller\\'.$this -> controller.'Controller';

           


           if(class_exists($contName))
           {


             $action = 'action'.ucfirst($requestes[2]);


             $this -> result = array( 'controller' => $this -> controller.'Controller', 'action' => $action );
 


           }


         }


       }
       


     }


     return $this -> result;


   }




 }