<?php

namespace Model;

use Helper\System\DB;
use Helper\Pagination;

class Task {

	private $path_save = PATH_SAVE;
	private $image_size = [ 'w' => 320, 'h' => 240 ];
	private $url_page = '/testbeejee/admin/?';
	private $div_int = 1.05;
	

	private function imageViewFormat( $name )
	{

		if( preg_match( '/\.jpg$/i' , $name ) )
		{
			return [ imagecreatefromjpeg( $this->path_save.$name ), 'jpg' ];
		}

		if( preg_match( '/\.png$/i' , $name ) )
		{
			return [ imagecreatefrompng( $this->path_save.$name ), 'png' ];
		}

		if( preg_match( '/\.gif$/i' , $name ) )
		{
			return [ imagecreatefromgif( $this->path_save.$name ), 'gif' ];
		}

	}


	private function savePicture( $source, $new_name, $tmp_size, $image, $old_name )
	{

		$thumb = imagecreatetruecolor( ceil( $tmp_size[0] ), ceil( $tmp_size[1] ) );

		unlink( $old_name );

		imagecopyresampled($thumb, $source[0], 0, 0, 0, 0, ceil( $tmp_size[0] ), ceil( $tmp_size[1] ), $image[0], $image[1] );


		if( $source[1] == 'jpg' )
		{
			return imagejpeg($thumb, $this->path_save . $new_name, 100 );
		}

		if( $source[1] == 'gif' )
		{
			return imagegif($thumb, $this->path_save . $new_name );
		}

		if( $source[1] == 'png' )
		{
			imagealphablending($thumb, false);
			imagesavealpha($thumb, true);
			return imagepng($thumb, $this->path_save . $new_name, 9 );
		}

		imagedestroy( $thumb );
	}


	private function pictureLoad()
	{

		$rand = rand( 1111111, 99999999 );
		$save = $this->path_save.$rand.'_'.$_FILES['picture']['name'];
		$new_name = $rand.'_'.$_FILES['picture']['name'];

		if( !move_uploaded_file( $_FILES['picture']['tmp_name'], $save ) )
		{
			return '';
		}

		$image = getimagesize( $save );
		$tmp_size = $image;

		if( $image[0] > $this->image_size['w'] ||  $image[1] > $this->image_size['h'] )
		{

			$source = $this->imageViewFormat( $_FILES['picture']['name'] );
			$new_name = $rand.'_'.str_ireplace( '.'.$source[1],'', $_FILES['picture']['name'] ).'.'.$source[1];

			while( true )
			{

				$tmp_size[0] /= $this->div_int;
				$tmp_size[1] /= $this->div_int;

				if( $tmp_size[0] < $this->image_size['w'] && $tmp_size[1] < $this->image_size['h'] )
				{
					$this->savePicture( $source, $new_name, $tmp_size, $image, $save );
					break;
				}
			}

		}

		return $new_name;

	}


	public function addTask()
	{

		$name_image = $this->pictureLoad();

		$query = DB::$connect->prepare( 'INSERT INTO tasks( text, username, email, picture, status)
		VALUES( :text, :username, :email, :image, "no-execute" )' );

		$query->bindParam( ':username', $_POST['username'] );
		$query->bindParam( ':email', $_POST['email'] );
		$query->bindParam( ':text', $_POST['text_task'] );
		$query->bindParam( ':image', $name_image );

		return $query->execute();
	}


	public function getCountTask()
	{

		$query = DB::$connect->query( 'SELECT COUNT(*) FROM tasks' );

		return $query->fetchColumn();
	}


	public function SaveEditTask()
	{

		if( !isset( $_POST['status'] ) ){ $_POST['status'] = 'no-execute'; }

		$query = DB::$connect->prepare( 'UPDATE tasks SET text = :text, status = :status WHERE id = :id' );

		$query->bindParam( ':text', $_POST['text'] );
		$query->bindParam( ':status', $_POST['status'] );
		$query->bindParam( ':id', $_POST['idTask'] );

		return $query->execute();
	}


	public function ListTask()
	{

		$sort = 'id';

		if( empty( $_GET['sort'] ) || !isset( $_GET['sort'] ) )
		{
			$_GET['sort'] = 'id'; $sort = 'id';
		}

		if( $_GET['sort'] == 'status' ){ $sort = 'status'; }
		if( $_GET['sort'] == 'username' ){ $sort = 'username'; }
		if( $_GET['sort'] == 'email' ){ $sort = 'email'; }

		$countOnPage = 3;
		$this->url_page .= 'sort='.$sort.'&';

		$paginate = Pagination::getInstance();
		$paginate->setCount( $this->getCountTask() )->setUrl( $this->url_page )->countOnPage( $countOnPage );

		$query = $paginate->setData( $sort );
		$query->execute();

		return $query->fetchAll( \PDO::FETCH_OBJ );
	}

}