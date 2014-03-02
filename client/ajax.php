<?php

require('functions.php');
// TODO sicurezza? un api token?

if (isset($_POST['action'])) {
        switch ($_POST['action']) {

            case 'update':
                isset($_POST['table'],
                      $_POST['field'],
                      $_POST['val'],
                      $_POST['id']) or
                    die("Malformed request. Check your form data");

                $link = new linCC_mysqli();
                $link->table_update($_POST['table'],
                                    $_POST['field'],
                                    $_POST['val'],
                                    $_POST['id']) or
                    die("Something went wrong with the query");
                $link->close();
                break;


            case 'get_table':
                isset($_POST['table']) or
                    die("Malformed request. Check your form data");
                get_table($_POST['table']);
                break;

            case 'get':
                isset($_POST['table'],
                      $_POST['field']) or
                    die("Malformed request. Check your form data");

                $link = new linCC_mysqli();
                $values = $link->get_col(
                    $_POST['table'],
                    $_POST['field']) or die("Something went wrong with the query");
                $link->close();
                echo json_encode($values);
                break;


            default:
                die("Action not defined");
                break;
        }
}
else {
    die("You must specify an action as post form data!");
}



?>