<?php

 require 'dataSource.php';
 require 'printtable.php';
 require 'ConsoleApp.php';



 $app = new ConsoleApp();

 $app->loadData();

 $app->createReport();

 $app->printResult();