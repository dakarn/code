var http = require('http');
var sys = require('sys');
var fs = require('fs');
var request = require('request');
var zlib = require('zlib');
var url = require('url');
var net = require('net');
var dns = require('dns');

var traffic = 0;
var list_accessip = [];
var blistdomain = [];
var listmethod = [];


setTimeout( function()
{
   var dataip = fs.readFileSync('accessip.dat').toString().split('|');
   
   for( var key in dataip)
   {
	   
     if( dataip[key] != "" )
	 { 
		list_accessip.push( dataip[key] ); 
     }
	 
   }
   
} , 100 );


setInterval( function()
{
   list_accessip = [];
   var dataip = fs.readFileSync('accessip.dat').toString().split('|');
   
   for( var key in dataip)
   {
	   
     if( dataip[key] != "" ){ list_accessip.push( dataip[key] ); }
	 
   }
   
} , 300000 );




function httpsreq(req, res, head)
{

 try 
 {
	 
    if( list_accessip.indexOf( req.connection.remoteAddress ) == -1 )
    {
      res.write("HTTP/1.1 500 Connection error\r\n\r\n"); res.end(); return;
    }
    

    var ph = url.parse("http://"+req.url);
	
    var socket = net.connect(ph.port, ph.hostname, function() {

        traffic += JSON.stringify(req.headers).length;
        traffic += 30;
        socket.write(head);
		
        res.write("HTTP/" + req.httpVersion + " 200 Connection established\r\n\r\n");
    });
   
    socket.on('data', function(chunk) { traffic += chunk.length; res.write(chunk); });
    socket.on('end', function() { res.end(); })
    socket.on('error', function() { traffic += 30; res.write("HTTP/" + req.httpVersion + " 500 Connection error\r\n\r\n"); res.end(); });
    
    res.on('data', function(chunk) { traffic += chunk.length; socket.write(chunk); });
    res.on('end', function() { socket.end(); });
    res.on('error', function() { socket.end(); });

	
 } catch( e ){ sys.debug(e); }

}




