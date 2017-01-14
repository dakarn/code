<?

  function __autoload( $classname )
  {

     include_once( str_replace( '\\', '/', ROOT.''.SYS.'/'.$classname.'.php' )); 
  
  }


  $loadTraits = array(

    'System\Core\SRoute',
    'System\Validators\SValidRoute',
    'System\Core\SController',


  );