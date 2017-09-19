<?php
if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

$arr_access = [ 'all', 'user', 'guest' ];
$arr_access_value = [ 'Все', 'Только зарегистрированные клиенты', 'Только гости' ];
?>

<h1>Настройка Compare Plugin</h1>
<br><br>

<form action="" method="post">


	<label><strong>Использовать сравнения могут:</strong></label><br>
	<select name="access_to_compare">

		<? foreach( $arr_access as $k=>$v ) : ?>

			<option value="<?= $v?>" <?= $options['access_to_compare'] == $v ? 'selected':'' ?>><?= $arr_access_value[$k]?></option>

		<? endforeach; ?>
	</select>
	<br><br><br>

	<input name="worker" <?= $options['worker']?> type="checkbox">
	<label><strong>Включить плагин?</strong></label><br><br>

	<input name="render_result" <?= $options['render_result']?> type="checkbox">
	<label><strong>Выводить результат добавления или удаления товара из сравнения?</strong></label><br><br>

	<input name="ajax_functional" <?= $options['ajax_functional']?> type="checkbox">
	<label><strong>Использовать Ajax для работы плагина?</strong></label><br><br>

	<label><strong>Максимальное количество товаров для сравнения:</strong></label><br>
	<input name="max_count_for_compare" value="<?= $options['max_count_for_compare']?>" type="text"><br><br>

	<input name="save_compare_plugin" type="submit" value="Обновить" class="button-primary">

</form>