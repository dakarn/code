<?

 namespace System\Database;

 use System\Exception\SDBException;

 
 class SDBConnection extends SDBQuery {



    public static $instance = false;

    public static $db = null;

    private $dbconfig = [];

    public static $dbs;


   public function Builder()
   {  

      return new SDBQueryBuilder;  

   }


   private function __construct( )
   {


      $config = $this -> parseDBConfig();


      try {



        self::$db = new \PDO( 'mysql:host='.$this -> dbconfig['host'].'; 
        dbname='.$this -> dbconfig['db'] , $this -> dbconfig['user'] , $this -> dbconfig['password'] );

 
        self::$db -> exec( 'set names '.$this -> dbconfig['charset'] );

   
      

      } catch(SDBException $e) {


        (new SDBException) -> errormessage( $e-> getFile() , $e -> getMessage(), $e -> getLine() ); exit;


     }

    

   }


   


   private function parseDBConfig( )
   {



     include_once('config/db.dat');


     $this -> dbconfig['host'] = $db['database']['host'];

     $this -> dbconfig['user'] = $db['database']['user'];

     $this -> dbconfig['password'] = $db['database']['password'];

     $this -> dbconfig['db'] = $db['database']['db'];

     $this -> dbconfig['charset'] = $db['database']['charset'];



   }



   public static function init( )
   {


     if( !self::$instance )
     {


       self::$instance = true;

       self::$dbs = new SDBConnection;

       return self::$dbs;


     } 

     return self::$dbs;


   }
 


 }