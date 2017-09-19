<?php

namespace Controller;

use Helper\System\Render;
use Helper\ValidatorEdit;
use Model\Task;


if( !isset( $_SESSION['admin'] ) ) { header(  'Location: /testbeejee/admin/auth/'); exit(); }


class AdminController {


	private $url_redirect = '/testbeejee/admin/';
	private $errors = [];

	public function EditTaskAction()
	{

		if( $_SERVER['REQUEST_METHOD'] == 'POST' )
		{

			$validator = new ValidatorEdit();
			$valid = $validator->validate();

			if ( $valid === true )
			{
				$task = new Task;
				$task->SaveEditTask();

				header( 'Location: '.$this->url_redirect );
				exit();

			} else {

				header( 'Location: '.$this->url_redirect ); }
				exit();

		}

	}

	public function ListTaskAction()
	{

		$page = 1;

		if( !empty( $_GET['page']) )
		{
			$page = '&page='.$_GET['page'];
		}

		$task = new Task;
		$list_task =  $task->ListTask();


		return new Render( 'admin/list-task.html', [ 'listing' => $list_task, 'page' => $page ] );
	}
}



