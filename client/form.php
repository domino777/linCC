<?php

require_once('functions.php');


if (isset($_POST['action'])) {
    switch ($_POST['action']) {

        case 'csv_upload':
            (isset($_POST['table_name'],
                   $_POST['sep'],
                   $_FILES['csv_file']) and
             $_FILES['csv_file']['error'] === 0) or
                die("Malformed request. Check your form data");

            $link = new linCC_mysqli();
            $field_num = count($link->get_fields($_POST['table_name']));
            $link->close();

            $data = array();
            $table_name = $_POST['table_name']; // TODO sanity check $table_name
            $sep = $_POST['sep'] === "" ? "," : $_POST['sep']; // TODO sanity check sep (from client side)

            // TODO sanity check other parameters?
            // $name = $_FILES[$csv_name]['name'];
            // $ext = strtolower(end(explode('.', $_FILES[$csv_name]['name'])));
            // $type = $_FILES[$csv_name]['type'];
            $tmpName = $_FILES['csv_file']['tmp_name'];

            $malformed_csv = FALSE;

            if(($handle = fopen($tmpName, 'r')) !== FALSE) {
                // necessary if a large csv file
                set_time_limit(0);

                while(($row = fgetcsv($handle, 1000, $sep, '*')) !== FALSE) {
                    if (count($row) + 1 !== $field_num) {
                        $malformed_csv = TRUE;
                        break;
                    }
                    // TODO sanity check della row
                    array_push($data, $row);
                }
                fclose($handle);
            }

            // TODO be more informative on errors
            if ($malformed_csv) {
                die("malformed_csv");
            }

            // STEP 2: write data do sql server (now $data content should e sanitized)
            $link = new linCC_mysqli();
            // TODO get and process return value
            $link->load($table_name, $data);
            $link->close();

            break;


        default:
            die("Action not defined");
            break;
    }
}

// return back to index.php
header("Location:index.php");

?>
