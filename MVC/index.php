<?php

session_start();

define( 'PATH_SYSTEM', $_SERVER['DOCUMENT_ROOT'].'/testbeejee/system/' );
define( 'TEMPLATE', PATH_SYSTEM.'template' );
define( 'PATH_SAVE', $_SERVER['DOCUMENT_ROOT'].'/testbeejee/public/picture/task/' );
define( 'URL', 'http://'.$_SERVER['HTTP_HOST'].'/testbeejee/' );

include( PATH_SYSTEM.'helper/system/LoaderClass.php' );

$loader = new \Helper\System\LoaderClass();
$loader->loader();

if( !isset( $_GET['options'] ) )
{
	$_GET['options'] = '';
}

$path = str_replace( '/testbeejee/', '', $_GET['options'] );

Helper\System\GET::set();
Helper\System\DB::getInstance( 'mysql:host=localhost;port=3306;dbname=beejee;charset=utf8', 'beejee', 'testbeejee' );


switch( $path )
{

	case '':

		$class = new \Controller\TaskController();
		$class->createTaskAction();

	break;
	case 'admin':

		$class = new \Controller\AdminController();
		$class->ListTaskAction();

	break;
	case 'admin/edit-task':

		$class = new \Controller\AdminController();
		$class->EditTaskAction();

		break;
	case 'admin/auth':

		$class = new \Controller\AuthAdminController();
		$class->indexAction();

	break;
	case 'admin/logout':

		$class = new \Controller\AuthAdminController();
		$class->logoutAction();

	break;
	default:

		$class = new \Controller\TaskController();
		$class->createTaskAction();

	break;

}
