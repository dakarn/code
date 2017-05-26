<?php
if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

class Compare_Class
{

	public static $instance = false;

	private function __construct()
	{
	}

	private function __clone()
	{
	}

	public static function getInstance()
	{
		if (!self::$instance) {
			self::$instance = new self();
			return self::$instance;

		} else {

			return self::$instance;
		}
	}

	public function init()
	{
		$access_to_compare = get_option( '_compare_access_to_compare' );

		if( ( $access_to_compare == 'all' ) || ( $access_to_compare == 'user' && is_user_logged_in() )
		|| ( $access_to_compare == 'guest' && !is_user_logged_in() ) )
		{
			add_action('template_redirect', [$this, 'add_to_compare'] );
			add_action('template_redirect', [$this, 'delete_from_compare'] );
			add_action('template_redirect', [$this, 'delete_all_compare' ]);
		}
	}

	private function no_exist_product_in_comapre( $product_id )
	{
		if ( stripos( $_SESSION['compare'], $product_id . '&') === false)
		{
			return true;
		}

		return false;
	}

	private function url_to_redirect()
	{
		$path = apply_filters( 'compare_redirect_after_added', parse_url( $_SERVER['REQUEST_URI'] )['path'] );
		$url = get_option('siteurl').'/'.$path;
		wp_safe_redirect( $url );
		exit();
	}

	public function add( $product_id )
	{

		$prod = wc_get_product( $product_id );

		$count_compare = explode( '&', $_SESSION['compare'] );

		if ( $prod && get_option( '_compare_max_count_for_compare' ) > count( $count_compare ) - 1 )
		{
			if ( !isset( $_SESSION['compare'] ) )
			{
				$_SESSION['compare'] = $product_id . '&';
				return true;

			} else {

				if ( $this->no_exist_product_in_comapre($product_id ) )
				{
					$_SESSION['compare'] .= $product_id . '&';
					return true;
				}
			}
		}

	}

	public function delete( $product_id )
	{
		$prod = wc_get_product( $product_id );

		if ($prod && isset( $_SESSION['compare'] ) )
		{
			$_SESSION['compare'] = str_replace( $product_id . '&', '', $_SESSION['compare']);
			return true;
		}

	}

	public function delete_all()
	{
		unset($_SESSION['compare']);
		return true;
	}

	public function add_to_compare()
	{

		if (isset($_GET['add-to-compare']) && is_numeric($_GET['add-to-compare']))
		{
			if( $this->add( $_GET['add-to-compare'] ) == true )
			{
				wc_add_notice( Compare_Class_Frontend::SUCCESS_OPERATION_ADD, 'success' );

			} else {

				wc_add_notice( Compare_Class_Frontend::FAILED_OPERATION, 'error' );
			}

			$this->url_to_redirect();
		}

	}


	public function delete_from_compare()
	{

		if (isset($_GET['delete-from-compare']) && is_numeric($_GET['delete-from-compare']))
		{
			if( $this->delete( $_GET['delete-from-compare'] ) == true )
			{
				wc_add_notice( Compare_Class_Frontend::SUCCESS_OPERATION_DEL, 'success' );

			} else {

				wc_add_notice( Compare_Class_Frontend::FAILED_OPERATION, 'error' );
			}

			$this->url_to_redirect();
		}

	}


	public function delete_all_compare()
	{
		if (isset($_GET['delete-all-compare']))
		{
			$this->delete_all();
			$this->url_to_redirect();
		}
	}

}