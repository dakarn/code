<?

 namespace System\Form;


 class SForm {


    private $listElement = [];


   public function Builder( )
   {



     return $this;

   }



   public function createForm( )
   {


     echo implode( '' , $this -> listElement);


   }



   public function beginForm( $address = '', $method = 'post', $onSubmit ='' )
   {



     $this -> listElement[] = '<form action="'.$address.'" method="'.$method.'" onSubmit="'.$onSubmit.'">';



   }


   public function addSelect( $name = '', $value = [], $opt = [ 'transfer' => 0, 'size' => 1 , 'multiple' => false ] )
   {



     $text = '<select name="'.$name.'" size='.$opt['size'].'>';


     foreach( $value as $k => $v ) $text .= '<option value="'.$k.'">'.$v.'</option>';


     $text .= '</select>'.str_repeat('<br>', $opt['transfer']);


     $this -> listElement[] = $text;


     return $this;


   }


   public function addElement( $type = 'text', $value = '', $name = 'default', $opt = [ 'transfer' => 0 ] )
   {



     $this -> listElement[] = '<input type="'.$type.'" value="'.$value.'" name="'.$name.'">'.str_repeat('<br>', $opt['transfer']);

     return $this;


   }



   public function addTextarea( $name = '', $value = '', $opt = [ 'rows' => 2 , 'cols' => 50 ] )
   {



     $this -> listElement[] = '<textarea rows='.$opt['rows'].' cols='.$opt['cols'].' name="'.$name.'">'.$value.'></textarea>';

     return $this;


   }


   public function endForm( )
   {


     $this -> listElement[] = '</form>';


   }


 }