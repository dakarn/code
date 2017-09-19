<?php

namespace Helper\System;

class GET {


	public static function set()
	{


		$query_string = parse_url( $_SERVER['REQUEST_URI'], PHP_URL_QUERY );

		if( empty( $query_string ) ) return;


		if( !strpos( $query_string, '&' ) )
		{

			$exp = explode( '=', $query_string );

			if( !isset( $exp[1] ) ) return;

			$_GET[$exp[0]] = $exp[1];


		} else if( strpos( $query_string, '&' ) )
		{

			$val = explode( '&', $query_string );

			foreach( $val as $key => $value )
			{

				$exp = explode('=', $value );

				if( !isset( $exp[1] ) ) return;

				$_GET[$exp[0]] = $exp[1];
			}

		}


	}

}