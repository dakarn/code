<?php
/*
Plugin Name: Compare Plugin
Plugin URI: http:///
Description: Compare Pugin for product.
Author: Man
Author URI: http:///
Text Domain: compare
Domain Path: /about/
Version: 1.0
*/

if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

if( is_admin() )
{
	require_once('compare.class.admin.php');

} else {

	if( get_option( '_compare_worker' ) == 'on' )
	{
		require_once('compare.class.frontend.php');
		require_once('compare.class.php');

		add_action('wp_loaded', [Compare_Class_Frontend::getInstance(), 'init']);
		add_action('wp_loaded', [Compare_Class::getInstance(), 'init']);


	}
}


