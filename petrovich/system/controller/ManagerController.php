<?php

namespace Controller;

use Helper\System\Render;
use Helper\ValidatorAddPage;
use Helper\ValidatorEditPage;
use Model\Page;

class ManagerController {


	private $errors = ['success'];
	private $message = [
		'Ошибка при удалений страницы.',
		'Ошибка при создании страницы.',
		'Ошибка при изменении страницы.',
	];

	public function addPageAction()
	{

		if( $_SERVER['REQUEST_METHOD'] == 'POST' )
		{

			if( ($validator = (new ValidatorAddPage())->validate()) === true )
			{

				if( $result = (new Page())->addPage() )
				{
					header('Location: ' . URL . 'item-page/?id=' . $result);
					exit();
				}

				$this->errors = $this->message[1];

			} else {

				$this->errors = $validator;

			}

		}

		return new Render( 'add-page.html', [ 'errors' => $this->errors ] );
	}

	public function deletePageAction()
	{

		$id = $_GET['id'] ?? 0;
		$id = abs( (int)$id );


		if( (new Page())->deletePage($id) === true )
		{
			header('Location: ' . URL);
			exit();
		}

		$this->errors = $this->message[2];

		return new Render( 'delete-page.html', [ 'errors' => $this->errors ] );
	}

	public function editPageAction()
	{

		$id = $_GET['id'] ?? 0;
		$id = abs( (int)$id );

		if( $_SERVER['REQUEST_METHOD'] == 'POST' )
		{

			if( ($validator = (new ValidatorEditPage())->validate()) === true )
			{

				if( $result = (new Page())->editPage($id) )
				{
					header('Location: ' . URL . 'item-page/?id=' . $id);
					exit();
				}

				$this->errors = $this->message[2];

			} else {

				$this->errors = $validator;

			}

		}

		$page = (new Page())->getPage($id);

		return new Render( 'edit-page.html', [ 'errors' => $this->errors, 'page' => $page ] );
	}

}