<?

 use System\Core\SConfig;


 class APP {


   private $is_dir;

   public $pathRequest;

   public $configDir;
   



   public static function run( $Class = '' )
   {


      if(!empty($class) && class_exists($class))
      {

        return new $Class; 

      } else {

   

      }


   }


   public function runnable( )
   {


    $this -> setWorkDir();

    $config = new SConfig; $config -> parseConfig();

    $route = new System\Core\SRoute;

    $route -> validation( $this -> pathRequest , new System\Validators\SValidRoute);


   }


   
   public function getWorkDir( )
   {

     
    return $this -> is_dir;

   }



   public function setWorkDir( )
   {



     $this -> is_dir = substr( $_SERVER['REQUEST_URI'] , 0 , strpos( $_SERVER['REQUEST_URI'], '/', 1 ) );


     define( 'SYS', $this -> is_dir );


     if( is_dir(ROOT.'/'.$this -> is_dir) ) 
     {

       $this -> pathRequest = str_replace( $this -> is_dir, '', $_SERVER['REQUEST_URI']);

     } else {



     }



   }






 }



?>