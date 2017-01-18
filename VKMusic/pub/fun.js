var Music = (function( )
{

  var offset = 0;


  window.addEventListener('load', function()
  { 
    document.getElementById('btn').addEventListener('click', function()
    {

      if( Music.setOffset > 1 ){ Music.setOffset( -50 ); } else if( Music.setOffset == 0 ){ Music.setOffset( 0 ); }
      Music.requetsList();

    });

  });


  


  function setList( data )
  {

     var json = JSON.parse(data);

     var doc = document.getElementById('content-answer'); 

     doc.innerHTML = '<br>';


     if( json.success == 0 ){ doc.innerHTML = '<br><br><big>'+json.message+'</big>'; return; }


     doc.innerHTML = '<br><br><big>Всего найдено '+json.count+' MP3 <b>|</b> Показаны '+(offset+50)+'</big><br><br>';

     var lists = json.list;

     

     if( offset > 0 ){ doc.innerHTML += '<br><div style="text-align: center; width: 180px; padding: 8px; background: lightgreen; border: thin solid gray; cursor: pointer;"\
     onClick="Music.setOffset( -50 ); Music.requetsList();"><b>Показать предыдущие</b></div><br>'; }


     for( var k in lists )
     {


        var title = lists[k].title;

        var name = lists[k].artist;


        if( name == null && title == null ) continue;

        if( name == null ){ name = "Неизвестно"; }
        if( title == null ){ title = "Неизвестно"; }
        
        name = name.replace( /(www|http)(.*)\.(.*){2,5}/ig , '' );    
        title = title.replace( /(www|http)(.*)\.(.*){2,5}/ig , '' );    

        doc.innerHTML += '<div title="Перейти к скачиванию" onClick="Music.loadingFile('+k+')" id='+k+'\
        class=item-music data-id='+lists[k].id+' data-id1='+lists[k].id1+'>\
        '+name+'  -  '+title+'\
        </div>';

        

     }


     if( json.count > 100 + offset && json.list != "" )
     {

      doc.innerHTML += '<br><div style="text-align: center; width: 170px; padding: 8px; background: lightgreen; border: thin solid gray; cursor: pointer;"\
      onClick="Music.setOffset( 50 ); Music.requetsList();"><b>Показать ещё</b></div>';

     }
    
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