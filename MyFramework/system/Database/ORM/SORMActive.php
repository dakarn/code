<?

 namespace System\Database\ORM;

 use \System\Database\SDBQuery;

 use \System\Database\SDBConnection as DB;



 class SORMActive implements IORMActive {



    private $db = null;

    public $listColumns = [];

    private $tableName; 

    private $key; 

    private $classDB;



   public function __construct( )
   {

      $this -> classDB = DB::init();

      $this -> tableName = $this -> tableName();

      $this -> key = $this -> primaryKey();


      $this -> db = DB::$db -> prepare( 'SHOW COLUMNS FROM user' ); 

      $this -> db -> execute(); $list = $this -> db ->fetchAll();

     
      foreach( $list as $k => $v )
      {

         $this -> listColumns[ $v[ 'Field' ] ] = '';

      }
      




   }


   
   public static function factory( )
   {




   }



   public function __set( $name, $value )
   {


      $this -> listColumns[ $name ] = $value;


   }



   public function __get( $name )
   {


      return $this -> listColumns[ $name ];


   }



   public function save( )
   {

   
      if(isset( $this -> listColumns[$this -> key] )) unset( $this -> listColumns[$this -> key] );

      $this -> classDB -> insert( $this -> tableName , array_keys($this -> listColumns) , $this -> listColumns );


   }


   public function findAll( $where = '' )
   {


     return $this -> classDB -> query( 'SELECT * FROM `'.$this -> tableName.'` '.$where.' ' ) -> readAll( );


   }


   
   public function findFirst( )
   {




   }


   public function findOne( $where )
   {


      return $this -> classDB -> query( 'SELECT * FROM `'.$this -> tableName.'` '.$where.' LIMIT 1' ) -> readOne( );


   }


   public function count( )
   {




   }


   public function tableName( )
   {


   }



   public function primaryKey( )
   {




   }


   public function update( )
   {


     $where = ''; $query = '';

     if(  $this -> key != '' && !empty( $this -> listColumns[$this -> key] )) $where = 'WHERE '.$this -> key.' = "'.$this -> listColumns[$this -> key].'" ';

     foreach( $this -> listColumns as $k => $v )
     {

       if(!empty( $v ) && $this -> key != $k) $query .= $k.' = "'.$v.'", ';

     }

     if(strpos( $query, ',' )) $query = substr( $query, 0, -2 );

     $this -> classDB -> query( 'UPDATE '.$this -> tableName.' SET '.$query.' '.$where ) -> execute();



   }






 }



 interface IORMActive {



   public function tableName( );

   public function primaryKey( );



 }