<?php

namespace BlokBundle\Cache;

use BlokBundle\Cache\CacheInterface;


class FileSystemCache implements CacheInterface {


	private $file;
	private $dir = 'cache-file/', $ext = '.cache';
	private $delim = '<key>', $keys = [];
	private $cache, $is_close = true;
	private $errors = [];


	private function checkExistsKey( $key )
	{
		return isset( $this->keys[$key] ) ? true : false;
	}


	private function checkExistsCache( $cache )
	{
		return file_exists( __DIR__.'/'.$this->dir.$cache.$this->ext ) ? true : false;

	}


	private function loadAll()
	{

		 while ( ($buffer = fgets( $this->file, 500 ) ) !== false)
		 {
		 	 $exp = explode( $this->delim, $buffer );

		 	 if( isset( $exp[1]) )
		 	 {
			     $this->keys[$exp[0]] = str_replace(';', '', $exp[1]);
		     }
		 }

	}


	public function __construct( $cache )
	{

		if( !$this->checkExistsCache( $cache ) )
		{
			$this->file = fopen(__DIR__.'/'.$this->dir . $cache . $this->ext, 'w+');

		} else {

			$this->file = fopen(__DIR__ . '/' . $this->dir . $cache . $this->ext, 'r+');
		}

		$this->cache = $cache;
		$this->is_close = false;
		$this->loadAll();

	}


	public function replaceKey( $key, $new_key )
	{

		$value = $this->keys[$key];
		$this->remove( $this->keys[$key] );
		$this->keys[$new_key] = $value;

		return $this;
	}


	public function get( $key )
	{

		if( !isset( $this->keys[$key] ) ) return false;

		return $this->keys[$key];
	}


	public function has( $element )
	{
		return $this->checkExistsKey( $element ) ? true : false;
	}


	public function remove( $key )
	{
		if( isset( $this->keys[$key] ) ){ unset( $this->keys[$key] ); }
		return true;
	}


	public function flush()
	{

		if( count( $this->keys ) == 0 || $this->is_close ) return false;

		$all_data = '';

		foreach( $this->keys as $key => $value )
		{
			$all_data .= $key.$this->delim.str_replace( PHP_EOL, '', $value ).';'.PHP_EOL;
		}

		fseek( $this->file , 0 );
		fwrite( $this->file, $all_data );
		$this->close();
		return $this;
	}


	public function close()
	{
		if( !$this->is_close )
		{
			fclose( $this->file ); $this->is_close = true; return true;
		}

		return false;
	}

	public function clearAll()
	{

		chdir(__DIR__.'/'.$this->dir );
		$listfile = glob( "*".$this->ext."" );

		foreach( $listfile as $value )
		{
			$this->file = fopen(__DIR__.'/'.$this->dir . $listfile, 'w+');
		}

		chdir(__DIR__ );
		return true;
	}


	public function clear( $cache )
	{

		$this->file = fopen(__DIR__.'/'.$this->dir . $cache.$this->ext, 'w+');
		return true;
	}


	public function set( $key, $item )
	{
		$this->keys[$key] = $item;
		return $this;
	}


	public function count()
	{
		return count( $this->keys );
	}


	public function getAll()
	{
		return $this->keys;
	}


	public function incrAndDecr( $key, $int )
	{

		$new_value = (int)$this->keys[$key];

		if( is_numeric( $new_value ) )
		{
			$this->keys[$key] = $new_value + $int;
		}

		return $this;
	}


	public function counter( $type, $key, $count = 1 )
	{
		$value = $type == 'incr' ? $count: ( $type == 'decr' ? -$count:0 );

		$this->incrAndDecr( $key, $value );

		return $this;
	}


}