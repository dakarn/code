<?

 namespace System\Logger;


 class SLogger {



  public function write( $message )
  {



    $f = fopen( 'logs/logs.dat', 'a+' );


    fwrite( $f, 'File: '$message[1].' --- '.$message[0].' -- '.$message[2].' -error- ' );



  }


  public function read( $exp, $message )
  {





  }



 }