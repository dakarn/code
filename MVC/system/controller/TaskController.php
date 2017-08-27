<?php

namespace Controller;

use Helper\System\Render;
use Helper\ValidatorTask;
use Model\Task;


class TaskController {


	private $errors = [ 'success' ];


	public function getErrors()
	{
		return $this->errors;
	}


	public function createTaskAction()
	{


		if( $_SERVER['REQUEST_METHOD'] == 'POST' ) {

			$validator = new ValidatorTask();
			$valid = $validator->validate();


			if ( $valid === true )
			{
				$task = new Task;
				$task->addTask();

			} else {

				$this->errors = $valid;
			}

		}

		return new Render( 'index.html', [ 'errors' => $this->errors ] );

	}

}
