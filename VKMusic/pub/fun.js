var Music = (function( )
{

  var offset = 0;
  var oldplay = -1;
  var lenresize = 24;

  if( navigator.userAgent.search( 'Android' ) != -1 || navigator.userAgent.search( 'Linux' ) != -1 ){ lenresize = 15; }

 
  function checkName( name , title )
  {


     if( name == null ){ name = "Неизвестно"; }
     if( title == null ){ title = "Неизвестно"; }

     if( name.length > lenresize ){ name = name.substring( 0 , lenresize ); }
     if( title.length > lenresize ){ title = title.substring( 0 , lenresize ); }

     if( name+title.length > 40 ){ name = name.substring( 0 , 15 ); title = title.substring( 0 , 15 ); }

     return [ name , title ];


  }


  function parseDuration( len )
  {

    var dur = [];

    dur.push( Math.floor( parseInt(len)/60) );   
    dur.push( Math.floor( parseInt(len)%60) ); 

    if( dur[1] < 10 ) dur[1] = '0'+dur[1];

    return dur;
    

  }

  function setList( data )
  {


     var json = JSON.parse(data); 

     var doc = document.getElementById('content-answer'); 

     doc.innerHTML = '<br>';


     if( json.success == 0 ){ doc.innerHTML = '<br><br><big>'+json.message+'</big>'; return; }
     if( json.list == "" ){ doc.innerHTML = '<br><br><big>Ой! Что-то пошло не так!</big>'; return; }


     doc.innerHTML = '<br><br><big>Всего найдено '+json.count+' MP3 <b>|</b> Показаны '+(offset+50)+'</big><br><br>';

     var lists = json.list;

     

     if( offset > 0 )
     { 

       doc.innerHTML += '<br><div class=btn-next\
       onClick="Music.setOffset( -50 ); Music.requetsList();"><b>Показать предыдущие</b></div><br>'; 

     }


     for( var k in lists )
     {


        var title = lists[k].title;
        var name = lists[k].artist;

        if( name == null && title == null ) continue;


        var resName = checkName( name , title );
        
        var dur = parseDuration( lists[k].length );


        doc.innerHTML += '<div id='+k+'\
        class=item-music data-id='+lists[k].id+' data-duration="'+lists[k].length+'" data-id1='+lists[k].id1+'>\
        '+resName[0]+'  -  '+resName[1]+'\
        <div class=img_fun>\ <div class=duration><small> '+dur[0]+':'+dur[1]+' </small></div>\
         <img onClick = "Music.loadingFile('+k+', Music.refreshLoad)" title="Скачать" src=pub/img/loadfile.png height=17>\
         <img id=goimg'+k+' onClick = "Music.loadingFile('+k+', Music.player)" title="Воспроизвести" src=pub/img/musicplay.png height=17>\
        </div>\
        </div>';
        

     }


     if( json.count > 100 + offset && json.list != "" )
     {

      doc.innerHTML += '<br><div class=btn-next\
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

    req.open( 'POST' , js.path, js.async );
    req.setRequestHeader( 'Content-Type', 'application/x-www-form-urlencoded' );
    req.send( js.param );

  }



  return {

 
   player: function( data , id )
   {


      var json = JSON.parse( data ); 
          
      if( !json.success ) return;


      if( document.getElementById( oldplay+'playmp3' ) ){ document.getElementById( oldplay+'playmp3' ).pause(); }


      if( !document.getElementById( id+'playmp3' ) )
      {

        document.getElementById(id).innerHTML += '<div id='+id+'audio>\
        <audio autoplay data-stop=true style="border: thin solid silver;" controls id='+id+'playmp3 src='+json.url+'></audio></div>';

        

        document.getElementById( id+'playmp3' ).onplay = function()
        {

          if( document.getElementById( oldplay+'playmp3' ) && oldplay != id )
          {
            document.getElementById( oldplay+'playmp3' ).pause(); 

          }

          oldplay = id;

        };


        document.getElementById( id+'playmp3' ).onended = function()
        {

          document.getElementById( id+'playmp3' ).play();

        };

        document.getElementById( id+'playmp3' ).oncanplay = function()
        {

          document.getElementById( id+'playmp3' ).play();

        };

        document.getElementById( 'goimg'+id )['onclick'] = null;

      }


   },


   refreshLoad: function( data , id )
   {

     var json = JSON.parse( data ); 
          
     if( json.success ){ open( json.url); }

   },


   submitOK: function()
   {

     if( Music.getOffset() > 11 ){ Music.setOffset( -50 ); } else if( Music.getOffset() == 0 ){ Music.setOffset( 0 ); }


     var title = document.getElementsByName( 'music_name' )[0].value;

     if( title == "" )
     {
        document.getElementById('content-answer').innerHTML = '<br><br><big>Вы не заполнили поле с названием!</big>'; return;
     }


     History.add(title);
     Music.requetsList();

   },


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
     

     var title = document.getElementsByName( 'music_name' )[0].value;

     document.getElementById('content-answer').innerHTML = '<br><br><img src="pub/img/loader.gif"><br>\
     Идет загрузка...';


     SendAjax({ 
      async: true,
      path: "pub/ajax.php",
      param: "action=requestList&title="+title+"&offset="+Music.getOffset()+"",
      even: function(data)
      {

            setList( data );

      } 
     });

   },


   
   loadingFile: function( id , callbacks )
   {

      var id1 = document.getElementById( id ).getAttribute( 'data-id' );
      var id2 = document.getElementById( id ).getAttribute( 'data-id1' );


      SendAjax({ 
       async: false,
       path: "pub/ajax.php",
       param: "action=loadingFile&id="+id1+"&id1="+id2,
       even: function(data)
       {

        callbacks( data , id );
           
       }
      });

   }


  };


})();