var Options = require('./options.js');
var loader = require('./loader.js');

var max_client = { http: 0, https: 0, sock4: 0, sock5: 0 };
var limit = [ 403, 'HTTP/1.1 403 Forbidden\r\n\r\n', '<h1><b>Access Denied!<b></h1><br><hr>Too many connections on a proxy server.' ];
var limi_account = [ 403, 'HTTP/1.1 403 Forbidden\r\n\r\n', '<h1><b>Access Denied!<b></h1><br><hr>Too many connections on a proxy server via that KeyCode.' ];
var is_cut_speed;
var limit_speed = 100000;
var max_limit_traffic = 1000000000;
var limit_count_threads = 4;
var ip_binding;
var max_threads_key;

function parseHead( data )
{

	var spl = data.toString().substring( 0 , data.toString().indexOf("\r\n\r\n") ).split("\r\n");
	jskey = {};

	for( var k in spl )
	{
		if( k === 0 )
		{
			var key = spl[k].split(" ");
			var type = "Method";

			if( key[0] ){ jskey[type] = key[0].trim(); }

			var type = "Path";

			if( key[1]){ jskey[type] = key[1].trim(); }

			var type = "Version";

			if(key[2]){ jskey[type] = key[2].trim(); }

			continue;
		}

		var key = spl[k].split(":");

		if( !key[1] ){ continue; }

		var type1 = key[0];
		jskey[type1] = key[1].trim();

	}

	return jskey;

}

function limitSpeed()
{
	return limit_speed;
}

function maxLimitTraffic()
{
	return max_limit_traffic;
}

function ipBinding()
{
	return ip_binding;
}

function maxThreadsKey()
{
	return max_threads_key;
}

function limitCountThreads()
{
	return limit_count_threads;
}

function sendError( res, code, text, https )
{
	if( https === 0 )
	{
		if( typeof text === 'string' )
		{
			res.writeHead(code, '');
			res.write(text);

		} else {

			res.writeHead(code, text);
			res.write('');
		}

	} else {

		res.write(code + text);
	}

	res.end();
}


function checkMaxClient( res, type_client )
{

	var limit_client = parseInt( loader.Loader.getOpt('global', 3 + type_client, true ) );
	var status = true;

	switch( type_client )
	{
		case 0:

			if( limit_client < max_client.http ){ status = false; }

		break;
		case 1:

			if( limit_client < max_client.https ){ status = false; }

		break;
		case 2:

			if( limit_client < max_client.sock4 ){ status = false; }

		break;
		case 3:

			if( limit_client < max_client.sock5 ){ status = false; }

		break;
	}

	if( !status ){ sendError( res, limit[0], limit[2], (type_client===0)?0:1 ); }
	return status;

}


function CutSpeed( index_user )
{

	if( index_user === -1 ){ return limit_speed;  }

	if( is_cut_speed === 'on' )
	{

		var th = Options.getUserMeta(index_user);

		if( th.threads <= limit_count_threads ){ return limit_speed; }

		return parseInt( limit_speed/Options.getUserMeta(index_user).threads );
	}

	return limit_speed;
}

function checkMaxThreadsKey( res, index_user, type )
{

	if( Options.getUserMeta(index_user).threads > maxThreadsKey() )
	{
		sendError( res, limi_account[0], limi_account[2], (type===0)?0:1 ); return false;
	}

	return true;
}


function setParameters()
{

	is_cut_speed = loader.Loader.getOpt('global', 2, true );
	limit_speed = parseInt( loader.Loader.getOpt('global', 7, true ) );
	max_limit_traffic = parseInt( loader.Loader.getOpt('global', 8, true ) );
	limit_count_threads = parseInt( loader.Loader.getOpt('global', 9, true ) );
	max_threads_key = parseInt( loader.Loader.getOpt('global', 11, true ) );
	ip_binding = parseInt( loader.Loader.getOpt('global', 10, true ) );
}

exports.checkMaxClient = checkMaxClient;
exports.sendError = sendError;
exports.parseHead = parseHead;
exports.CutSpeed = CutSpeed;
exports.setParameters = setParameters;
exports.limitSpeed = limitSpeed;
exports.maxLimitTraffic = maxLimitTraffic;
exports.limitCountThreads = limitCountThreads;
exports.ipBinding = ipBinding;
exports.maxThreadsKey = maxThreadsKey;
exports.checkMaxThreadsKey = checkMaxThreadsKey;