function sockserver(c)
{

 try {

  
  var version = 0, port = 0 , ip = '' , typeip = 0; var domainsip = []; var socket = '';


  c.on('data', function(data)
  {

    

    if(data[0] == 4 && version == 0 )
    {   

      version = 4;
      port = data[3];
      ip = data[4]+"."+data[5]+"."+data[6]+"."+data[7];
    
      c.write( String.fromCharCode(0)+""+String.fromCharCode(90)+"abcdef");
	  
      traffic += data.length;
	  

    } else if( version == 4 ){ 


      if( list_accessip.indexOf( c.remoteAddress.toString() ) == -1 )
      {
        c.write("HTTP/1.1 403 Forbidden\r\n\r\n"); c.write("<h1><b>Access Denied!<b></h1>"); c.end(); return;
      }

      var host = parseHead(data).Host;
	  
      if( blistdomain.indexOf( host ) != -1 )
      {
		c.write("HTTP/1.1 200 OK\r\n\r\n"); 
		c.write("<h1><b>Access Denied!<b></h1><big>This domain( "+host+" ) is blacklisted.</big>"); 
		c.end(); 
		return;
      }

      socket = net.connect(port, ip, function() {
 
         
         traffic += data.length;
         socket.write( data );  
        
      });
   

      socket.on('data', function(chunk) {

          traffic += chunk.length; c.write(chunk);

      });

      socket.on('end', function() { c.end(); });

      socket.on('close', function() { c.end(); });

      socket.on('error', function() 
	  { 
	  
		traffic += 30; 
		c.write("HTTP/1.1 500 Connection error\r\n\r\n"); 
		c.end(); 
	  
	  });


    } else if(data[0] == 5 && version == 0)
    { 

      version = 5;
      c.write( String.fromCharCode(5)+""+String.fromCharCode(0));
	  

    } else if(version == 5 && port == "")
    {  

       if( data[3] == 3)
       {
        
         port = data[6+data[4]];
		 
         if( data[7+data[4]] >= 0 ){ port += ""+data[6+data[4]]+""; }
        
         ip = data.toString().substring( 5 , data[4]+5 );

         dns.lookup(ip,function(err, address, family)
         { 

           domainsip = address.toString().split(".");
           if( domainsip.length > 0 )
           {
			   
            var str1 = ""+String.fromCharCode(5)+""+String.fromCharCode(0)+""+String.fromCharCode(0)+""+String.fromCharCode(1)+""+String.fromCharCode(domainsip[0]);
            var str2 = ""+String.fromCharCode(domainsip[1])+""+String.fromCharCode(domainsip[2])+""+String.fromCharCode(domainsip[3])+""+String.fromCharCode(port);
			
            c.write( str1+""+str2 );
			
           }

         });
        
       } else if( data[3] == 1)
       {

         port = data[8]+""+data[9];
		 
         ip = data[4]+"."+data[5]+"."+data[6]+"."+data[7];

         if( domainsip.length == 0 )
         { 
	 
          var ip1 = ip.split("."); 
          c.write( String.fromCharCode(5)+""+String.fromCharCode(0)+""+String.fromCharCode(0)+""+String.fromCharCode(1)+""+String.fromCharCode(ip1[0])+""+String.fromCharCode(ip1[1])+""+String.fromCharCode(ip1[2])+""+String.fromCharCode(ip1[3])+""+String.fromCharCode(port));
		  
         }

       }


    } else if(version == 5 && port > 0)
	{

      if( list_accessip.indexOf( c.remoteAddress.toString() ) == -1 )
      {
        c.write("HTTP/1.1 200 OK\r\n\r\n"); 
		c.write("<h1><b>Access Denied!<b></h1>"); 
		c.end(); 
		return;
      }

      
      var host = parseHead(data.toString()).Host;
	  
      if( blistdomain.indexOf( host ) != -1 )
      {
        c.write("HTTP/1.1 200 OK\r\n\r\n"); 
	    c.write("<h1><b>Access Denied!<b></h1><big>This domain( "+host+" ) is blacklisted.</big>"); 
	    c.end(); 
	    return;
      }

      socket = net.connect(port, ip, function() { traffic += data.length; socket.write( data );  });
   
      socket.on('data', function(chunk) { traffic += chunk.length; c.write(chunk); });

      socket.on('end', function() { c.end(); });

      socket.on('close', function() { c.end(); });

      socket.on('error', function(e) { traffic += 30; c.write("HTTP/1.1 500 Connection error\r\n\r\n"); c.end(); });
	  
    }
    
  });

  c.on('end', function(){ if(socket ){ socket.end(); } });

  c.on('error', function(error) { if(socket ){ socket.end(); } });

  
 } catch( e ){ sys.debug(e); }
  

}


function requestdatahttps(req,res)
{ 

     res.writeHead("HTTP/1.1 200 OK"); 
	 res.write("<h1><b>Access Denied!<b></h1><br><br>\
     <big>This server does not support HTTP Proxy. Use another server.</big>"); 
	 res.end(); 
	 return;
   
}


function requestdata(req,res)
{

 try 
 {

 
     var headers = req.headers; var ph = url.parse(req.url);

     if( list_accessip.indexOf( req.connection.remoteAddress ) == -1 )
     {
       res.writeHead("HTTP/1.1 200 OK"); res.write("<h1><b>Access Denied!<b></h1>"); res.end(); return;
     }

     if( blistdomain.indexOf( ph.hostname.toString() ) != -1 )
     {
       res.writeHead("HTTP/1.1 200 OK"); 
	   res.write("<h1><b>Access Denied!<b></h1><big>This domain( "+ph.hostname+" ) is blacklisted.</big>"); 
	   res.end(); 
	   return;
     }

     var options = { port: ph.port, hostname: ph.hostname, method: req.method, path: ph.path, headers: req.headers };

     var proxyRequest = http.request(options);
   
     proxyRequest.on('response', function(proxyResponse) 
     {
	   
       res.writeHead(proxyResponse.statusCode, proxyResponse.headers);

       traffic += JSON.stringify(proxyResponse.headers).length;

       proxyResponse.on('data', function(chunk) { traffic += chunk.length; res.write(chunk, 'binary'); });

       proxyResponse.on('end', function() { res.end(); });


    });

    proxyRequest.on('error', function(e) { res.end(); });

    req.on('data', function(chunk) { traffic += chunk.length; proxyRequest.write(chunk, 'binary'); });
    req.on('end', function() { proxyRequest.end(); });

  
 } catch( e ){ sys.debug(e); }

}



