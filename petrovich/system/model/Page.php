<?php

namespace Model;

use Helper\Pagination;
use Helper\System\DB;

class Page {


	private $url = URL.'page-list/?';
	private $date_format = 'Y-m-d H:i:s';

	public function addPage()
	{

		$stmt = DB::get()->prepare( 'INSERT INTO pet__page ( title, body, keywords, modified ) 
			VALUES(?,?,?,?)' );

		$datetime = date($this->date_format, time());
		$content = $_POST['header_text'].''.$_POST['text'].''.$_POST['footer_text'];

		$stmt->bind_param( 'ssss',
			$_POST['title'],
			$content,
			$_POST['keywords'],
			$datetime );

		if( $stmt->execute() )
		{
			$id = $stmt->insert_id;
			$stmt->close();

			return $id;
		}

		return false;
	}


	public function getPage($id)
	{

		$stmt = DB::get()->query( 'SELECT title, body, keywords, pageId, modified 
		FROM pet__page WHERE pageId = '.$id.' LIMIT 1' );

		$data = $stmt->fetch_assoc();

		return $data;
	}

	public function getLastPages($count)
	{

		$data = [];
		$stmt = DB::get()->query( 'SELECT title, body, keywords, pageId, modified 
		FROM pet__page ORDER BY modified DESC LIMIT '.$count.'' );

		while( $row = $stmt->fetch_object() )
		{
			$data[] = $row;
		}

		return $data;
	}

	private function getCountPage()
	{

		$stmt = DB::get()->query( 'SELECT COUNT(*) FROM pet__page' );

		return $stmt->fetch_row()[0];
	}

	public function getPages()
	{

		$paginate = Pagination::getInstance();
		$paginate->setCount($this->getCountPage())->setUrl($this->url)->countOnPage(COUNT_ON_PAGE);

		return $paginate->setData();

	}

	public function deletePage($id)
	{

		$stmt = DB::get()->prepare( 'DELETE FROM pet__page WHERE pageId = ?' );
		$stmt->bind_param('i', $id);

		if( $stmt->execute() )
		{
			$stmt->close();
			return true;
		}

		return false;
	}

	public function editPage($id)
	{

		$stmt = DB::get()->prepare( 'UPDATE pet__page SET title = ?,
 			body = ?,
 			keywords = ?, 
 			modified = ? 
			WHERE pageId = ?' );

		$datetime = date($this->date_format, time());

		$stmt->bind_param( 'ssssi', $_POST['title'], $_POST['text'], $_POST['keywords'], $datetime, $id );

		if( $stmt->execute() )
		{
			$stmt->close();
			return true;
		}

		return false;
	}

}