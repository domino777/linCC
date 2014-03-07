<?php

require_once('functions.php');

$csv_name = "csv";
// TODO: add separator char

if (isset($_FILES[$csv_name], $_POST['table_name']) &&
    $_FILES[$csv_name]['error'] === 0) {

    $data = array();
    $table_name = $_POST['table_name'];

    // TODO sanity check $table_name

    // $name = $_FILES[$csv_name]['name'];
    // $ext = strtolower(end(explode('.', $_FILES[$csv_name]['name'])));
    // $type = $_FILES[$csv_name]['type'];
    $tmpName = $_FILES[$csv_name]['tmp_name'];

    if(($handle = fopen($tmpName, 'r')) !== FALSE) {
        // necessary if a large csv file
        set_time_limit(0);

        // TODO: can omit lenght (but slowering)
//        while(($row = fgetcsv($handle, 1000, ',') !== FALSE) {
        while(($row = fgetcsv($handle, 1000, ',', '*')) !== FALSE) {

            // number of fields in the csv
            $cols = count($row);
            // TODO sanity check della row

            array_push($data, $row);
        }
        fclose($handle);
    }

    // STEP 2: write data do sql server (now $data content should e sanitized)
    $link = new linCC_mysqli();
    // TODO get and process return value
    $link->load($table_name, $data);
    $link->close();
}

// return back to index.php
header("Location:index.php");

?>
