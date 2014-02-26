<?php

require('./config.php');

/* classe specifica per l'oggetto msqli utilizzato da linCC
 */
class linCC_mysqli extends mysqli {
    public function __construct() {

        global $db_host, $db_port, $db_user, $db_passwd, $db_name;

        if (!isset($db_host, $db_port, $db_user, $db_passwd, $db_name)) {
            die("<p>Connection error: check values in file config.php</p>");
        }

        $this->db_host   = $db_host;
        $this->db_port   = $db_port;
        $this->db_user   = $db_user;
        $this->db_passwd = $db_passwd;
        $this->db_name   = $db_name;

        parent::__construct($db_host . ":" . $db_port,
                            $db_user,
                            $db_passwd,
                            $db_name);

        if (mysqli_connect_error()) {
            die('Connect Error (' . mysqli_connect_errno() . ') ' .
                mysqli_connect_error());
        }
    }


    /* return an array filled withe the field names of the table $tname */
    public function get_field_names($tname) {

        $fields = array();

        $sql_query = "SHOW COLUMNS FROM " . $tname;
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


    /* return the content (as assoc array) of the given table $tname */
    public function get_values($tname) {

        $fields = array();

        $sql_query = "SELECT * FROM " . $tname;
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

    /* funzione chiamata da ajax.php
     */
    public function table_update($table, $field, $value, $id) {
        // TODO la chiave primaria deve essere definita altrove (mettichè non si chiama id)
        $sql_query = "UPDATE " . $table . " SET " . $field . "=" . $value . " WHERE id=" . $id;
        $result = $this->query($sql_query);
        // TODO che me ne faccio del result?
        //$result->close();
    }

    /* called by form.php
     */
    public function load($table, $data) {
        $sql_query = "INSERT INTO " . $table . " VALUES ";
        foreach ($data as $row) {
            $sql_query .= "( " . implode(", ", $row) . " )";
            if ($row !== end($data)) {
                $sql_query .= ",";
            }
        }
        echo $sql_query;
        $this->query($sql_query) or die("impossibile eseguire la query");
    }
}


/* riempie e ritorna una stringa che descrive il tag thead (e il suo contenuto)
 * della tabella */
function table_header($tname) {

    $link = new linCC_mysqli();
    $field_names = $link->get_field_names($tname);
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
function table_body($tname) {

    $link = new linCC_mysqli();
    $rows = $link->get_values($tname);
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

/* Return an array filled with the names of the tables to display
 */
function getTableNames() {
    // TODO: $table_names ora è definito in functions.php, ma sarebbe bello
    // poterlo ottenerlo dal server sql
    global $table_names;
    return $table_names;
}

/* Print the table
 */
function getTable($table_name) { ?>
    <table class="table table-condensed table-bordered" id="table">
        <?php echo table_header($table_name); ?>
        <?php echo table_body($table_name); ?>
    </table><?php
}

?>