<?php

require('./config.php');

/* classe specifica per l'oggetto msqli utilizzato da linCC
 */
class linCC_mysqli extends mysqli {
    public function __construct() {

        global $db_host, $db_port, $db_user, $db_passwd, $db_name, $db_table;

        if (!isset($db_host, $db_port, $db_user, $db_passwd, $db_name,
                   $db_table)) {
            die("<p>Connection error: check values in file config.php</p>");
        }

        $this->db_host   = $db_host;
        $this->db_port   = $db_port;
        $this->db_user   = $db_user;
        $this->db_passwd = $db_passwd;
        $this->db_name   = $db_name;
        $this->db_table  = $db_table;

        parent::__construct($db_host . ":" . $db_port,
                            $db_user,
                            $db_passwd,
                            $db_name);

        if (mysqli_connect_error()) {
            die('Connect Error (' . mysqli_connect_errno() . ') ' .
                mysqli_connect_error());
        }
    }


    /* optional: pass table name */
    public function get_field_names() {

        $fields = array();

        if (func_num_args() == 1) {
            $table_name = func_get_arg(0);
        }
        else { // default value
            $table_name = $this->db_table;
        }

        $sql_query = "SHOW COLUMNS FROM " . $table_name;
        if ($result = $this->query($sql_query)) {
            while ($column = $result->fetch_array()) {
                array_push($fields, $column['Field']);
            }
            /* free result set */
            $result->close();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $fields;
    }


    /* TODO warning: può ritornare un ordine casuale? */
    public function get_values() {

        $fields = array();

        // TODO: ci saranno piu tabelle
        $table_name = func_num_args() == 1 ? func_get_arg(0) :
                                             $this->db_table;

        $sql_query = "SELECT * FROM " . $table_name;
        if ($result = $this->query($sql_query)) {
            // TODO: fecth assoc o altro?
            while ($row = $result->fetch_assoc()) {
                array_push($fields, $row);
            }
            /* free result set */
            $result->close();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $fields;
    }

    public function table_update($table, $field, $value, $id) {
        // TODO la chiave primaria deve essere definita altrove (mettichè non si chiama id)
        $sql_query = "UPDATE " . $table . " SET " . $field . "=" . $value . " WHERE id=" . $id;
        $result = $this->query($sql_query);
        // TODO che me ne faccio del result?
        //$result->close();
    }
}


/* riempie e ritorna una stringa che descrive il tag thead (e il suo contenuto)
 * della tabella */
function table_header() {

    $link = new linCC_mysqli();
    $field_names = $link->get_field_names();
    $link->close();

    $theader = "<thead>" . PHP_EOL;
    foreach ($field_names as $name) {
        $theader .= "<th>" . $name . "</th>" . PHP_EOL;
    }
    $theader .= "</thead>" . PHP_EOL;

    return $theader;
}


/* riempie e ritorna una stringa che descrive il tag tbody (e il suo contenuto)
 * della tabella */
function table_body() {

    $link = new linCC_mysqli();
    $rows = $link->get_values(); // TODO passargli un ordine?
    $link->close();

    $tbody = "<tbody>" . PHP_EOL;
    foreach ($rows as $row) {
        $tbody .= "<tr>";
        foreach ($row as $key => $val) {
            if (!isset($val)) {
                $val = "-";
            }
            // TODO sto id deve essere definito altrove
            if ($key === "id") {
                $tbody .= "<td class=\"immutable\">";
            }
            else {
                $tbody .= "<td class=\"editable\">";
            }
            $tbody .= $val . "</td>" . PHP_EOL;
        }
        $tbody .= "</tr>";
    }
    $tbody .= "</tbody>" . PHP_EOL;

    return $tbody;
}

?>