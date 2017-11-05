<?php

namespace BlokBundle\Service;

use Symfony\Component\DependencyInjection\ContainerInterface;

class Pagination
{
	private $sc;
	private $count_list = 10;
	private $page = 1;
	private $count = 0;
	private $word = ['Назад', 'Далее'];
	private $url;
	private $offset = 0;
	private $link_pages = '<li class="%s"><a href="%s%d">%d</a></li>';
	private $active = 'active';
	private $simple_html = '<a class="%s" href="%s%d">%d</a> ';
	private $count_list_pages = 10;
	private $open_close_tag = ['<ul class=pagination>', '</ul>'];

	public function __construct(ContainerInterface $sc)
	{
		$this->sc = $sc;
	}

	public function getPage($page = 1)
	{
		$this->page = abs((int)$page);
		$this->offset = $this->count_list * ($this->page - 1);
	}

	public function setCount(int $count)
	{
		$this->count = $count;
		return $this;
	}

	public function setUrl(string $url)
	{
		$this->url = $url;
		return $this;
	}

	public function countOnPage(int $countOnPage)
	{
		$this->count_list = $countOnPage;
		return $this;
	}

	public function setPrepare($pdo, string $query, int $page)
	{
		$doct = $pdo->getConnection();
		$this->getPage($page);

		$query = $doct->prepare($query.' LIMIT '.$this->offset.','.$this->count_list.'');

		$query->execute();
		return $query->fetchAll(2);

	}

	public function setData($repos, array $criteria, array $orderBy, int $page)
	{
		$this->getPage($page);
		return $repos->findBy($criteria, $orderBy, $this->count_list, $this->offset);
	}

	private function calculatePages(string $link)
	{
		$last_page = '';
		$count_pages = ceil($this->count/$this->count_list);
		$start = 1;
		$end = $count_pages;

		if ($this->page < $this->count_list_pages) {
			$end = $this->count_list_pages;
		}

		if ($this->page > $this->count_list_pages - 1) {

			$link .= sprintf( $this->link_pages, '', $this->url, $start, $start );
			$start = $this->page - 3;
			$end =  $this->page + 4;

			if ($end >= $count_pages){
				$end = $count_pages;
			}
		}

		if ($this->page < $this->count_list_pages) {
			$last_page = sprintf( $this->link_pages, '', $this->url, $count_pages, $count_pages );
		}

		return array($start, $end, $link, $last_page);

	}

	public function list_pages($simple = false)
	{
		if ( $this->count <= $this->count_list) {
			return null;
		}

		$link = $this->open_close_tag[0];

		if ($simple === true) {
			$link = '<span>';
			$this->open_close_tag[1] = '</span>';
			$this->link_pages = $this->simple_html;
		}

		list($start, $end, $link, $last_page) = $this->calculatePages($link);

		for ($start; $start <= $end; ++$start) {
			$link .= sprintf($this->link_pages, $start===$this->page?$this->active:'', $this->url, $start, $start);
		}

		$link .= $last_page;
		$link .= $this->open_close_tag[1];

		return $link;
	}

	public function next()
	{
		$link = '<button disabled class="btn btn-danger">'.$this->word[1].'</button>';

		if( $this->page * $this->count_list < $this->count )
		{
			$link = '<a href="'.$this->url.( $this->page + 1 ) . '" class="btn btn-danger">' . $this->word[1] . '</a>';
		}

		return $link;
	}

	public function prev()
	{
		$link = '<button disabled class="btn btn-danger">'.$this->word[0].'</button>';

		if($this->page > 1) {
			$link = '<a href="'.$this->url.( $this->page - 1 ).'" class="btn btn-danger">'.$this->word[0].'</a>';
		}

		return $link;
	}



}