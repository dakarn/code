<?

 namespace System\Helpers;

 class Paginator {



   private $count;

   private $page;

   private $page_col;

   private $count_ceil;

   static $call=false;

   private $list_page = [];

  
  private function __construct( ) { }



  public static function factory()
  {

    if(!self::$call)
    {
     
     self::$call = true;

     return new PN;

    }


  }


  public function page_start($count=0,$page_col=1)
  {

     $this -> count = $count;

     $this -> page_col = $page_col;

     if(isset($_GET['page'])){ $this -> page = abs(intval($_GET['page'])); } else { $this -> page = 1; }

     $this -> count_ceil = ceil($this -> count/$this -> page_col);

     if($this -> page > $this -> count_ceil || $this -> page==0)
     { 

      $this -> page = 1;

     }


     $onpage = $this -> page*$this -> page_col;

     $start = $onpage - $this -> page_col;

     return $start;
    
  }


  public function page_next($path)
  {

    
    if($this -> count > $this -> page_col)
    {
  
       $for1 = 0; 

       $for2 = 4;

       if($this -> page > 1) $for2 = $this -> page + 3; 

       if($this -> page > 2) $for1 = $this -> page - 3; 

       if($this -> page >= 5) $for1-=1; 

       if($this -> page-3 < $this -> count_ceil & $this -> page + 4 == $this -> count_ceil) $for2 = $for2 + 1; 


       if($this -> page > 5) echo '<a id=navi href='.$path.'&page=1>1</a>...'; 

       if($this -> page >= 3 & $for1 >= 1 & $this -> page < 6) echo '<a id=navi href='.$path.'&page=1>1</a>'; 
     

       for($i = $for1; $i < $for2; $i++)
       {
      
         if($this -> count_ceil > $i)
         {
       
           echo '<a id='.(($this -> page-1==$i) ? 'navi_active': 'navi').' href='.$path.'&page='.($i+1).'>'.($i+1).'</a>';

         }

       }

       if($for2+1 < $this -> count_ceil)
       { 

         echo '...<a id=navi href='.$path.'&page='.$this -> count_ceil.'>'.$this -> count_ceil.'</a>'; 

       }

    }

   
  }
   
  return $this -> list_page;

}
