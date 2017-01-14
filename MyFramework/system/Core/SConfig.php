<?

 namespace System\Core;

 use System\Exception\SParamException;


 class SConfig {


    public static $deafultController;

    public static $extensionTemplate;

    public static $logwrite;

    public static $param_list = [];



   public function parseConfig( )
   {


     include_once('config/config.dat');


     self::$logwrite = $config['log_write'];

     self::$deafultController = $config['application']['defaultController'];

     self::$extensionTemplate = $config['extension_template'];

     


    

   }



   public static function getParam( $param )
   {

     try {



       if(!isset( self::$$param )) throw new SParamException( 'The call is not an existing parameter config' );
      

         return self::$$param;



      } catch(SParamException $e) {


          (new SParamException) -> errormessage($e-> getFile() , $e -> getMessage(), $e -> getLine() ); 

      }

   }


 }