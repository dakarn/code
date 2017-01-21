var ValidationForm = (function()
{

   var column=[];
   var rule=[];
   var options=[];
   var errlist=[];
   var errno='';


   function _empty(column)
   {
    
    if(document.getElementsByName(column)[0].value.length>0){ return true; }
    else { errlist[column]='Не заполнено поле '+column.toUpperCase()+'<br>'; return false; }

   }


   
   function _reg(column,patterns)
   {

    pat=/^[a-z]{1,4}/i;
    if(patterns.test(document.getElementsByName(column)[0].value)) { return true; } 
    else { errlist[column]='Не верно заполнено поле '+column.toUpperCase()+'<br>'; return false; } 

   }


   function _email(column)
   {

    
    re=/^[a-z0-9_]{2,30}[@]{1}\w{2,10}[.]{1}[a-z]{2,5}$/i; 
    if(re.test(document.getElementsByName(column)[0].value)){ return true; } 
    else { errlist[column]='Не верно заполнено поле '+column.toUpperCase()+'<br>'; return false; }
 
   }


   function _int(column)
   {

    errlist[column]='Поле '+column.toUpperCase()+' должно содержать число<br>'; re=/[0-9]{1,}/;
    return re.test(document.getElementsByName(column)[0].value) ? true : false; 

   }


   function _confirm_text(column)
   {

    spl=column.split(',');
    errlist[column]='Поля '+spl[0].toUpperCase()+' и '+spl[1].toUpperCase()+' должны содержать одинаковое значение<br>';
    return document.getElementsByName(spl[0])[0].value==document.getElementsByName(spl[1])[0].value ? true : false;

   }




   function _min_max(column,opt)
   {

   
    errlist[column]='Не верная длина поля '+column.toUpperCase()+'<br>';

    var rows=document.getElementsByName(column)[0].value;


    if(typeof opt.ave=='undefined')
    {  

      return rows.length>=opt.min && rows.length<=opt.max ?  true : false; 

    } else {  return rows.length==opt.ave ?  true : false;  }
    
   
 
   }


   return 
   {


   check : function()
   {

     for(i=0;i<rule.length;++i)
     {

       switch(rule[i])
       {

        case 'regex': errno+=_reg(column[i],options[i]); break;
        case 'empty': errno+=_empty(column[i]); break;
        case 'email': errno+=_email(column[i]); break;
        case 'length': errno+=_min_max(column[i],options[i]); break;
        case 'int': errno+=_int(column[i]); break;
        case 'confirm': errno+=_confirm_text(column[i]); break;
        
       }

       

     }

     delete column;
     delete rule;
     delete options;

     if(errno.search('false') == -1){ errno=''; return true; } else { errno=''; return false; }

   },

   
   add : function(name,type)
   {

    column[column.length]=name;

    rule[rule.length]=type;

    if(typeof arguments[2]!='undefined') { options[options.length]=arguments[2]; } else { options[options.length]=null; }
     
    return this;

   },


   errorlist : function()
   {

     if(typeof arguments[0] != 'undefined' ){ return errlist[arguments[0]]; } else { return errlist; }
    

   },


   errorView : function(div)
   {

     if(document.getElementById(div)){ getID(div).innerHTML=''; }

     if(typeof arguments[1] == 'undefined')
     {

       for(var item in errlist) 
       {

        getID(div).innerHTML+=errlist[item]; 

       }
       

     } else { getID(div).innerHTML=errlist[arguments[1]];  }
    

   }



  };


 

})();
