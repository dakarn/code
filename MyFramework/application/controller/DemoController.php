<?

 namespace Application\Controller;

 use \System\Core\SController;

 use \System\Core\SView;

 use \System\Lang\SLang;

 use \Application\Model\ReadUser;

 use \System\Validators\SValidationForm;

 use \Application\Widgets\MenuWidget;



 class DemoController extends SController {





   public function actionIndex( )
   {    

     

     $lang = SLang::locale( 'ru' ) -> fileLib( 'index.php' );



     $this -> command = SLang::get( 'title' );

     $this -> test = SLang::get( 'test' );

   

     $constform = new \Application\Form\Form;


     $form = new SValidationForm;


     $form -> addRules( 'name' , 'empty' , 'Name is empty' ) -> addRules( 'password' , 'int' , 'Password is empty' );


     $form -> setCallback( 0 , '\\System\\Validators\\GG' , 's', 'not error', [] );




     if($form -> methodCheck( 'POST' ))
     {


       if($form -> is_validation())
       {


         $db = new ReadUser;

         $tt = $db -> getUser();

         $this -> list = $tt;

         print_r( $db -> get() );


         $cache = new \System\Cache\SCache;

         $cache -> open( 'memory' ) -> set( 'list', $tt );

         


       }



     }


     new SView( 'index', array( 'form' =>  $constform ,'title' => 'My Framework' ));

   }








 }