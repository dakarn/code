<?


class MP3ID3 {


 private $file;
 private $fp;
 private $lenfile;
 private $id3type = '';
 private $vers_id3 = 0;
 private $bt = 0 ;
 private $modecompress = 0;
 private $datatag = '';
 private $sizetag = 0 ;
 private $sizeframe = 0;

 private $genre_arr = array( "Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge", 
 "Hip-Hop","Jazz","Metal","New Age","Oldies","Other","Pop", 
 "R&B","Rap","Reggae","Rock","Techno","Industrial","Alternative", 
 "Ska","Death Metal","Pranks","Soundtrack","Euro-Techno","Ambient", 
 "Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance","Classical", 
 "Instrumental","Acid","House","Game","Sound Clip","Gospel", 
 "Noise","AlternRock","Bass","Soul","Punk","Space","Meditative", 
 "Instrumental Pop","Instrumental Rock","Ethnic","Gothic", 
 "Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance", 
 "Dream","Southern Rock","Comedy","Cult","Gangsta","Top 40", 
 "Christian Rap","Pop/Funk","Jungle","Native American","Cabaret", 
 "New Wave","Psychedelic","Rave","Showtunes","Trailer","Lo-Fi", 
 "Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical", 
 "Rock & Roll","Hard Rock", 
 "Folk","Folk/Rock","National Folk","Swing","Fast Fusion", 
 "Bebob","Latin","Revival","Celtic","Bluegrass","Avantgarde", 
 "Gothic Rock","Progressive Rock","Psychedelic Rock", 
 "Symphonic Rock","Slow Rock","Big Band","Chorus","Easy Listening", 
 "Acoustic","Humour","Speech","Chanson","Opera","Chamber Music", 
 "Sonata","Symphony","Booty Bass","Primus","Porn Groove", 
 "Satire","Slow Jam","Club","Tango","Samba","Folklore", 
 "Ballad","Power Ballad","Rhythmic Soul","Freestyle", 
 "Duet","Punk Rock","Drum Solo","Acapella","Euro-House", 
 "Dance Hall", "Goa", "Drum & Bass", "Club-House", "Hardcore", 
 "Terror", "Indie", "BritPop", "Negerpunk", "Polsk Punk", "Beat", 
 "Christian Gangs", "Heavy Metal", "Black Metal", "Crossover", 
 "Contemporary Ch?", "Cristian Rock", "Merengue", "Salsa", 
 "Thrash Metal", "Anime", "JPop", "Synthpop" );

 private $freq = 0;

 private $freq_arr = array(
  '00' => array( '11'=> '44100', '10' => '22050', '00'=> '11025' ),
  '01' => array( '11'=> '48000', '10' => '24000', '00'=> '12000' ),
  '10' => array( '11'=> '32000', '10' => '16000', '00'=> '8000' ),
  '11' => array( '11'=> '32000', '10' => '16000', '00'=> '8000' )

 );

 
 private $sample = 0;
 
 private $sample_arr = array(
  '00' => array( '01' => '576', '10' => '1152', '11' => '384' ),
  '10' => array( '01' => '576', '10' => '1152', '11' => '384' ),
  '11' => array( '01' => '1152', '10' => '384', '11' => '384' )

 );

 private $channel = 0;
 private $channel_arr = array('00'=>'Stereo','01'=>'Joint Stereo','10'=>'Dual channel','11'=>'Mono');

 private $mpegver = 0;
 private $mpegver_arr = array('00'=>'MPEG-2.5','10'=>'MPEG-2','11'=>'MPEG-1');

 private $layerver_arr = array('01'=>'Layer III','10'=>'Layer II','11'=>'Layer I');
 private $layerver = 0;

 private $duration = 0;
 private $data_v23 = array('TIT2'=>'','TIT3'=>'','TCON'=>'','TCOM'=>'','TYER'=>'',
 'TALB'=>'','TENC'=>'','TCOP'=>'','TRCK'=>'','TPE1'=>'','COMM'=>'','WXXX'=>'');

 private $data_v22 = array('TP2'=>'','TT2'=>'','TT3'=>'','TCN'=>'','TCM'=>'','TYE'=>'',
 'TAL'=>'','TCP'=>'','TRK'=>'','TP1'=>'','WXX'=>'','PIC'=>'');

 private $bitrate_num = array('0001'=>'0','0010'=>'1','0011'=>'2','0100'=>'3','0101'=>'4','0110'=>'5','0111'=>'6',
 '1000'=>'7','1001'=>'8','1010'=>'9','1011'=>'10','1100'=>'11','1101'=>'12','1110'=>'13');

