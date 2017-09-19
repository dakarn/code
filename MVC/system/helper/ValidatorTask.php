<?php

namespace Helper;


class ValidatorTask {


	private $allow_ext = 'gif|png|jpg';

	private $errors = [
		'Не заполнено имя.',
		'Не верно заполнен E-mail.',
		'Не заполнен текст задания.',
		'Файл с таким расширением нельзя загружать.',
		'Вы не зарузили изображение.',
	];

	public function validate()
	{

		$errors = [];

		if( empty( $_POST['username'] ) )
		{
			$errors[] = $this->errors[0];
		}

		if( empty( $_POST['text_task'] ) )
		{
			$errors[] = $this->errors[2];
		}

		if( !filter_var( $_POST['email'], FILTER_SANITIZE_EMAIL ) )
		{
			$errors[] = $this->errors[1];
		}

		if( empty( $_FILES['picture']['name'] ) )
		{
			$errors[] = $this->errors[4];
		}

		if( !preg_match( '/\.('.$this->allow_ext.')$/i' , $_FILES['picture']['name'] ) )
		{
			$errors[] = $this->errors[3];
		}

		if( count( $errors ) > 0 ) { return $errors; }

		return true;

	}

}