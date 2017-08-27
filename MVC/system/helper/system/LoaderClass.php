<?php

namespace Helper\System;

class LoaderClass {



	public function loader()
	{
		spl_autoload_register( function( $class )
		{

			$extension = '.php';
			$path_class = str_replace('\\', '/', $class);

			if (!file_exists(PATH_SYSTEM . $path_class . $extension))
			{
				echo 'Such controller not found.';
				return;
			}

			include_once(PATH_SYSTEM . $path_class . $extension);

			if( !class_exists( $class ) )
			{
				echo 'Such class not found.';
				return;
			}

		});

	}

}
