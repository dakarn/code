<?


 namespace System\Logger;

 use \System\Core\SConfig;


 class SLogRun {





    public function __construct( $class, $message )
    {


        if( SConfig::getParam( 'logwrite') )  $class -> write( $message );

    }





 }