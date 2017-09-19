<?php

namespace Helper\System;

class Render {


	private $path = TEMPLATE.'/';
	private $errors = [ 'errors/404.html' ];


	public function __construct($template, array $params = [])
	{

		if( !file_exists( $this->path.$template ) )
		{
			return include( $this->path.$this->errors[0] );
		}

		extract( $params );

		return include( $this->path.$template );
	}
}