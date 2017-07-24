var url = require('url');
var net = require('net');
var dns = require('dns');
var loader = require('./loader.js');
var Options = require('./options.js');
var Opt = require('./var_option.js');

const error500 = 'HTTP/1.1 500 Connection error\r\n\r\n';
const DOMAIN = 3;
const IP = 1;
const IPV6 = 4;
const HTTPS_PORT = 443;
const okHTTPS = 'HTTP/1.1 200 Connection established\r\n\r\n';

function run( sock, data, dataVar )
{

	 var IP_USER = sock.remoteAddress.split(":").pop();
	 var index_user = -1;

	 sock.on( 'end', function(){ if( dataVar.socket ){ dataVar.socket.end(); } });
	 sock.on( 'error', function( error ) { if( dataVar.socket ){ dataVar.socket.end(); } });

	if( !Opt.checkMaxClient( sock, 1 ) ) return;


	if( isHelloServer( data, dataVar.version ) )
	 {
		 dataVar.version = 5;
		 sock.write( chr(5)+''+chr(0) );

	 } else if( isConnectHost( dataVar ) )
	 {

		 if( data[3] === DOMAIN )
		 {
		 	getDOMAIN( data, dataVar, sock );

		 } else if( data[3] === IP )
		 {
			getIP( data, dataVar, sock );

		 } else if( data[3] === IPV6 )
		 {
			getIPV6( data, dataVar, sock );
		 }

	 } else if( isGetContent( dataVar ) )
	 {

		 var headers = Opt.parseHead( data );

		 if( (index_user = Options.checkAccessSock( sock, data, dataVar )) === false ) return;
		 if( !Options.deniedIP( IP_USER, sock, 'other' ) ) return;
		 if( !Options.blackListHost( headers.Host, sock, 'other' ) ) return;
		 if( !Opt.checkMaxThreadsKey(index_user, 1) ) return;

		 Options.setTraffic( index_user, data.toString().length, IP_USER, headers );
		 Options.setThreadUser( index_user, 1 );

		 dataVar.socket = net.connect( dataVar.port, dataVar.ip, function () {

			 Options.setTraffic( index_user, data.toString().length, IP, headers );
		     dataVar.socket.write(data);

	     });

	     dataVar.socket.on('data', function (chunk)
	     {

		     //console.log(Options.getUserMeta(index_user).threads);
	     	 var len = chunk.length;
		     Options.setTraffic( index_user, len, IP_USER, headers );
		     sock.write(chunk);

		     if( Options.checkLimitTraffic(index_user) === false )
		     {
			     dataVar.len_data_traffic += len;

			     if( Options.checkUpTraffic( dataVar.len_data_traffic, index_user ) )
			     {
				     dataVar.socket.pause(); var diff = Opt.limitSpeed() - dataVar.len_data_traffic;
				     setTimeout(function () { dataVar.len_data_traffic = 0; dataVar.socket.resume(); }, 1000+Math.floor(Math.abs(diff)/100));
			     }
		     }
	     });


		 dataVar.socket.on('end', function() {  Options.setThreadUser( index_user, 0 ); sock.end(); });

		 dataVar.socket.on('error', function(e) { sock.write( error500 ); sock.end(); });

	 }

}


function getIP( data, dataVar, sock )
{

	dataVar.port = data[8]+data[9];
	dataVar.ip = data[4]+'.'+data[5]+'.'+data[6]+'.'+data[7];

	if( dataVar.domainsip.length === 0 )
	{
		var ip1 = dataVar.ip.split(".");
		var answer = chr(5)+''+chr(0)+''+chr(0)+''+chr(IP)+''+chr(ip1[0])+''+chr(ip1[1])+''+chr(ip1[2])+''+chr(ip1[3])+''+chr(dataVar.port);
		sock.write( answer );

	} else {

		sock.write( chr(5)+''+chr(4) );
	}
}

function getDOMAIN( data, dataVar, sock )
{

	dataVar.port = data[ 6 + parseInt(data[4]) ];
	dataVar.ip = data.toString().substring( 5 , data[4] + 5 );

	if( data[7 + data[4]] >= 0 ){ dataVar.port += data[6 + data[4]]; }

	getDnsIp( data, dataVar, sock );

}

function getIPV6( data, dataVar, sock )
{
	dataVar.port = data[8]+data[9];
	dataVar.ip = data[4]+''+data[5]+''+data[6]+''+data[7]+''+data[8]+''+data[9]+''+data[10]+''+data[11];
	dataVar.ip += data[12]+''+data[13]+''+data[14]+''+data[15]+''+data[16]+''+data[17]+''+data[18]+''+data[18];

	if( dataVar.domainsip.length === 0 )
	{
		var ip1 = dataVar.ip.split('.'), ip_answer = '';
		var answer = chr(5)+''+chr(0)+''+chr(0)+''+chr(IPV6)+''+dataVar.ip+''+chr(dataVar.port);
		sock.write( answer );

	} else {

		sock.write( chr(5)+''+chr(4) );
	}
}

function isHttps( data, dataVar )
{

	var find = 'CONNECT';

	if( data.toString().substring( 0, 6 ) === find ){ dataVar.isHTTPS = true; return true; }

	return false;
}

function isHelloServer( data, version )
{

	if( data[0] === 5 && version === 0 ) return true;
	return false;
}

function isConnectHost( dataVar )
{

	if( dataVar.version === 5 && dataVar.port === 0 ) return true;
	return false;
}

function isGetContent( dataVar )
{

	if( dataVar.version === 5 && dataVar.port > 0 ) return true;
	return false;
}

function getDnsIp( data, dataVar, sock )
{

	dns.lookup( dataVar.ip, function( err, address, family )
	{

		dataVar.domainsip = address.toString().split(".");

		if( dataVar.domainsip.length > 0 )
		{
			var str1 = chr(5)+''+chr(0)+''+chr(0)+''+chr(DOMAIN)+''+chr(dataVar.ip.length);
			var str2 = dataVar.ip+''+chr(dataVar.port);

			sock.write( str1+''+str2 );

		} else {

			sock.write( chr(5)+''+chr(4) );
		}

	});
}


function chr( code )
{
	return String.fromCharCode( code );
}

exports.run = run;