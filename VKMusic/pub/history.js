var History = (function(){


 maxcount = 12;


 function isCopy( title )
 {


      var classes = document.getElementsByClassName('item-history'); 

      for( var k in classes )
      {

        if( classes[k].innerHTML == title ) return [ true , classes.length ];

      }

      return [ false , classes.length ];

 }


 return {

  

   add: function( title )
   {

      
      var ser = document.getElementById('history-search');

      if( ser.innerHTML == "История поиска пуста!" ){ ser.innerHTML = ''; }

      var copy = isCopy( title );


      if( copy[0] ) return;
      if( maxcount <= copy[1] ) ser.innerHTML = '';



      ser.innerHTML += '<div class=item-history onClick="History.get(66);">'+title+'</div>';


   },


   get: function( title )
   {

     document.getElementsByName('music_name')[0].value = title;
     Music.requetsList();

   },


 };


})();