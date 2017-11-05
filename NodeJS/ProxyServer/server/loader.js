var fs = require('fs');
var Options = require('./options.js');

var file = 'funproxy.dat';
var opt_arr = [];
var opt_value_arr = [];
var setFunLoad;
var accept_file = 'denied-ip.dat';
var error = ['File options not found'];

function Loader(){}

Loader.accessList = [];

Loader.options = function () {

	try {
		fs.readFile(file, function (err, data) {

			if (err) {
				throw error[0];
			}

			Loader.parseOptions(data.toString());
			setFunLoad();

		});

	} catch (e) {
		console.error(e);
	}
}

Loader.getOpt = function(item)
{
	var key = opt_arr.indexOf(item);

	if (arguments[2] && arguments[2] === true && key !== -1) {
		return opt_value_arr[key][arguments[1]].toString().split(": ")[1];
	}

	return opt_value_arr[key] === -1 ? false : opt_value_arr[key];
}

Loader.parseOptions = function(data)
{

	var index = data.indexOf("[Types proxy]"); var nul = data.indexOf("\r\n\r\n");
	optproxy = data.substring( index , nul ).split("\r\n"); optproxy.splice(0,1);
	data = data.substring(nul+1);
	opt_arr.push('types');
	opt_value_arr.push(optproxy);

	var index1 = data.indexOf("[Port proxy]"); var nul1 = data.indexOf("\r\n\r\n");
	optport = data.substring( index1 , nul1 ).split("\r\n"); optport.splice(0,1);
	data = data.substring(nul1+1);
	opt_arr.push('port');
	opt_value_arr.push(optport);

	var index2 = data.indexOf("[Blacklist domain]"); var nul2 = data.indexOf("\r\n\r\n");
	optbdom = data.substring( index2 , nul2 ).split("\r\n"); optbdom.splice(0,1);
	data = data.substring(nul2+1);
	opt_arr.push('blacklist');
	opt_value_arr.push(optbdom);

	var index3 = data.indexOf("[Types HTTP method]"); var nul3 = data.indexOf("\r\n\r\n");
	optmethod = data.substring( index3 , nul3 ).split("\r\n"); optmethod.splice(0,1);
	data = data.substring(nul3+1);
	opt_arr.push('method');
	opt_value_arr.push(optmethod);

	var index4 = data.indexOf("[GlobalOptions]"); var nul4 = data.indexOf("\r\n\r\n");
	optglob = data.substring( index4 , nul4 ).split("\r\n"); optglob.splice(0,1);
	data = data.substring(nul4+1);
	opt_arr.push('global');
	opt_value_arr.push(optglob);

	var dataip = fs.readFileSync( accept_file ).toString().split('|');

	for( var key in dataip )
	{
		if( dataip[key] !== "" ) { Loader.accessList.push( dataip[key] ); }
	}

	Options.getAccessKey();
}

Loader.onLoad = function(callback)
{
	setFunLoad = callback;
}

exports.Loader = Loader;
