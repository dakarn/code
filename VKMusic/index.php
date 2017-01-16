<?

  $i = 0;

  $count = 0;

  $postfield = 'act=a_load_section&al=1&album_id=-1&claim=0&offset=0&owner_id=113537351&search_history=0&search_lyrics=0&search_performer=0&search_q=scooter&search_sort=0&type=search';

  $c = curl_init('https://vk.com/al_audio.php'); 

  curl_setopt($c,CURLOPT_USERAGENT,"Opera/9.80 (Windows NT 6.1; WOW64) Presto/2.12.388 Version/12.16");

  curl_setopt($c,CURLOPT_POST,true);

  curl_setopt ($c, CURLOPT_SSL_VERIFYPEER, 0); curl_setopt ($c, CURLOPT_SSL_VERIFYHOST, 2);


  curl_setopt($c,CURLOPT_POSTFIELDS, $postfield ); curl_setopt($c,CURLOPT_COOKIE, file_get_contents('file/user-session.dat') );

  curl_setopt($c,CURLOPT_HTTPHEADER,array('X-Requested-With'=>'XMLHttpRequest'));

  curl_setopt($c,CURLOPT_RETURNTRANSFER,1); $result=curl_exec($c); curl_close($c); 

  $result =  substr( $result , strpos( $result , "[[" ) ); 

  $result = substr( $result , 1 , strpos( $result , "]]" ) );

  preg_match_all( '/\[(.*)"\]/isU' , $result , $res );

  $count = count( $res[1] );

  while ( $i < $count )
  {

    preg_match_all( '/"(.*)"/isU' , $res[1][$i] , $data );  
    preg_match( '/,([0-9]{1,3}),/i' , $res[1][$i] , $len ); 

    echo $data[1][4].' - '.$len[1].'<br>'; 

    ++$i;

  }