 private $bitrate = array(
		'1111' => array(32,64,96,128,160,192,224,256,288,320,352,384,416,448),
		'1110' => array(32,48,56,64,80,96,112,128,160,192,224,256,320,384),
	        '1101' => array(32,40,48,56,64,80,96,112,128,160,192,224,256,320),				     
	        '1011' => array(32,48,56,64,80,96,112,128,144,160,176,192,224,256),
	        '1010' => array(8,16,24,32,40,48,56,64,80,96,112,128,144,160),
                '0010' => array(8,16,24,32,40,48,56,64,80,96,112,128,144,160),
                '0011' => array(32,48,56,64,80,96,112,128,144,160,176,192,224,256),
 );
	


 function __construct( $file = '' )
 {


  $this -> file = $file;

  if( $file != '' )
  {


    if( strpos( $file , '.mp3' ) === false ) exit( 'File not MP3' );

    $this -> fp = fopen( $this -> file, 'rb' );

    $this -> lenfile = filesize( $this -> file );


  } else {

   echo 'Can not open file';

  }





 }




 function exists_id3_2( )
 {


  fseek ( $this -> fp , 0 ); 

  $tag = fread( $this -> fp , 4 );


  if( $tag[0].$tag[1].$tag[2] == 'ID3' )
  {


    fseek( $this -> fp , 6 ); 

    $fd = fread( $this -> fp , 4 ); 

    $i = 0;


    while( $i < strlen( $fd ) )
    {

      $arr[] = bin2hex( $fd[$i] );
  
      $i++;

    }


    $this -> sizetag = bindec( base_convert( $arr[0] , 16 , 2 ).base_convert( $arr[1] , 16 , 2 ).
    base_convert( $arr[2] , 16 , 2 ).base_convert( $arr[3] , 16 , 2 ) );

    return true;

  }

  return false;

 }



 public function read_id3_v2( $vers )
 {

   fseek( $this -> fp , 6 ); 

   $fd = fread( $this -> fp , 4 ); 


   $i = 0;

   while( $i < strlen( $fd ) )
   {

     $arr[] = bin2hex( $fd[$i] );
  
     $i++;

   }


   $this -> sizetag = bindec( base_convert( $arr[0] , 16 , 2 ).base_convert( $arr[1] , 16 , 2 ).
   base_convert( $arr[2] , 16 , 2 ).base_convert( $arr[3] , 16 , 2 ) );


   $fd = fread( $this -> fp, $this -> sizetag + 10 );


   $i = 0; $size = 0; $msg = $fd; $arr = array(); $curlen = 0; $strlen = mb_strlen( $fd , 'UTF-8' );


   while( $i < 40 )
   {

    $type = $msg[0].$msg[1].$msg[2].$msg[3];

    $len = bindec( base_convert( bin2hex( $msg[4] ) , 16 , 2 ).base_convert( bin2hex( $msg[5] ) , 16 , 2 ).
    base_convert( bin2hex( $msg[6] ) , 16 , 2 ).base_convert( bin2hex( $msg[7] ) , 16 , 2 ) );

    $t = substr( $msg , 10 , $len );

 
    if( $type == 'APIC' )
    {

      fseek( $this -> fp , 0 );
      fseek( $this -> fp , $curlen + 10 ); 

      $fd = fread( $this -> fp, $this -> lenfile );
      $p = strpos( $fd , 'ÿÙ' );

      $strlen = $p + $curlen + 10 + 2 + 1200;

      $size = $p + 2;

      $tagpic = trim( substr( $fd , 0 , $size ) );

      fseek( $this -> fp , 0 ); fseek( $this -> fp, $p + $curlen + 2 + 10);

      $curlen += $size + 10;

      $msg = $tagpic.fread( $this -> fp , 1200 );
   

    } else {


      $size = $len + 10;

      $curlen += $size; 

      $this -> data_v23[$type] = $t;

    }


    $msg = substr( $msg , $size );

    if( $strlen <= $curlen ){ break; }

    $i++;


   } 

   return $this -> data_v23;

 }



 function read( )
 {

   if( $this -> exists_id3_2() ){ $this -> id3type.= '2,'; }

   fseek( $this -> fp , $this -> lenfile - 140 );

   $fd = fread( $this -> fp , 140 );

   $pos = strpos( $fd , 'TAG' );

   fseek( $this -> fp , $this -> lenfile + $pos - 140); 

   $fd = fread( $this -> fp , 140 - $pos );

   

   if( $fd[0].$fd[1].$fd[2] == 'TAG' )
   { 


     $this -> id3type.= '1,';

     $this -> datatag = $this -> read_id3_v1( $fd );


   } else {


     fseek( $this -> fp , 0 ); 

     $tag = fread( $this -> fp , 4 );


     if( $tag[0].$tag[1].$tag[2] == 'ID3' )
     { 

        fseek( $this -> fp , 0 ); 

        $this -> vers_id3 = '2.'.ord( $tag[3] );


       if( $this -> vers_id3 == 2.2)
       {

          $this -> datatag = $this -> read_id3_v22( ord($tag[3] ) );


       } else {


          $this -> datatag = $this -> read_id3_v2( ord( $tag[3] ) );


       }


     }


   }


   $this -> readFrame( );

   fclose( $this -> fp );

   return $this;

 }



