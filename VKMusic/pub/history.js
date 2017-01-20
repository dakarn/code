var History = (function(){



 return {


   add: function( title )
   {

      var ser = document.getElementById('history-search');

      if( ser.innerHTML == "История поиска пуста!" ){ ser.innerHTML = ''; }


      ser.innerHTML += '<div style="cursor: pointer;" return false;"><big>'+title+'</big></div>';


   }

 };


})();