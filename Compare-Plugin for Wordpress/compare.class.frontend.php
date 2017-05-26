<?php
if ( ! defined( 'ABSPATH' ) ) {
	exit;
}


class Compare_Class_Frontend {


	const FAILED_OPERATION = 'Возникли проблемы при добавлении в сравнения!';
	const SUCCESS_OPERATION_ADD = 'Товар добавлен в сравнения!';
	const SUCCESS_OPERATION_DEL = 'Товар убран из сравнения!';

	const ajax_request_add = 'add-to-compare';
	const ajax_request_del = 'delete-from-compare';
	const ajax_request_all_del = 'delete-all-compare';

	public static $instance = false;

	private function  __construct(){}
	private function  __clone(){}

	public static function getInstance()
	{
		if( !self::$instance )
		{
			self::$instance = new self();
			return self::$instance;

		} else {

			return self::$instance;
		}
	}


	public function reg_shortcode()
	{
		add_shortcode('add_button_compare_product', [$this, 'add_button_compare_product'] );
		add_shortcode('compare_product_show_page', [$this, 'compare_product_page_list' ] );
		add_shortcode('compare_link_on_page', [$this, 'compare_link_on_page' ] );

	}

	public function reg_action()
	{
		$access_to_compare = get_option( '_compare_access_to_compare' );

		if( ( $access_to_compare == 'all' ) || ( $access_to_compare == 'user' && is_user_logged_in() )
		|| ( $access_to_compare == 'guest' && !is_user_logged_in() ) )
		{
			add_action('wc_ajax_' . self::ajax_request_add, [$this, 'add_to_compare']);
			add_action('wc_ajax_' . self::ajax_request_del, [$this, 'delete_from_compare']);
			add_action('wc_ajax_' . self::ajax_request_all_del, [$this, 'delete_all_compare']);
		}
	}

	public function init()
	{
		wp_enqueue_style( 'compare-style', plugin_dir_url(__FILE__).'assest/style.css', ['bootstrap_head'] );
		wp_enqueue_script( 'compare',  plugin_dir_url(__FILE__).'assest/compare.js?'.time(), ['jquery'] );

		$this->reg_shortcode();

		$this->reg_action();
	}

	private function get_result_html_block($type, $message = '' )
	{
		if( get_option( '_compare_render_result' ) == 'on' )
		{
			ob_start();
			wc_get_template('compare/' . $type . '.php', ['message' => $message]);
			return ob_get_clean();
		}
	}

	public function compare_link_on_page()
	{
        wc_get_template( 'compare/link-on-compare.php' );
	}

	public function add_to_compare()
	{

		if( isset( $_POST['product_id'] ) && is_numeric( $_POST['product_id']))
		{
			$prod = wc_get_product( $_POST['product_id'] );

			if ( $prod )
			{
				if( Compare_Class::getInstance()->add( $_POST['product_id'] ) != true )
				{
					$obj_error = trim( $this->get_result_html_block( 'error', self::FAILED_OPERATION ) );
					wp_send_json_error( ['message' => $obj_error ] , 200 );
				}

				$obj_btn = trim( $this->add_button_compare_product( $prod ) );
				$obj_success = trim( $this->get_result_html_block( 'success', self::SUCCESS_OPERATION_ADD ) );

				wp_send_json_success( [ 'message' => $obj_success, 'fragment' => $obj_btn ] , 200 );
			}
		}

		wp_die();
	}

	public function delete_all_compare()
	{
		Compare_Class::getInstance()->delete_all();

		wp_send_json_success( ['fragment' => '<div class="woocommerce-info">Таблица сравнения пуста!</div>' ] );
	}

	public function delete_from_compare()
	{

		if( isset( $_POST['product_id'] ) && is_numeric( $_POST['product_id']))
		{
			$prod = wc_get_product( $_POST['product_id'] );

			if ( $prod )
			{
				if( Compare_Class::getInstance()->delete( $_POST['product_id'] ) != true )
				{
					$obj_error = trim( $this->get_result_html_block( 'error', self::FAILED_OPERATION ) );
					wp_send_json_error( ['message' => $obj_error ] , 200 );
				}

				$obj_btn =  trim( $this->add_button_compare_product( $prod ) );
				$obj_success = trim( $this->get_result_html_block( 'success', self::SUCCESS_OPERATION_DEL ) );

				wp_send_json_success( [ 'message' => $obj_success, 'fragment' => $obj_btn ] , 200 );
			}
		}

		wp_die();
	}

	public function compare_product_page_list()
	{

		$args['list_compare'] = isset($_SESSION['compare']) ? $_SESSION['compare'] : false;

		if ($args['list_compare'] != false)
		{
			$args['list_compare'] = wc_get_products( [
				'post_type' => 'product',
				'post_status' => 'publish',
				'include' => explode('&', $args['list_compare'])
			] );

			foreach( $args['list_compare'] as $v ){ $args['unique_cat'][] = $v->get_categories(); }

			$args['unique_cat'] = array_unique( $args['unique_cat'] );
		}

		if( file_exists( get_template_directory().'/woocommerce/compare/compare-list.php' ) )
		{
			wc_get_template('compare/compare-list.php', $args );
		}

	}


	public function add_button_compare_product( $prod = '' )
	{
		if( file_exists( get_template_directory().'/woocommerce/compare/add-compare.php' ) )
		{
			ob_start();
			wc_get_template('compare/add-compare.php', [ 'product' => $prod ] );
			return ob_get_clean();
		}
	}
}

