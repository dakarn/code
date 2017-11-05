var http = require('http');
var net = require('net');
var process = require('process');
require('events').EventEmitter.prototype._maxListeners = 10000;

var Options = require('./server/options.js');
var Opt = require('./server/var_option.js');
var loader = require('./server/loader.js');
var httpServer = require('./server/http.js');
var httpsServer = require('./server/https.js');
var sock4Server = require('./server/sock4.js');
var sock5Server = require('./server/sock5.js');

loader.Loader.options();

loader.Loader.onLoad( function()
{
	Opt.setParameters();
	runServers();
});

function runServers()
{
	try
	{
		var typesProxy = loader.Loader.getOpt('types');
		var port = loader.Loader.getOpt('port');

		if (typesProxy[1] === "HTTPS-Proxy: on") {

			var serverhttps = http.createServer( httpsServer.requestdatahttps );
			serverhttps.on('connect', httpsServer.run );
			serverhttps.listen( port[1].split(" ")[1], function(){});
		}

		if (typesProxy[0] === "HTTP-Proxy: on") {

			var server = http.createServer(httpServer.run);
			server.listen(port[0].split(" ")[1], function(){
			});
		}

		if (typesProxy[2] === "SOCKS-Proxy: on") {

			var sock = net.createServer( sockserver ).listen(port[2].split(" ")[1]);
		}

	} catch (e){
		console.log(e);
	}

}

function sockserver(sock)
{
	var version = 0;
	var ip = '';
	var port = 0;
	var socket;
	var domainsip = [];
	var typeip = 0;
	var isHTTPS = false;
	var len_data_traffic = 0;

	var dataVar = {
		isHTTPS: isHTTPS,
		version: version,
		len_data_traffic: len_data_traffic,
		ip: ip,
		port: port,
		socket: socket,
		domainsip: domainsip,
		typeip: typeip
	};

	try {
		sock.on('data', function (data) {

			sock4Server.run(sock, data, dataVar);
			sock5Server.run(sock, data, dataVar);

		});

	} catch (e) {
		console.error(e);
	 }

}

function traficCount()
{
	/*var kb = 'kb'; var traf = 0; var trafproc = "";
	 if( traffic <= 1024 ){kb = 'B'; traf = traffic;} else if( traffic > 1024 && traffic <= 1024000 )
	 {trafproc = ""; kb = 'KB'; traf = traffic/1000;} else if( traffic > 1024000 && traffic <= 1024000000 ){trafproc ="."+Math.round(traffic%1000%1000); kb = 'MB'; traf = traffic/1000/1000;} else if( traffic > 1024000000 && traffic <= 1024000000000 ){
	 traf = traffic/1000/1000/1000; kb = 'GB';  trafproc ="."+Math.round(traffic%1000%1000%1000);
	 }trafproc = trafproc.substring( 0, 3 );if( trafproc[2] == 0 ){ trafproc = trafproc.substring(0,2); }//sys.debug("Traffic: "+Math.round(traf)+trafproc+" "+kb);
	 */
}
