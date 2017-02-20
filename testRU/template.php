<?

  foreach( $this->result as $k=>$v)
  {

      $month = substr( $v['dates'], 0 , 2 );
      $year = substr( $v['dates'], -2 );

      echo $month.'.'.$year.' '.$v['count'].' '.$v['sum'].'<br>';

  }