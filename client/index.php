<?php

require('./functions.php');

$table_names = getTableNames();
$def_table = $table_names[0];

?><!DOCTYPE html>

<html>
<head>
    <title>db_read</title>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap core CSS -->
    <link href="./lib/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <link href="./css/style.css" rel="stylesheet">
</head>

<body>
<noscript>Attenzione, javascript deve essere abilitato per il funzionamento di LinCC</noscript>

<nav class="navbar navbar-default navbar-fixed-top" role="navigation">
  <div class="container">
    <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href=".">linCC</a>
    </div><!-- /.navbar-header -->

    <!-- Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
      <ul class="nav navbar-nav">
        <li><a>showing: <span class="table_name"><?=$def_table;?></span></a></li>
      </ul>
      <ul class="nav navbar-nav navbar-right">
        <li class="dropdown" id="menu" >
          <a class="dropdown-toggle" data-toggle="dropdown">select table <b class="caret"></b></a>
          <ul class="dropdown-menu">
            <?php foreach ($table_names as $name) : ?>
              <li><a><?=$name;?></a></li>
            <?php endforeach; ?>
          </ul>
        </li>
      </ul>
    </div><!-- /.navbar-collapse -->
  </div><!-- /.container-fluid -->
</nav>

<div class="container">

  <div class="row">
    <?php getTable($def_table); ?>
  </div>

  <div class="row">
      <form action="form.php" method="POST" enctype="multipart/form-data">
          <!-- TODO: transform in js | input[type=hidden]@name echoato in maniera intelligente -->
          <input type="hidden" name"<?php echo "varList"?>" />
          <input type="file" name="csv"/>
          <input type="submit"/>
      </form>
      <!-- <form class="form-horizontal" role="form">
          <div class="form-group">
              <label class="sr-only">cvs file
                  <input type="text" class="form-control" placeholder="cvs file">
              </label>
          </div>

          <div class="input-group">
            <input type="text" class="form-control" placeholder="cvs file">
          </div>
          <button type="button" class="btn btn-default">
              <span class="glyphicon glyphicon-open"></span> upload csv
          </button>
      </form>

      <form class="form-inline" role="form">
          <div class="form-group">
              <label class="sr-only" for="exampleInputEmail2">Email address</label>
              <input type="email" class="form-control" id="exampleInputEmail2" placeholder="Enter email">
          </div>
          <div class="form-group">
              <label class="sr-only" for="exampleInputPassword2">Password</label>
              <input type="password" class="form-control" id="exampleInputPassword2" placeholder="Password">
          </div>
          <div class="checkbox">
              <label>
                  <input type="checkbox"> Remember me
              </label>
          </div>
          <button type="submit" class="btn btn-default">Sign in</button>
      </form> -->
  </div>

  <!-- Bootstrap core JavaScript
  ================================================== -->
  <!-- Placed at the end of the document so the pages load faster -->
  <script src="./lib/jquery/jquery-1.11.0.min.js"></script>
  <script src="./lib/bootstrap/js/bootstrap.min.js"></script>

  <!-- Highcharts JS
  ================================================== -->
  <script src="./lib/highcharts/js/highcharts.js"></script>

  <!-- demo JS
  ================================================== -->
  <script src="./js/demo.js"></script>
</div>
</body>
</html>
