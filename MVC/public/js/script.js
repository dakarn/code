function ReviewTask()
{
	$( '#username-review' ).text( $( '[name=username]' ).val() );
	$( '#email-review' ).text( $( '[name=email]' ).val() );
	$( '#text-review' ).text( $( '[name=text_task]' ).val() );

}
