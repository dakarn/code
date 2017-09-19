<?

 namespace Application\Model;

 use \System\Database\ORM\SORMActive;



 class DemoModel extends SORMActive {





    public function tableName( )
    {


      return 'user';

    }


    public function primaryKey( )
    {


      return 'id';

    }


 }