 private function read_id3_v22($vers)
 {

   fseek( $this -> fp , 0 ); 

   fseek( $this -> fp , 6 ); 

   $this -> id3type.= '2,';

   $fd = fread( $this -> fp , 4 ); 



   $i = 0;

   $len = strlen( $fd );

   while( $i < $len )
   {


     $arr[] = bin2hex( $fd[ $i ] );
  
     $i++;


   }

   $this -> sizetag = bindec( base_convert( $arr[0],16,2).base_convert( $arr[1],16,2 ).
   base_convert( $arr[2],16,2 ).base_convert( $arr[3],16,2 ) );

   $fd = fread( $this -> fp , $this -> sizetag + 10 );

   $i = 0; $size = 0; $msg = $fd; $arr = array(); $curlen = 0; $strlen = mb_strlen( $fd , 'UTF-8' );


   while( $i < 40 )
   {


     $type = $msg[0].$msg[1].$msg[2];

     $len = bindec( base_convert( bin2hex($msg[4]),16,2 ).base_convert( bin2hex($msg[5] ),16,2 ).base_convert( bin2hex( $msg[6]),16,2 ).base_convert( bin2hex( $msg[7]) ,16,2) );

     $t = substr( $msg , 10 , $len );

     if( $type == 'PIC' )
     {


       file_put_contents( basename( $this -> file ).'.jpg', trim( substr( $t , 4 ) ) );


     } else {


      $size = $len + 10;

      $curlen += $size; 

      $this -> data_v22[$type] = $t;


     }


     $msg = substr( $msg , $size );
 
     if( $strlen <= $curlen ){ break; }

     $i++;


   } 


   return $this -> data_v22;


 }


 public function read_id3_v1($fd)
 {

     $pack='';

     if( $fd[125] == chr( 0 ) && $fd[ 126 ] != 0 )
     {


        $this -> vers_id3 = 1.1;
 
        $pack = unpack( 'a3TAG/a30Title/a30Artist/a30Album/cYear/a28Comment/x1/c1Track/c1Genre/' , $fd );


     } else { 

        $this -> vers_id3 = 1; $pack = unpack( 'a3TAG/a30Title/a30Artist/a30Album/a4Year/a30Comment/c1Genre/' , $fd ); 

     }

   
     return $pack;

 }



 function modeCompress( $fd )
 {
   
   if( $this -> mpegver == 11 && $this -> channel != 11 )
   {


     $zag = substr( $fd,0,36 ); 

     $head = $zag[32].$zag[33].$zag[34].$zag[35];


   } else if( $this -> mpegver == 11 && $this -> channel == 11 )
   {

     $zag = substr( $fd,0,36 ); 

     $head = $zag[32].$zag[33].$zag[34].$zag[35];

   }


   if( $head == 'Info' || $head == 'Xing' )
   {


     $head = 'Xing'; $length = substr($fd,40,4);

     $length = bin2hex( $length );

     $length = bindec( base_convert( $length,16,2 ) );

     return $length;


   } else if( strpos( $fd, 'VBRI' ) !== false )
   {


     $head = 'VBRI'; $length = substr($fd,46,4); $length = bin2hex( $length ); $length = bindec( base_convert( $length,16,2 ) );

     return $length;


   } else {


     return false;

   }


 }




 function getComment( $vers = '' )
 {

   if( $vers == 1 )
   { 

      return trim( $this -> datatag['Comment'] );


   } else if( $vers == 2 )
   { 


      return trim( str_replace( 'ÿþ' , '' , $this -> datatag['COMM'] ) );

   }



   if( $this -> vers_id3 != 0 )
   { 

     return $this -> vers_id3 == '2.3' ? trim( str_replace( 'ÿþ' , '' , $this -> datatag['COMM'] ) )
     : trim( $this -> datatag['Comment'] ); 

   }



 }



 function getArtist( $vers = '' )
 {

   if( $vers == 1 )
   {

     return trim( $this -> datatag['Artist'] );

   } else if( $vers == 2 )
   {

     return trim( str_replace( 'ÿþ', '', $this->datatag['TPE1'] ) );

   }


   if( $this -> vers_id3 != 0 )
   { 

     return $this -> vers_id3 == '2.3' ? trim( str_replace( 'ÿþ', '', $this -> datatag['TPE1'] ) ) : ( !empty( $this->datatag['Artist'] ) ? $this->datatag['Artist'] : '');

   }

 }



 function sizeID3v2Tag( )
 {


   return $this -> sizetag;


 }


 function id3_version( )
 {


   return $this -> vers_id3;


 }


