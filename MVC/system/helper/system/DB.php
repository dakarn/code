<?php

namespace Helper\System;

class DB {


	public static $instance = null;
	public static $connect = null;

	private function  __construct(){ }

	private function __clone(){ }

	public static function getInstance( $data, $username, $password )
	{

		if( self::$instance === null )
		{
			self::$instance = new self();

			self::$connect = new \PDO( $data, $username, $password );
			self::$connect->setAttribute(\PDO::ATTR_ERRMODE, \PDO::ERRMODE_EXCEPTION);
		}

		return self::$instance;
	}


}