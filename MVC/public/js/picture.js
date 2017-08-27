var LoadPicture = (function(){

	var img;
	var ext = /(jpg|png|gif)/i;
	var size = [ 320, 240 ];
	var new_size = [ 320, 240 ];
	var elem = '[name=picture]';
	var compress = '#picture-compress';


	function compressImage( event )
	{

		var w, h;

		function compressor()
		{

			if( w < size[0] && h < size[1] )
			{
				new_size[0] = w;
				new_size[1] = h;
				return;
			}

			while( true )
			{
				h /= 1.05;
				w /= 1.05;

				if( w < size[0] && h < size[1] )
				{
					new_size[0] = Math.floor( w );
					new_size[1] = Math.floor( h );
					break;
				}

			}

		}


		var image = new Image();
		image.src = event.target.result;

		image.addEventListener('load', function ()
		{
			$( compress ).html( image );

			w = image.width;
			h = image.height;
			compressor();

			$( compress ).html('');
			$('#picture-review').html('<img src="'+event.target.result+'" width="'+new_size[0]+'" height="'+new_size[1]+'">');

		});


	}


	function showImgPicture()
	{

			var reader = new FileReader();
			reader.readAsDataURL(img);

			reader.onload = function ( event )
			{
				compressImage( event );
			}
	}

	function checkExtension()
	{
		if( ext.test( img.name ) != 1 )
		{
			return false;
		}

		return true;
	}

	return {

		init: function()
		{
			$( elem ).change( function( event )
			{

				if( window.File && window.FileReader) {

					img = event.target.files[0];

					if( !checkExtension() ) return;

					showImgPicture();

				}
			});
		},

	}

})();

$(function() {

	LoadPicture.init();

});
