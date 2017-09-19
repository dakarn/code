var mysql = require('mysql');
var sess_alize = require('php-unserialize');
var sess_salize = require('php-serialize');
var util = require('util');
var loader = require('./loader.js');
var Opt = require('./var_option.js');


var sql_upd = 'UPDATE keys_property SET property = ? WHERE id = ?';
var sql_read = 'SELECT k.*, kp.* FROM keys_access k JOIN keys_property kp ON k.id = kp.id ' +
	'WHERE k.type_key = ? AND k.expires_at > ?';
var timerUpd = 600;
var need_write_db = false;
var trafficHttp = 0;
var trafficHttps = 0;
var trafficSock4 = 0;
var trafficSock5 = 0;
var connect = null;
var keys_proxy_code_arr = [];
var keys_proxy_prop_arr = [];
var keys_proxy_ip_arr = [];
var forbidden = [ 403, 'HTTP/1.1 403 Forbidden\r\n\r\n' ];
var denied_bl = '<h1><b>Access Denied!<b></h1><br><hr>This domain( %s ) is blacklisted.';
var denied_ip = '<h1><b>Access Denied!<b></h1><br><hr>This IP address is blacklisted.';
var denied = '<h1><b>Access Denied!</b></h1><br><hr>You do not have permission to view this page.';
var auth407_json = {'Proxy-Authenticate': 'Basic realm="Access to site via Proxy-Server - USERNAME: USER ID on SF.RU - PASSWORD: KeyCode for Proxy"', 'Content-Type': 'text/html'};
var auth407 = 'HTTP/1.1 407 Proxy Authentication Required\r\nProxy-Authenticate: Basic realm="Access to site via Proxy-Server - USERNAME: USER ID on SF.RU - PASSWORD: KeyCode for Proxy"\r\nContent-Type: text/html\r\n\r\n';
var processReadDB = false;
var limit_traffic = [ '<h1><b>Access Denied!<b></h1><br><hr>Your traffic key has been exceeded.<br>Wait for new days.'];


function getUserMeta( index_user )
{
	if( index_user === -1 ){ return false;  }
	return keys_proxy_prop_arr[index_user];
}

function checkUpTraffic( len, index_user )
{

	if( len >= Opt.CutSpeed(index_user) ){ return true; }
	return false;
}

function checkLimitTraffic( index_user )
{

	if( index_user === -1 ){ return true; }

	if( keys_proxy_prop_arr[index_user].curr_traffic > Opt.maxLimitTraffic() ){ return false; }
	return true;
}


function chechProxyAuth( res, headers, IP )
{

	var user_code = new Buffer(headers['proxy-authorization'].toString().replace('Basic ', ''),'base64').toString().split(':');
	var find_code = keys_proxy_code_arr.indexOf(user_code[1]);
	var curr_time = Math.floor(new Date().getTime()/1000);

	if( find_code === -1 ||
	( find_code !== -1 && keys_proxy_prop_arr[find_code].user_id !== parseInt(user_code[0]) ) )
	{
		Opt.sendError( res, 407, auth407_json, 0 );  return false;
	}

	if( IP !== keys_proxy_prop_arr[find_code].curr_ip &&
	(curr_time - timerUpd) < keys_proxy_prop_arr[find_code].curr_last_enter )
	{
		Opt.sendError( res, forbidden[0], diff_ip[0], 0 );  return false;
	}

	keys_proxy_prop_arr[find_code].curr_ip = IP;
	keys_proxy_prop_arr[find_code].curr_last_enter = curr_time;

	return find_code;
}


function checkAccessHttp( res, req, isHTTPS )
{

	var IP = req.connection.remoteAddress.split(":").pop();

	if( loader.Loader.getOpt('global')[0] === 'BasicAuth: on' )
	{

		var find_ip = keys_proxy_ip_arr.indexOf( IP );

		if( isHTTPS )
		{

			if( find_ip === - 1  ){ Opt.sendError( res, forbidden[1], '', 1 ); return false; }

			return find_ip;

		} else if( !isHTTPS )
		{

			if( find_ip !== - 1  )
			{

				return find_ip;

			} else if( !req.headers['proxy-authorization'] )
			{
				Opt.sendError( res, 407, auth407_json, 0 ); return false;

			} else {

				if( (find_ip = chechProxyAuth( res, req.headers, IP ) ) === false ) return false;

			}

			return find_ip;
		}

	}

	return -1;
}


function checkAccessSock( sock, data, dataVar )
{

	var headers = Opt.parseHead( data );
	var IP = sock.remoteAddress.split(":").pop();

	if( loader.Loader.getOpt('global')[1] === 'SocksAuth: on' )
	{

		var find_ip = keys_proxy_ip_arr.indexOf( IP );

		if( find_ip === - 1  )
		{
			Opt.sendError( sock, forbidden[1] + denied, 1 ); return false;
		}

		return find_ip;

	}

	return -1;

}


function delNoExistCode( new_code )
{

	for( var key in keys_proxy_code_arr )
	{
		if( new_code.indexOf(keys_proxy_code_arr[key]) === -1 )
		{
			delete keys_proxy_code_arr[key];
			delete keys_ip_code_arr[key];
			delete keys_prop_code_arr[key];
		}
	}
}

