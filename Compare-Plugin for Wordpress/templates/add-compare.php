<?php
if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

if( !isset( $product ) || empty( $product ) )
{
	global $product;
}


if( get_option( '_compare_access_to_compare' ) == 'user' && !is_user_logged_in() )
{
	return;
}

if( get_option( '_compare_access_to_compare' ) == 'guest' && is_user_logged_in() )
{
	return;
}

if( strpos( $_SESSION['compare'], $product->get_id().'&' ) === false ) : ?>

	<? if( get_option( '_compare_ajax_functional' ) == 'on' ) : ?>

		<a id="result-query" href="" onClick="send_compare( 'add-to-compare', <?= $product->get_id()?>); return false;" class="btn btn-default">В сравнения</a>

	<? else: ?>

		<a href="?add-to-compare=<?= $product->get_id() ?>" class="btn btn-default">В сравнения</a>

	<? endif; ?>

<? else: ?>

	<? if( get_option( '_compare_ajax_functional' ) == 'on' ) : ?>

		<a href="" id="result-query" href="" onClick="send_compare( 'delete-from-compare', <?= $product->get_id()?>); return false;" class="btn btn-info">Убрать из сравнений</a>

	<? else: ?>

		<a href="?delete-from-compare=<?= $product->get_id() ?>" class="btn btn-info">Убрать из сравнений</a>

	<? endif; ?>

<? endif; ?>
