





function getC(id)
{

  var d=document.getElementsByClassName( id );
  return d[0];

} 


function getID( id )
{

  return document.getElementById(id);

}


var Window = (function()
{

  

  function compileCss( opt )
  {


   return 'border: thin solid black; display: block; top: '+opt.y+'px; left: '+Math.floor(document.body.getBoundingClientRect().left+opt.x)+'px;\
   position: fixed; background: '+opt.color+'; z-index: 202; width: '+opt.w+'px; height: '+opt.h+'px;\
   border-radius: 6px 6px 6px 6px; box-shadow: 8px 5px 5px gray';



  }


  function createShadow( shadow )
  {

    var parents = document.body;

    var create = document.createElement('div');

    if(shadow == 1){ create.id = 'shadow'; } else if(shadow == 0){ create.id = 'shadow1'; }

    parents.appendChild(create);

  }


  function createWin( options,title,shadow )
  {

    
    creates = document.createElement('div');

    creates.id = 'windcr';

    creates.setAttribute( 'style', compileCss(options) );

    document.body.appendChild(creates);

    var text = '<table><tr><td style="width:300px;padding-left:8px;"><big><font color=black>'+title+'</font></big></td>\
    <td align=right width='+options.w+'>\
    <img title="Закрыть" class=img_close src="http://5.19.253.227/musicjs/public/img/win-close.png"\
    onClick="Window.close();"></td></tr></table>';


    Window.setText(text);


    if(shadow == 1)
    { 

      getID('shadow').addEventListener("click", function(){ Window.close(); } );

    }

    if(shadow == 0)
    {

      getID('shadow1').addEventListener("click", function(){ Window.close(); } );

    }


    window.addEventListener( 'resize' , function( )
    {

      getID('windcr').style.left = document.body.getBoundingClientRect().left+options.x; 

    });


  }
  

  return {


   create: function(options, title , shadow1 )
   {

    createShadow(shadow1);

    createWin(options,title,shadow1);

    return this;

   },

   close: function()
   {


    document.body.removeChild( getID('windcr') );

    if( getID('shadow') ){ document.body.removeChild( getID('shadow') ); }

    if( getID('shadow1') ){ document.body.removeChild( getID('shadow1') ); }
    


   },

   hide: function()
   {

     getID('windcr').style.display = 'none';
    
   },


   move: function(x,y)
   {

     getID('windcr').style.top = y;
     getID('windcr').style.left = x;

   },


   setText: function(page)
   {

     getID('windcr').innerHTML = getID('windcr').innerHTML + page;
   
   }

 };


})();