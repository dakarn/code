<?php
if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

$image_size = [ 130, 130 ];
$image_size = apply_filters( 'image_size_list_compare', $image_size );
$exception_attr = apply_filters( 'exception_attr_compare', [ 'brand' ] );

function cut_name_cat( $name )
{
	return preg_replace( '/<a href=(.*)>(.*)<\/a>/i', '$2', $name );
}

function show_type_btn()
{
	$text = 'Очистить сравнения';
	$src = '<span class="glyphicon glyphicon-remove"></span> ';

	if( get_option( '_compare_ajax_functional' ) == 'on' ) {
		echo '<a href="" id="result-query" href="" onClick="send_compare_delete_all(); return false;" 
		class="btn btn-primary">'.$text.'</a>';
	} else {
		echo '<a href="/compare-product/?delete-all-compare" class="btn btn-primary">'.$text.'</a>';
	}
}
?>

<br>
<div class="container">

	<span style="display: none"><? wc_print_notices(); ?></span>

	<? if( $list_compare ) : ?>

		<div style="border-radius: 1%; border: thin dashed gray; padding: 10px; width: 500px; background: rgb(245, 245, 245);">
			<label>Выводить тип товара:</label>
			<select name="" class="form-control" onChange="choose_comapre_single( this )">

				<? foreach( $unique_cat as $v ) : ?>
					<option value="<?= cut_name_cat($v)?>"><?= cut_name_cat($v)?></option>
				<? endforeach; ?>

					<option value="all">Показать все</option>

			</select><br><br>
			<? show_type_btn() ?><br>
		</div><br><br>

	  <div style="overflow-x: auto; width: 1200px;">

		<table class="table table-bordered" style="width:<?= count( $list_compare ) * 240?>px">
		<tbody>
		<tr>

	    <? foreach( $list_compare as $value ) : ?>

		    <td class="uniq-select" data-uniq="<?= cut_name_cat($value->get_categories())?>" style="background: rgb( 241, 241, 241 )">
	          <div style="overflow: hidden; height: 288px; text-align: center; padding: 12px; width: 220px;">

			    <a href="/product/<?= $value->slug ?>"><?= $value->get_image( $image_size ) ?></a><br><br>
			    <div style="overflow: hidden; height: 35px; font-size: small">
				    <a href="/product/<?= $value->slug ?>" title="<?= $value->name?>"><?= $value->name?></a><br>
			    </div><br>
		        <b><span style="font-size: 17px;"><?= wc_price( $value->price ) ?></span></b><br>
		        <a href="/compare-product/?delete-from-compare=<?= $value->id ?>" class="btn btn-default">
			        <span class="glyphicon glyphicon-remove glyph-remove"></span> Удалить
		        </a>

		     </div>
		    </td>


	    <? endforeach; ?>

		</tr>
		<tr>

			<? foreach( $list_compare as $value ) : ?>

				<? $attributes = $value->get_attributes();
				usort( $attributes, function($a, $b){ return strcmp($a['name'], $b['name']); } ); ?>

				<td class="uniq-select" data-uniq="<?= cut_name_cat($value->get_categories())?>" style="background: rgb( 255, 255, 255)">
				  <div style="overflow: hidden; max-height: 1868px; text-align: left; padding: 8px; width: 220px;">
					<div style="font-size: 20px;">Характеристики</div><br><br>

					<? foreach ( $attributes as $attribute ) : ?>

					  <div style="margin-top: 6px;">

						<strong><?= wc_attribute_label( $attribute->get_name() ); $values = []; ?>:</strong><br>

						<? if ( $attribute->is_taxonomy() )
						{
							$attribute_values = wc_get_product_terms($value->get_id(), $attribute->get_name(), array('fields' => 'all'));

							foreach ( $attribute_values as $attribute_value )
							{
								$values[] = esc_html( $attribute_value->name );
							}
						}

						echo implode( ', ', $values ); ?>

						<br>
					  </div>

					<? endforeach; ?>

				  </div>
				</td>

			<? endforeach; ?>

		</tr>
		</tbody>
		</table>

	  </div>

	<? else: ?>

		<div class="woocommerce-info">Таблица сравнения пуста!</div>

	<? endif; ?>

</div>