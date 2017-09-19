<?

 define( 'ROOT', $_SERVER['DOCUMENT_ROOT'] );


 
 $systemDir = 'system';


 $configDir = 'config/';


 include_once( $systemDir.'/CoreRun.php' );


 $app = new APP;


 include_once( $systemDir.'/Loader.php' );


 $app -> runnable();


 