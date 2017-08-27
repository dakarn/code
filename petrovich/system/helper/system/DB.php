<?php

namespace Helper\System;

class DB {


	public static $instance = false;
	public static $connect = null;

	private function  __construct() {}

	private function __clone() {}

	public static function get()
	{

		if( !self::$instance )
		{
			self::$instance = true;
			self::$connect =  new \mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
			self::$connect->set_charset('utf8');
		}

		return self::$connect;
	}


}