function writeDB( index_loop, temp_prop_arr, temp_ip_arr, temp_code_arr )
{

	var count = temp_code_arr.length;

	if( count === index_loop )
	{
		processReadDB = false;
		connect.destroy();
		delNoExistCode( temp_code_arr );
		return true;
	}


	if( (old_index = keys_proxy_code_arr.indexOf( temp_code_arr[index_loop] )) !== -1 )
	{
		keys_proxy_prop_arr[old_index].expires = temp_prop_arr[index_loop].expires;
		keys_proxy_prop_arr[old_index].ip = temp_prop_arr[index_loop].ip;
		keys_proxy_prop_arr[old_index].ban = temp_prop_arr[index_loop].ban;

	} else {

		keys_proxy_code_arr.push( temp_code_arr[index_loop] );
		keys_proxy_prop_arr.push( temp_prop_arr[index_loop] );
		keys_proxy_ip_arr.push( temp_ip_arr[index_loop] );
	}

	var key_id = temp_prop_arr[index_loop].id;

	delete temp_prop_arr[index_loop].expires;
	delete temp_prop_arr[index_loop].id;
	delete temp_prop_arr[index_loop].user_id;
	delete temp_prop_arr[index_loop].curr_ip;
	delete temp_prop_arr[index_loop].curr_last_enter;
	delete temp_prop_arr[index_loop].threads;

	temp_prop_arr[index_loop].curr_traffic = keys_proxy_prop_arr[index_loop].curr_traffic;
	var sess_data = sess_salize.serialize( temp_prop_arr[index_loop] );

	connect.query( sql_upd, [ sess_data, key_id ], function ( err, result, fields )
	{
		++index_loop;
		return writeDB( index_loop, temp_prop_arr, temp_ip_arr, temp_code_arr );
	});

}

function readDB()
{

	var time = new Date().getMilliseconds()/1000;
	var keyType = ['proxy','full'];

	connect.query( sql_read, [keyType[0], time], function( err, result, fields )
	{

		var temp_code_arr = [], temp_prop_arr = [], temp_ip_arr = [];
		processReadDB = true;

		for( var key in result )
		{

			var json = sess_alize.unserialize( result[key].property );
			temp_code_arr.push( result[key].key_code );
			temp_ip_arr.push( json.ip.trim() );

			json.id = result[key].id; json.user_id = result[key].user_id; json.expires = result[key].expires_at;
			json.curr_ip = ''; json.curr_last_enter = 0; json.threads = 0;

			temp_prop_arr.push( json );
		}


		if( need_write_db )
		{
			writeDB( 0, temp_prop_arr, temp_ip_arr, temp_code_arr );

		} else {

			keys_proxy_code_arr = temp_code_arr;
			keys_proxy_ip_arr = temp_ip_arr;
			keys_proxy_prop_arr = temp_prop_arr;
			need_write_db = true;
			processReadDB = false;
			connect.destroy();
		}

	});

}

function deniedIP( ip, res, type_prx )
{

	if( loader.Loader.accessList.indexOf( ip ) !== -1 )
	{
		if (type_prx === 'http') { res.writeHead(forbidden[0], ''); res.write(denied_ip); res.end(); }
		if (type_prx === 'other') { res.write( forbidden[1] + denied_ip ); res.end(); }

		return false;
	}

	return true;
}

function blackListHost( host, res, type_prx )
{

	if( loader.Loader.getOpt('blacklist').indexOf( host ) !== -1 )
	{
		if (type_prx === 'http')
		{
			res.writeHead( forbidden[0], '' );
			res.write( util.format( denied_bl, host ) ); res.end();
		}

		if (type_prx === 'other') { res.write( forbidden[1] + util.format( denied_bl, host ) ); res.end(); }

		return false;
	}

	return true;
}

function getAccessKey()
{

	connect = mysql.createConnection({
		host: "", user: "", password: "", database: ""
	});

	connect.connect(function (err)
	{

		readDB();

		if( need_write_db ) return;

		timerUpd = setInterval( function() { getAccessKey(); }, 60000 * 5 );

	});

}

function setTraffic( index, len, IP )
{

	if( processReadDB ) return;
	if( index === -1 ) return;

	keys_proxy_prop_arr[index].curr_traffic += len;

}

function setThreadUser( index_user, type )
{
	if( index_user === -1 ) return;
	var th = keys_proxy_prop_arr[index_user];

	if( type === 1 ){ th.threads++; }
	if( type === 0 ){ if(th.threads===0){ return; } th.threads--; }
}

function chr( code )
{
	return String.fromCharCode( code );
}

exports.getUserMeta = getUserMeta;
exports.auth407 = auth407_json;
exports.getAccessKey = getAccessKey;
exports.checkAccessHttp = checkAccessHttp;
exports.checkAccessSock = checkAccessSock;
exports.setTraffic = setTraffic;
exports.setThreadUser = setThreadUser;
exports.forbidden = forbidden;
exports.denied_ip = denied_ip;
exports.denied_bl = denied_bl;
exports.deniedIP = deniedIP;
exports.blackListHost = blackListHost;
exports.checkLimitTraffic = checkLimitTraffic;
exports.checkUpTraffic = checkUpTraffic;

