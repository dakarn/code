var url = require('url');
var net = require('net');
var loader = require('./loader.js');
var Options = require('./options.js');
var Opt = require('./var_option.js');

var code = 'abcdef';
var error500 = 'HTTP/1.1 500 Connection error\r\n\r\n';

function run( sock, data, dataVar )
{
	if( !Opt.checkMaxClient( sock, 1 ) ) return;

	var IP = sock.remoteAddress.split(":").pop();
	var len_data_traffic = 0, index_user = -1;

	sock.on( 'end', function(){ if( dataVar.socket ){ dataVar.socket.end(); } return; });
	sock.on( 'error', function( error ) { if( dataVar.socket ){ dataVar.socket.end(); } return; });

	if (isHelloServer( data, dataVar.version)) {

		dataVar.version = 4;
		dataVar.port = data[3];
		dataVar.ip = data[4]+'.'+data[5]+'.'+data[6]+'.'+data[7];

		sock.write( chr(0)+''+chr(90)+code );

	} else if (isGetContent( dataVar.version)) {

		var headers = Opt.parseHead( data );
		var host = headers.Host;

		if( (index_user = Options.checkAccessSock( sock, data, dataVar )) === false ) return;
		if( !Options.deniedIP( IP, sock, 'other' ) ) return;
		if( !Options.blackListHost( headers.Host, sock, 'other' ) ) return;
		if( !Opt.checkMaxThreadsKey(index_user, 1) ) return;

		Options.setThreadUser( index_user, 1 );
		Options.setTraffic( index_user, data.toString().length, IP, headers );

		dataVar.socket = net.connect( dataVar.port, dataVar.ip, function()
		{
			Options.setTraffic( index_user, data.toString().length, IP, headers );
			dataVar.socket.write( data );
		});

		dataVar.socket.on('data', function(chunk)
		{
			var len = chunk.length;
			Options.setTraffic( index_user, len, IP, headers );
			sock.write( chunk );

			if( Options.checkLimitTraffic(index_user) === false )
			{
				len_data_traffic += len;

				if( Options.checkUpTraffic( len_data_traffic, index_user ) )
				{
					dataVar.socket.pause(); var diff = Opt.limitSpeed() - len_data_traffic;
					setTimeout(function () { len_data_traffic = 0; dataVar.socket.resume(); }, 1000+Math.floor(Math.abs(diff)/100));
				}
			}

		});

		dataVar.socket.on('end', function() { Options.setThreadUser( index_user, 0 ); sock.end(); });
		dataVar.socket.on('error', function() { sock.write( error500 ); sock.end(); });

	}

}

function isHelloServer( data, version )
{
	if (data[0] === 4 && version === 0) {
		return true;
	}
	return false;
}

function isGetContent( version )
{
	if (version === 4) {
		return true;
	}
	return false;
}

function chr( code )
{
	return String.fromCharCode( code );
}

exports.run = run;