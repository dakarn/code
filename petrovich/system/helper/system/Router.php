<?php

namespace Helper\System;

class Router {


	public static $prefix_action = 'Action';


	private function runRoute($value)
	{

		$classname = '\\'.str_replace( ':', '\\', $value['controller'] );
		$action = $value['action'].self::$prefix_action;

		$controller = new $classname();
		$controller->$action();
	}

	public static function parseRoute($router, $path)
	{

		$find = false;

		foreach( $router as $key => $value )
		{

			if( isset( $value['path']) && $value['path'] == $path )
			{
				static::runRoute($value);
				$find = true;
				return true;
			}

		}

		if( !$find )
		{
			static::runRoute( end( $router ) );
			return true;
		}

	}

}