 function getTitle( $vers = '' )
 {

   if($vers == 1 )
   {

    return trim($this->datatag['Title']);

   } else if($vers==2)
   {

     return trim(str_replace('ÿþ','',$this->datatag['TIT2'])); 

   }


   if($this->vers_id3!=0)
   {

     return $this->vers_id3=='2.3' ? trim(str_replace('ÿþ','',$this->datatag['TIT2'])) : (!empty($this->datatag['Title']) ? $this->datatag['Title']: '');

   }

 }



 function getAlbum( $vers = '' )
 {

   if( $vers == 1 )
   { 

     return trim($this->datatag['Album']); 

   } else if($vers==2)
   { 

     return trim(str_replace('ÿþ','',$this->datatag['TALB']));

   }

   if( $this -> vers_id3 != 0 ) return $this->vers_id3=='2.3' ? trim(str_replace('ÿþ','',$this->datatag['TALB'])) : trim($this->datatag['Album']);


 }


 function getYear( $vers = '' )
 {


   if($vers == 1 )
   { 

         return trim( $this -> datatag['Year'] );


   } else if( $vers == 2 )
   { 

         return trim( str_replace( 'ÿþ' , '' , $this -> datatag['TYER'] ) );

   }


   if( $this -> vers_id3 != 0 )
   {

         return $this -> vers_id3 == '2.3' ? trim( str_replace( 'ÿþ' , '' , $this -> datatag['TYER'] ) ) : trim( $this -> datatag['Year'] );

   }


 }


 private function searchFirstFrame( $fd )
 {

   
   if( ( $pos = strpos( $fd , 'ÿû' ) ) !== true) return $pos;

   if( ( $pos = strpos( $fd , 'ÿý' ) ) !== true) return $pos;

   if( ( $pos = strpos( $fd , 'ÿÿ' ) ) !== true) return $pos;

   if( ( $pos = strpos( $fd , 'ÿú' ) ) !== true) return $pos;


 }


 private function readFrame( )
 {


     fseek( $this -> fp , 0 ); $i = 0;

     $fd = fread( $this -> fp, $this -> lenfile );

 
     $pos = $this -> searchFirstFrame( $fd ); 


     if( strpos( $this -> id3type , '1' ) !== FALSE )
     {

       $len=$this->lenfile-$pos-128; 


     } else {


       $len=$this->lenfile-$pos;


     }

      
     $mpeg = base_convert(ord($fd[$pos+1]),10,2);

     $this -> mpegver = $mpeg[3].$mpeg[4];

     $this -> layerver = $mpeg[5].$mpeg[6];

     $bitrate = base_convert(ord($fd[$pos+2]),10,2);

     $bitrate = str_pad($bitrate,'8','0',STR_PAD_LEFT);

     $this -> bt = $bitrate[0].$bitrate[1].$bitrate[2].$bitrate[3];

     $this- > bt = $this->bitrate[$this->mpegver.$this->layerver][$this->bitrate_num[$this->bt]];

     $this -> freq = $bitrate[4].$bitrate[5]; 
     

     if( $bitrate[6] == 1 )
     {

        $pos++; 

        $this -> sizeframe = (round((144*($this->bt.'000'))/$this->freq_arr[$this->freq][$this->mpegver]))+1;


     } else {


        $this -> sizeframe = round((144*($this->bt.'000'))/$this->freq_arr[$this->freq][$this->mpegver]);

     }
     
     
     $channel = base_convert( ord( $fd[ $pos+3 ] ) , 10 , 2 ); $channel = str_pad( $channel , '8' , '0' , STR_PAD_BOTH);
     

     $this -> channel = $channel[0].$channel[1]; 
 

     $len_xing = $this -> modeCompress( mb_substr( $fd , $pos+4 , 52 , 'cp1251' ) );

     if( !$len_xing )
     {

       $this -> duration = round( $len/( $this -> bt + 000) * 8 );


     } else {

    
       $this -> duration = round( ( $len_xing * $this -> sample_arr[$this->mpegver][$this -> layerver])
       /$this -> freq_arr[ $this -> freq ][ $this -> mpegver ] ).'000';


     }


 }



 function getDuration( )
 {

   return $this -> duration;

 }


 function getFrameSize( )
 {

   return $this -> sizeframe;

 }


 function getMpegVer( )
 {

  return $this -> mpegver_arr[$this -> mpegver];

 }


 
 function getLayerVer( )
 {

   return $this -> layerver_arr[$this -> layerver];

 }


 
 function getFreq( )
 {

   return $this -> freq_arr[$this -> freq][$this -> mpegver];

 }


 function getChannel( )
 {

   return $this -> channel_arr[$this -> channel];

 }


 public function getBitrate( )
 {

   return $this -> bt;

 }

 public function getVersType( )
 {

   return $this -> id3type;

 }




}