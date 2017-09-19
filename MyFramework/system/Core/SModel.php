<?

  namespace System\Core;


  class SModel {



    public static function factory( $model )
    {


      return new $model;


    }


 }