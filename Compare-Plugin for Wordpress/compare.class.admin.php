<?php
if ( ! defined( 'ABSPATH' ) ) {
	exit;
}


class Compare_Class_Admin {


	public static function get_content_setting()
	{

		self::save_options();

		$options = self::get_plugin_option();

		include( 'setting.php' );
	}

	public static function save_options()
	{
        if( isset( $_POST['save_compare_plugin'] ) )
        {
            update_option( '_compare_max_count_for_compare', (int)$_POST['max_count_for_compare'] );
	        update_option( '_compare_access_to_compare', $_POST['access_to_compare'] );
	        update_option( '_compare_ajax_functional', $_POST['ajax_functional'] );
	        update_option( '_compare_render_result', $_POST['render_result'] );
	        update_option( '_compare_worker', $_POST['worker'] );
        }
	}

	public static function get_plugin_option()
    {
        $args['max_count_for_compare'] = get_option( '_compare_max_count_for_compare' ) == false ? '8': get_option( '_compare_max_count_for_compare' );
	    $args['ajax_functional'] = get_option( '_compare_ajax_functional' ) == 'on' ? 'checked': '';
	    $args['access_to_compare'] = get_option( '_compare_access_to_compare' ) == false ? 'all': get_option( '_compare_access_to_compare' );
	    $args['render_result'] = get_option( '_compare_render_result' ) == 'on' ? 'checked': '';
	    $args['worker'] = get_option( '_compare_worker' ) == 'on' ? 'checked': '';

	    return $args;
    }

	public static  function compare_admin_init()
	{
		global $_wp_last_object_menu;

		$_wp_last_object_menu++;

		add_submenu_page( 'options-general.php','Compare Plugin',
			'Compare Plugin',
			'manage_options', 'compare-plugin',
			 [Compare_Class_Admin, 'get_content_setting' ], '',
			$_wp_last_object_menu );
	}

}

add_action('admin_menu', [ Compare_Class_Admin, 'compare_admin_init' ] );