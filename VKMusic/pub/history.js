var History = (function(){



 return {


   add: function( title )
   {

      var ser = document.getElementById('history-search');

      if( ser.innerHTML == "������� ������ �����!" ){ ser.innerHTML = ''; }


      ser.innerHTML += '<div style="cursor: pointer;" return false;"><big>'+title+'</big></div>';


   }

 };


})();