try 
{

	fs.readFile( "funproxy.dat", function(err , data )
	{

		data = data.toString();

		var ind = data.indexOf("[Types proxy]"); var nul = data.indexOf("\r\n\r\n"); 
		optproxy = data.substring( ind , nul ).split("\r\n");
		optproxy.splice(0,1);
		data = data.substring(nul+1);
   
		var ind1 = data.indexOf("[Port proxy]"); var nul1 = data.indexOf("\r\n\r\n"); 
		optport = data.substring( ind1 , nul1 ).split("\r\n");
		optport.splice(0,1);
		data = data.substring(nul1+1);

		var ind2 = data.indexOf("[Blacklist domain]"); var nul2 = data.indexOf("\r\n\r\n"); 
		optbdom = data.substring( ind2 , nul2 ).split("\r\n");
		optbdom.splice(0,1);
		blistdomain = optbdom;
		data = data.substring(nul2+1);

		var ind3 = data.indexOf("[Types HTTP method]"); var nul3 = data.indexOf("\r\n\r\n"); 
		optmethod = data.substring( ind3 , nul3 ).split("\r\n");
		optmethod.splice(0,1);
		listmethod = optmethod;
		data = data.substring(nul3+1);

		if( optproxy[1] == "HTTPS-Proxy: on")
		{
			var serverhttps = http.createServer(requestdatahttps); serverhttps.on('connect', httpsreq); serverhttps.listen(optport[1].split(" ")[1],function(){ });
		}

		if( optproxy[0] == "HTTP-Proxy: on")
		{
			var server = http.createServer(requestdata); server.listen(optport[0].split(" ")[1],function(){ });
		}

		if( optproxy[2] == "SOCKS-Proxy: on")
		{
			var sock = net.createServer(sockserver).listen(optport[2].split(" ")[1]);
		}

	});

	
} catch(e){ sys.debug(e); };



setInterval(function(){

 try
 {
   var kb = 'kb'; var traf = 0; var trafproc = "";

   if( traffic <= 1024 ){  kb = 'B'; traf = traffic; } else
   if( traffic > 1024 && traffic <= 1024000 ){ trafproc = ""; kb = 'KB'; traf = traffic/1000; } else 
   if( traffic > 1024000 && traffic <= 1024000000 ){ trafproc ="."+Math.round(traffic%1000%1000); kb = 'MB'; traf = traffic/1000/1000; } else
   if( traffic > 1024000000 && traffic <= 1024000000000 ){ kb = 'GB'; traf = traffic/1000/1000/1000; trafproc ="."+Math.round(traffic%1000%1000%1000); }
 
   trafproc = trafproc.substring( 0, 3 );
   if( trafproc[2] == 0 ){ trafproc = trafproc.substring(0,2); }

   //sys.debug("Traffic: "+Math.round(traf)+trafproc+" "+kb);

 } catch( e ){ sys.debug(e); }

},10000);


function parseHead( data )
{

  var data = data.toString().substring( 0 , data.toString().indexOf("\r\n\r\n") );
  
  var spl = data.split("\r\n");
  jskey = {};
  
  for( var k in spl )
  {

   if( k == 0)
   { 

    var key = spl[k].split(" ");
    var kk = "Method";
	
    if( key[0] ){ jskey[kk] = key[0].trim(); }

    var kk = "Path";
	
    if( key[1]){ jskey[kk] = key[1].trim(); }

    var kk = "Version";
	
    if(key[2]){ jskey[kk] = key[2].trim(); }
    continue; 
	
   }

   var key = spl[k].split(":");
   
   if( !key[1] ){ continue; }
   
   var kk1 = key[0];
   
   jskey[kk1] = key[1].trim();

  }

  return jskey;


}