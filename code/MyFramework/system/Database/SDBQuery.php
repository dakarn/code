<?

 namespace System\Database;


 class SDBQuery {



     private $command;



   public function query( $sql )
   {


     $this -> command = SDBConnection::$db -> prepare($sql);


     return $this;


   }


   public function readAll(  )
   {


     $exec = $this -> command -> execute( );

     return $this -> command -> fetchAll( \PDO::FETCH_ASSOC );


   }



   public function readOne( $sql )
   {


     $exec = $this -> command -> execute( );

     return $this -> command -> fetchAll( \PDO::FETCH_ASSOC );



   }





   public function exec( )
   {



  

   }



   public function execute( )
   {


     $this -> command -> execute();

     return $this;


   }


   public function insert( $table , $columns = array() , $values = array() )
   {


     $this -> query("INSERT INTO ".$table." (`".implode( '`,`', $columns)."`) VALUES('".implode( "','", $values)."')");

     $this -> command -> execute( ); 

     return $this;


   }



   public function update( $table, $columns, $columns, $where )
   {


     $this -> query("UPDATE ".$table." SET ".$where."");

     $this -> command -> execute( ); 

     return $this;



   }




 }