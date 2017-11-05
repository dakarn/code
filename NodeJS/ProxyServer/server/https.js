var url = require('url');
var net = require('net');
var util = require('util');
var fs = require('fs');
var loader = require('./loader.js');
var Options = require('./options.js');
var Opt = require('./var_option.js');

var error500 = [ 500, 'HTTP/1.1 500 Connection error\r\n\r\n' ];
var forbidden = [ 403, 'HTTP/1.1 403 Forbidden' ];
var ok = '200 Connection established\r\n\r\n';
var http = 'HTTP/';

function run( req, res, head )
{
	try
	{
		if( !Opt.checkMaxClient( res, 1 ) ) return;

		var len_data_traffic = 0;
		var index_user = -1;

		if( (index_user = Options.checkAccessHttp( res, req, true )) === false ) return;
		if( !Opt.checkMaxThreadsKey(index_user, 1) ) return;

		var IP = req.connection.remoteAddress.split(":").pop();
		var ph = url.parse("http://"+req.url);

		if( !Options.deniedIP( IP, res, 'other' ) ) return;

		if( !Options.blackListHost( ph.hostname.toString().trim(), res, 'other' ) ) return;

		Options.setThreadUser( index_user, 1 );


		var socket = net.connect(ph.port, ph.hostname, function()
		{
			var len = JSON.stringify(req.headers).length;
			Options.setTraffic( index_user, len, IP );
			socket.write(head);

			res.write(http + req.httpVersion + " "+ok);

		});

		socket.on('data', function(chunk)
		{
			var len = chunk.length;
			Options.setTraffic( index_user, len, IP );
			res.write(chunk);

			if( Options.checkLimitTraffic(index_user) === false )
			{
				len_data_traffic += len;

				if( Options.checkUpTraffic( len_data_traffic, index_user ) )
				{
					socket.pause(); var diff = Opt.limitSpeed() - len_data_traffic;
					setTimeout(function () { len_data_traffic = 0; socket.resume(); }, 1000+Math.floor(Math.abs(diff)/100));
				}
			}

		});

		socket.on('end', function() { Options.setThreadUser( index_user, 0 ); res.end(); });

		socket.on('error', function()
		{
			res.write(http + req.httpVersion + " "+error500); res.end();
		});

		res.on('data', function(chunk)
		{
			Options.setTraffic( index_user, chunk.length, IP );
	        socket.write(chunk);
		});

		res.on('end', function() { socket.end(); });
		res.on('error', function() { socket.end(); });

	} catch( e ){ console.error(e); }

}

function requestdatahttps(req,res)
{

	res.writeHead( forbidden );
	res.write("<h1><b>Access Denied!<b></h1><br><br>" +
		"<span style='font-size: 19px'>This server does not support HTTP Proxy. Use another server.</span>");
	res.end();

	return false;

}

exports.run = run;
exports.requestdatahttps = requestdatahttps;
