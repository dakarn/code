<?php

namespace Helper;

use Helper\System\DB;

class Pagination
{

	private $count_list = 3;
	private $page;
	private $count = 0;
	private $word = [ 'Назад', 'Далее' ];
	private $url;

	public static $instance = null;


	private function  __construct(){ }

	public static function getInstance()
	{

		if( self::$instance === null )
		{
			self::$instance = new self();
		}

		return self::$instance;
	}

	public function setCount($count)
	{
		$this->count = $count;
		return $this;
	}

	public function setUrl($url)
	{
		$this->url = $url;

		if( !isset( $_GET['page'] ) ){ $_GET['page'] = 1; }

		$this->page = abs( $_GET['page'] );

		if( empty( $_GET['page'] ) ){ $this->page = 1; }
		if( !isset( $_GET['page'] ) ){ $this->page = 1; }
		if( !empty( $_GET['page'] ) && !is_numeric( $_GET['page'] ) ){ $this->page = 1; }

		return $this;
	}

	public function countOnPage($countOnPage)
	{
		$this->count_list = $countOnPage;
		return $this;
	}


	public function setData()
	{

		$offset = $this->count_list * ( $this->page - 1 );
		$data = [];

		$result = DB::get()->query( 'SELECT pageId, title, body, keywords, modified 
		FROM pet__page ORDER BY modified DESC LIMIT '.$offset.', '.$this->count_list );

		while( $row = $result->fetch_object() )
		{
			$data[] = $row;
		}

		return $data;
	}


	public function next()
	{

		$link = '<button disabled class="btn btn-danger">'.$this->word[1].'</button>';

		if( $this->page * $this->count_list < $this->count )
		{
			$link = '<a href="'.$this->url.'page='.( $this->page + 1 ) . '" class="btn btn-danger">' . $this->word[1] . '</a>';
		}

		return $link;
	}


	public function prev()
	{

		$link = '<button disabled class="btn btn-danger">'.$this->word[0].'</button>';

		if( $this->page > 1 )
		{
			$link = '<a href="'.$this->url.'page='.( $this->page - 1 ).'" class="btn btn-danger">'.$this->word[0].'</a>';
		}

		return $link;
	}



}