<?php

require('./functions.php');

$table_names = get_table_names();
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
<noscript>Warning, you need to enable javascript</noscript>

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
        <li><a href="#" id="load_csv_link">upload csv</a></li>
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

<div class="container" id="content">

  <div class="row">
    <?php get_table($def_table); ?>
  </div>

  <div class="row" id="csv">
    <div class="panel panel-default">
      <div class="panel-heading">
        <h3 class="panel-title">Upload csv file</h3>
      </div>
      <div class="panel-body">
        <form action="form.php" method="POST" enctype="multipart/form-data">
          <!-- TODO: transform in js | input[type=hidden]@name echoato in maniera intelligente -->
          <input type="hidden" name="action" value="csv_upload" />
          <input type="hidden" name="table_name" value="<?=$def_table?>" />
          <div class="form-group">
            <label>File input
            <input type="file" name="csv_file"/>
            </label>
          </div>
          <div class="form-group">
            <label>Separator
              <input type="text" class="form-control" name="sep" placeholder="default: ,">
            </label>
          </div>
          <div class="form-group">
            <input class="btn btn-primary" type="submit" value="upload"/>
          </div>
        </form>
      </div>
    </div>
  </div>

  <!-- Bootstrap core JavaScript
  ================================================== -->
  <!-- Placed at the end of the document so the pages load faster -->
  <script src="./lib/jquery/jquery-1.11.0.min.js"></script>
  <script src="./lib/bootstrap/js/bootstrap.min.js"></script>

  <!-- Highcharts JS
  ================================================== -->
  <!--script src="./lib/highcharts/js/highcharts.js"></script-->

  <!-- client script JS
  ================================================== -->
  <script src="./js/script.js"></script>
</div>
</body>
</html>
