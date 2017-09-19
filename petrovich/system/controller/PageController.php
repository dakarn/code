<?php

namespace Controller;

use Helper\System\Render;
use Model\Page;

class PageController {


	public function indexAction()
	{

		$count = 10;
		$pages = (new Page())->getLastPages($count);

		return new Render( 'index.html', [ 'pages' => $pages ] );
	}

	public function itemPageAction()
	{

		$id = $_GET['id'] ?? 0;
		$id = abs( (int)$id );

		$page = (new Page())->getPage($id);

		return new Render( 'item-page.html', [ 'data' => $page ] );
	}


	public function listPagesAction()
	{

		$pages_list = (new Page())->getPages();
		$offset = COUNT_ON_PAGE * ($_GET['page'] - 1);

		return new Render( 'list-page.html', [ 'offset' => $offset, 'pages' => $pages_list ] );
	}

}
