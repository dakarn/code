var Music = (function( )
{

  var offset = 0;


  window.addEventListener('load', function()
  { 
    document.getElementById('btn').addEventListener('click', function()
    {

      Music.setOffset( -50 );
      Music.requetsList();

    });

  });


  


  function setList( data )
  {

     var json = JSON.parse(data); var lists = json.list;

     var doc = document.getElementById('content-answer'); 

     doc.innerHTML = '<br>';


     for( var k in lists )
     {


        var title = lists[k].title;

        var name = lists[k].artist;


        if( name == null && title == null ) continue;

        if( name == null ){ name = "Неизвестно"; }
        if( title == null ){ title = "Неизвестно"; }
        


        doc.innerHTML += '<div title="Перейти к скачиванию" onClick="Music.loadingFile('+k+')" id='+k+'\
        class=item-music data-id='+lists[k].id+' data-id1='+lists[k].id1+'>\
        '+name+'  -  '+title+'\
        </div>';

        

     }


     doc.innerHTML += '<br><div style="width: 150px; padding: 8px; background: lightgreen; border: thin solid black; cursor: pointer;"\
     onClick="Music.setOffset( 50 ); Music.requetsList();"><b>Показать ещё</b></div>';
    
  }



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


   getOffset: function()
   {

     return offset;

   },

   setOffset: function( offsets )
   {

      offset += offsets;

   },

   requetsList: function()
   {
     
     var title = encodeURIComponent( document.getElementsByName( 'music_name' )[0].value );

     if( title == "" ){ document.getElementById('content-answer').innerHTML = '<br><br><big>Вы не заполнили поле с названием!</big>'; return; }

     document.getElementById('content-answer').innerHTML = '<br><br><img src="pub/img/loader.gif"><br>\
     Идет загрузка...';

     SendAjax({ 
     path: "pub/ajax.php",
     param: "action=requestList&title="+title+"&offset="+Music.getOffset()+"",
     even: function(data)
     {

            setList( data );

     }});

   },


   
   loadingFile: function( id )
   {

      var id1 = document.getElementById( id ).getAttribute( 'data-id' );
      var id2 = document.getElementById( id ).getAttribute( 'data-id1' );


      SendAjax({ 
      path: "pub/ajax.php",
      param: "action=loadingFile&id="+id1+"&id1="+id2,
      even: function(data)
      {
           var json = JSON.parse( data ); 
          
           if( json.success ){ location.href = json.url; }
      }});

   }


  };


})();