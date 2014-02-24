<?php

require('./functions.php');

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
<div class="container">

    <div class="page_header">
        <h1>linCC
            <small>tabella
            <div class="btn-group">
                <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown">
                    varList <span class="caret"></span>
                </button>
                <ul class="dropdown-menu" role="menu">
                    <li><a href="#">varList</a></li>
                    <li><a href="#">PLCConnections</a></li>
                </ul>
            </div>
            </small>
        </h1>
    </div>

    <div class="row">
        <table class="table table-condensed table-bordered" id="table">
            <?php echo table_header(); ?>
            <?php echo table_body(); ?>
        </table>
    </div>

    <!-- <div class="row">
        <button>asd</button>
    </div> -->

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
