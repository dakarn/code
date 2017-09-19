<?

 namespace System\Exception;

 use \System\Logger\SLogRun;


 abstract class SException extends \Exception {


  


   public function errormessage( $file , $msg, $line ) 
   {


     $string = file( $file )[$line-1]; 


     $loggger = new SLogRun( new \System\Logger\SLogger, [ $msg, $file, $line ] );


     exit('<h1>A server error</h1><br><b>In File: </b> '.$file.' <br><b>Error: </b>'.$msg.'<br> <b>Line:</b> '.$line.'<br><br>

     <div style = "font-size: 16px; background: silver; padding: 8px; "> <code> '.$string.' </code> </div>

    ');


     

   }


 }