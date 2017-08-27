<?php

namespace Controller;

use Helper\System\Render;

class AuthAdminController {


	private $url_redirect = URL.'admin/';
	private $config = PATH_SYSTEM.'config/config.php';


	public function indexAction()
	{

		include_once $this->config;

		if( $_SERVER['REQUEST_METHOD'] == 'POST' )
		{

			if( $admin_login == $_POST['login'] && $admin_pass == $_POST['pass'] )
			{

				$_SESSION['admin'] = 'admin_correct';
				header( 'Location: '.$this->url_redirect );
				exit();
			}

		}

		return new Render( 'admin/auth.html' );

	}

	public function logoutAction()
	{

		unset( $_SESSION['admin'] );
		session_destroy();

		header( 'Location: '.URL );
		exit();

	}

}
