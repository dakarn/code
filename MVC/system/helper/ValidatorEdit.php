<?php

namespace Helper;


class ValidatorEdit {


	private $errors = [
		'Не заполнен текст задания.',
	];

	public function validate()
	{

		$errors = [];

		if( empty( $_POST['text'] ) )
		{
			$errors[] = $this->errors[0];
		}

		if( count( $errors ) > 0 ) { return $errors; }

		return true;

	}

}