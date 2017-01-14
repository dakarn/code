<?

 namespace System\Database;

 
 class SDBQueryBuilder extends SDBQuery {



      private $sql;


    public function select( $column = '*' )
    {

       $this -> sql = 'SELECT '.$column;

       return $this;

    }



    public function from( $table )
    {


       $this -> sql .= ' FROM '.$table;


        return $this;

    }



    public function where( $where, $array = [] )
    {

       return $this;

    }



    public function run( )
    {


      return $this -> query( $this -> sql ) -> readAll( );


    }



    public function count( $col )
    {


       $this -> sql .= ' , COUNT('.$col.')';

       return $this;


    }


    public function limit( $limit )
    {

       $this -> sql .= ' LIMIT '.$limit;

       return $this;

    }



    public function selectDisct( $column )
    {

       $this -> sql .= ' SELECT DISTINCT '.$column;

       return $this;

    }




    public function join( $table, $condition )
    {


       $this -> sql .= ' JOIN '.$table.' ON '.$condition;

       return $this;

    }


    public function union( )
    {


       $this -> sql .= ' UNION';

       return $this;

    }



    public function leftJoin( $table, $condition )
    {

       $this -> sql .= ' LEFT JOIN '.$table.' ON '.$condition;

       return $this;

    }


    public function group( $col )
    {

        $this -> sql .= ' GROUP BY '.$col;

        return $this;
 
    }


    public function order( $col )
    {

        $this -> sql .= ' ORDER BY '.$col;

        return $this;

    }



    public function asc(  )
    {

      $this -> sql .= ' ASC';

      return $this;


    }

    public function desc(  )
    {

      $this -> sql .= ' DESC';

      return $this;


    }


 }