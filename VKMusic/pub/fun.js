var Music = (function( )
{

  window.addEventListener('load', function()
  { 
    document.getElementById('btn').addEventListener('click', function()
    {
      Music.requetsList();
    });

  });


  function SendAjax( js )
  {

    var req = new XMLHttpRequest();
    req.onreadystatechange = function()
    { 
       if ( req.readyState == 4 ){ js.even(req.responseText); }
    }

    req.open( 'POST' , js.path, true );
    req.setRequestHeader( 'Content-Type', 'application/x-www-form-urlencoded' );
    req.send( js.param );

  }


  return {


   requetsList: function()
   {

     document.getElementById('content-answer').innerHTML = '<br><br><img src="pub/img/loader.gif"><br>\
     Идет загрузка...';

     SendAjax({ 
     path: "pub/ajax.php",
     param: "action=requetsList&title=",
     even: function(data)
     {
            
     }});

   },

   
   loadingFile: function()
   {


   }

  };


})();