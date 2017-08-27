<?php

session_start();

define( 'PATH_SYSTEM', dirname($_SERVER['SCRIPT_FILENAME']).'/system/' );
define( 'TEMPLATE', PATH_SYSTEM.'template' );
define( 'URL', 'http://'.$_SERVER['HTTP_HOST'].'/petrovich/' );
define( 'DIR_PATH', '/petrovich/' );
define( 'COUNT_ON_PAGE', 5 );

define( 'DB_HOST', '****' );
define( 'DB_NAME', '****' );
define( 'DB_USER', '****' );
define( 'DB_PASSWORD', '****' );

include_once( PATH_SYSTEM.'config/router_maps.php' );
include_once( PATH_SYSTEM.'helper/system/LoaderClass.php' );

$loader = new Helper\System\LoaderClass();
$loader->loader();

if( !isset( $_GET['options'] ) )
{
	$_GET['options'] = '';
}

$path = str_replace( DIR_PATH, '', $_GET['options'] );

Helper\System\GET::set();
Helper\System\Router::parseRoute($router, $path);