<?


 class ConsoleApp extends DataSource implements Printable  {


    private $result;


   public function printResult()
   {

       require 'template.php';

   }


   public function loadData()
   {

      $this->loadFixtures();

   }


   public function createReport()
   {



      $db = $this->getDatabaseConnection();


      $q = $db->prepare( 'SELECT 
          d.* , p.* ,
          COUNT(*) as count, 
          SUM(amount) as sum, 
          strftime(\'%m.%Y\' , p.create_ts) as dates
          FROM
            payments as p LEFT JOIN documents as d 
          ON d.payment_id = p.id 
          WHERE d.payment_id IS NULL 
          GROUP BY strftime(\'%m\', p.create_ts)' );

      $q->execute();

      $this->result = $q->fetchAll( PDO::FETCH_ASSOC );

      $q->closeCursor();



   }



 }