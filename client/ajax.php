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

            default:
                die("azione non definita");
                break;
        }
}
else {
    die("cosa avevi intenzione di fare?");
}



?>