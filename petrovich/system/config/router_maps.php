<?php

$router = [
		[ 'path' => '', 'controller' => 'Controller:PageController', 'action' => 'index' ],
		[ 'path' => 'item-page', 'controller' => 'Controller:PageController', 'action' => 'itemPage' ],
		[ 'path' => 'page-list', 'controller' => 'Controller:PageController', 'action' => 'listPages' ],
		[ 'path' => 'edit-page', 'controller' => 'Controller:ManagerController', 'action' => 'editPage' ],
		[ 'path' => 'add-page', 'controller' => 'Controller:ManagerController', 'action' => 'addPage' ],
		[ 'path' => 'delete-page', 'controller' => 'Controller:ManagerController', 'action' => 'deletePage' ],
		[ 'default' => '', 'controller' => 'Controller:PageController', 'action' => 'index' ],

];