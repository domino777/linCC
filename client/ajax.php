<?php

require('functions.php');
// TODO sicurezza? un api token?

if (isset($_POST['action'])) {
        switch ($_POST['action']) {
            case 'update':
                // TODO che da culo, walter sei ubriaco torna a casa
                isset($_POST['table'],
                      $_POST['field'],
                      $_POST['val'],
                      $_POST['id']) or die("richiesta malformata");


                $link = new linCC_mysqli();
                $link->table_update(
                    $_POST['table'],
                    $_POST['field'],
                    $_POST['val'],
                    $_POST['id']) or die("something went wrong con la query");
                $link->close();
                break;

            case 'get_table':
                getTable($_POST['table']);
                break;

            case 'get':
                $link = new linCC_mysqli();
                // TODO sanitize here
                $values = $link->get(
                    $_POST['table'],
                    $_POST['field']) or die("something went wrong con la query");
                $link->close();
                echo json_encode($values);
                break;

            default:
                die("azione non definita");
                break;
        }
}
else {
    die("cosa avevi intenzione di fare?");
}



?>