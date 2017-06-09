<?php

namespace BlokBundle\Cache;

interface CacheInterface {


	public function has( $element );

	public function set( $key, $item );

	public function get( $key );

	public function remove( $key );

	public function replaceKey( $ke, $new_key );

	public function close();

	public function count();

	public function counter();

}