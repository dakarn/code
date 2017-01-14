<?


 namespace Application\Form;

 use \System\Form\SForm;



 class Form extends SForm {



   public function __construct( )
   {

      $this ->beginForm( '' , 'POST' , '' );

      $this -> Builder()

         -> addElement( 'text' , '' , 'name', [ 'transfer' => 2 ] ) 
         -> addSelect( 'text' , [ 'g' => 'ff', 'ww' => 'dd' ], [ 'size' => 1, 'transfer' => 2 ] )
         -> addElement( 'password' , '' , 'password', [ 'transfer' => 2 ] )
         -> addElement( 'submit' , 'OK' , 'click' );

      $this ->endForm( );

   }








 }