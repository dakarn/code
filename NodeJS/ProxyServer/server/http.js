var http = require('http');
var url = require('url');
var net = require('net');
var util = require('util');
var Opt = require('./var_option.js');
var Options = require('./options.js');
var loader = require('./loader.js');

function run( req, res )
{
	try
	{
		if (!Opt.checkMaxClient(res, 0)) {
			return;
		}

		var len_data_traffic = 0;
		var index_user = -1;

		if ((index_user = Options.checkAccessHttp(res, req, false)) === false ) {
			return;
		}

		if (!Opt.checkMaxThreadsKey(res, index_user, 0)) {
			return;
		}

		var ph = url.parse(req.url);
		var IP = req.connection.remoteAddress.split(":").pop();

		if (!Options.deniedIP(IP, res, 'http')){
			return;
		}

		if (!Options.blackListHost(ph.hostname.toString().trim(), res, 'http')) {
			return;
		}

		Options.setThreadUser(index_user, 1);
		var options = { port: ph.port, hostname: ph.hostname, method: req.method, path: ph.path, headers: req.headers };
		var proxyRequest = http.request(options);

		proxyRequest.on('response', function(proxyResponse)
		{
			res.writeHead(proxyResponse.statusCode, proxyResponse.headers);

			var len = JSON.stringify(proxyResponse.headers).length;
			Options.setTraffic(index_user, len, IP, req.headers);

			proxyResponse.on('data', function(chunk)
			{
				var len = chunk.length;
				Options.setTraffic(index_user, len, IP, req.headers);
				res.write(chunk, 'binary');

				if (Options.checkLimitTraffic(index_user) === false) {

					len_data_traffic += len;

					if (Options.checkUpTraffic(len_data_traffic, index_user)) {

						proxyResponse.pause();
						var diff = Opt.limitSpeed() - len_data_traffic;

						setTimeout(function () {

							len_data_traffic = 0;
							proxyResponse.resume();

						}, 1000 + Math.floor(Math.abs(diff) / 100));
					}
				}

			});

			proxyResponse.on('end', function() { Options.setThreadUser( index_user, 0 ); res.end(); });
			proxyResponse.on('error', function() {  res.end(); });

		});

		proxyRequest.on('error', function(e) {  res.end(); });

		req.on('data', function(chunk) {

			Options.setTraffic( index_user, chunk.length, IP, req.headers );
			proxyRequest.write(chunk, 'binary');
		});

		req.on('end', function() {  proxyRequest.end(); });
		res.on('end', function() { proxyRequest.end(); });
		res.on('error', function() { proxyRequest.end(); });

	} catch( e ){ console.error(e); }

}

exports.run = run;
