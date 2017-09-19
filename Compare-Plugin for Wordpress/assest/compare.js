function send_compare( action, product_id ) {

	var action = action;

	$.post('?wc-ajax='+action,
		{
			product_id: product_id
		},
		function( data ) {

			if( data.success && data.data.fragment )
			{
				$( '#notice-message' ).html( data.data.message );

				$('#result-query').replaceWith( data.data.fragment );

			} else {

				$('#notice-message').html(data.data.message);
				$('#result-query').html(data.data.message);
			}
		},
		'json'
	);

}

function choose_comapre_single( target )
{
	$( '.table' ).css( 'width', parseInt( $( '.uniq-select[data-uniq='+target.value+']' ).length/2) * 239 );

	if( target.value == 'all' ) { $( '.uniq-select' ).show(); return; }

	$( '.uniq-select' ).show();
	$( '.uniq-select[data-uniq!='+target.value+']' ).hide();

}

function send_compare_delete_all()
{

	$.post('?wc-ajax=delete-all-compare', {},
		function( data ) {

			$( '.container' ).html( data.data.fragment );
		},
		'json'
	);
}