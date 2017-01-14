<?

 namespace System\Validators;



 class SValidationForm {


    private $callbackList = [];

    private $method;

    private $listType = [];
   
    public $attributes;

    private $errorCount = 0;

    private $errorList = [];



   public function is_validation( )
   {

      $class = '';
      
      foreach( $this -> listType as $k => $v )
      {


         if(empty( $yourclass ))
         {

 
            $validclass = '\\System\\Validators\\S'.$v[1].'Valid';


         } else {


            $validclass = '\\System\\Validators\\'.$v[3];

            
         }

           
         if(!$valid = ( new $validclass ) -> set( $_POST[ $v[0] ] ))
         {


           $this -> errorCount++;
 
           $this -> errorList[ $v[0] ] = $v[2];


           
           if(isset( $this -> callbackList[$k] ) && $this -> callbackList[$k][2] == 'error')
           {

           
             

             eval( $this -> callbackList [$k][3]);


           }


         } else {



           if(isset( $this -> callbackList[$k] ) && $this -> callbackList[$k][2] == 'not error')
           {

 
             //if($this -> callbackList[$k][0] != ''){ $class = (new $this -> callbackList[$k][0]()); }
           
             //$class -> $this -> callbackList[$k][3];



           }


         }


       

      }


      return $this -> errorCount == 0 ? true: false;

   }



   public function methodCheck( $method )
   {

      
      $this -> method = $method;

      return $_SERVER['REQUEST_METHOD'] === $method ? true: false;
      


   }



   public function count( )
   {


      return $this -> errorCount;
      

   }



   public function setCallback( $id, $class, $function, $typeResult, $param = '' )
   {



     $d = $function.'('.implode( ',' , $param ).');'; 


     if(!empty( $this -> listType[$id] )) $this -> callbackList[ $id ] = [ $class, $function, $typeResult, $d ];

    
     return $this;


   }



   public function getErrors( )
   {


      return $this -> errorList;
      

   }


   public function addRules( $name, $type, $textError , $yourclass = '' )
   {


     $this -> listType[] = [ $name , ucfirst( $type ), $textError, $yourclass ];

     return $this;


   }




 }