<?php

require('./config.php');

/**
 * Class used for creating objects representing the connection to the database
 * used by linCC. It also give some helpful methods.
 */
class linCC_mysqli extends mysqli {
    public function __construct() {

        parent::__construct(
            $host = DB_HOST,
            $username = DB_USER,
            $passwd = DB_PASS,
            $dbname = DB_NAME,
            $port = DB_PORT);
        // (constants defined in config.php)

        if (mysqli_connect_error()) {
            die('Connect Error (' . mysqli_connect_errno() . ') ' .
                mysqli_connect_error());
        }
    }


    /**
     * Get the fields of a specific table.
     *
     * Perform a 'SHOW COLUMNS FROM <tname>' query for retrieving the
     * columns name of the given table $tname.
     *
     * @param $tname: string representing the name of the table on which take
     *                the field names
     *
     * @return an array composed of the field names of the given table $tname
     */
    public function get_fields($tname) {

        $fields = array();

        $sql_query = "SHOW COLUMNS FROM " . $tname;
        if ($result = $this->query($sql_query)) {
            while ($column = $result->fetch_assoc()) {
                array_push($fields, $column['Field']);
            }
            // free result set
            $result->free();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $fields;
    }


    /**
     * Get the primary key field name of a specific table.
     *
     * Perform a 'SHOW KEYS FROM <tname> WHERE Key_name="PRIMARY"' query for
     * retrieving the column name of the primary key of the given table.
     *
     * @param $tname: string representing the name of the table on which take
     *                the field names
     *
     * @return a string representing the column name of the primary key of the
     *         given table
     */
    public function get_pkey($tname) {

        $sql_query = "SHOW KEYS FROM " . $tname . " WHERE Key_name=\"PRIMARY\"";
        if ($result = $this->query($sql_query)) {
            $pkey = $result->fetch_assoc()['Column_name'];
            // free result set
            $result->free();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $pkey;
    }


    /**
     * Get all values of a column in a specific table.
     *
     * Perform a 'SELECT id, <field_name> FROM <table_name>' query for
     * retrieving pairs of id => values.
     *
     * @param $tname: string representing the name of the table on which take
     *                the field names
     *        $colname: string representing the name of the interested column
     *                  to retreive
     *
     * @return an assoc array composed of many id => value elements.
     */
    public function get_col($tname, $colname) {

        $pkname = $this->get_pkey($tname);
        $values = array();

        $sql_query = "SELECT " . $pkname . "," . $colname . " FROM " . $tname;
        if ($result = $this->query($sql_query)) {
            while ($entry = $result->fetch_assoc()) {
                $values[$entry[$pkname]] = $entry[$colname];
            }
            /* free result set */
            $result->free();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $values;

    }


    /**
     * Get all values of a specific table.
     *
     * Perform a 'SELECT * FROM <table_name>' query for retrieving the complete
     * table.
     *
     * @param $tname: string representing the name of the table on which take
     *                the field names
     *
     * @return an array filled with assoc arrays. The structure is better
     *         described with the following text:
     *         [
     *             // first row
     *             [ 'field1' => 'val1', 'field2' => 'val2', ... ],
     *
     *             // second row
     *             [ 'field1' => 'val1', 'field2' => 'val2', ... ]
     *         ]
     */
    public function get($tname) {

        $fields = array();

        $sql_query = "SELECT * FROM " . $tname;
        if ($result = $this->query($sql_query)) {
            while ($row = $result->fetch_assoc()) {
                array_push($fields, $row);
            }
            /* free result set */
            $result->free();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $fields;
    }

    /* TODO: this function is still experimental [domyno contribute]
     */
    public function getVarList(){

        $fields = array();

        $sql_query =
        "SELECT id, tagName,PLCConnections.PLCDesc,tagType.name, tagDB, tagByte, tagBIT, rValue, wValue, wFlag, tagComment" .
        "FROM varList" .
        "INNER JOIN PLCConnections" .
        "ON varList.tagPLCNo = PLCConnections.id" .
        "INNER JOIN tagType" .
        "ON varList.tagType = tagType.id";
        if ($result = $this->query($sql_query)) {
            while ($row = $result->fetch_assoc()) {
                array_push($fields, $row);
            }
            /* free result set */
            $result->free();
        }
        else {
            die("Error: failure on query: " . $sql_query);
        }

        return $fields;
    }


    /* remove a row in the database
     */
    public function remove($tname, $id) {
        $pkname = $this->get_pkey($tname);
        $sql_query = "DELETE from " . $tname . " WHERE " . $pkname . "=" . $id;
        return $this->query($sql_query);
    }


    /* funzione chiamata da ajax.php
     */
    public function table_update($tname, $field, $value, $id) {
        $pkname = $this->get_pkey($tname);
        $sql_query =
            "UPDATE " . $tname . " SET " . $field . "=\"" . $value .
            "\" WHERE " . $pkname . "=" . $id;
        return $this->query($sql_query);
    }


    /* called by form.php
     */
    public function load($tname, $data) {
        $sql_query = "INSERT INTO " . $tname . " VALUES ";
        $groups = array();
        foreach ($data as $row) {
            // TODO: what if primary key is not on first field?
            array_push($groups, "(NULL, '" . implode("', '", $row) . "')");
        }
        $sql_query .= implode(", ", $groups);
        $this->query($sql_query) or die("impossibile eseguire la query");
    }
}


/* riempie e ritorna una stringa che descrive il tag thead (e il suo contenuto)
 * della tabella */
function table_header($tname) {

    $link = new linCC_mysqli();
    $field_names = $link->get_fields($tname);
    $pkname = $link->get_pkey($tname);
    $link->close();

    $theader = "<thead>" . PHP_EOL;
    foreach ($field_names as $name) {
        $theader .=
            "<th" . ($name === $pkname ?
                        " style=\"display:none;\" " :
                        "") .
            ">" . $name . "</th>" . PHP_EOL;
    }
    $theader .= "</thead>" . PHP_EOL;

    return $theader;
}


/* riempie e ritorna una stringa che descrive il tag tbody (e il suo contenuto)
 * della tabella */
function table_body($tname) {

    $link = new linCC_mysqli();
    $rows = $link->get($tname);
    $pkname = $link->get_pkey($tname);
    $link->close();

    $tbody = "<tbody>" . PHP_EOL;
    foreach ($rows as $row) {
        $tbody .= "<tr>";
        foreach ($row as $key => $val) {
            if (!isset($val)) {
                $val = "-";
            }
            $tbody .=
                "<td" . ($key === $pkname ?
                            " style=\"display:none;\" " :
                            " class=\"editable\" ") .
                ">" . $val . "</td>" . PHP_EOL;
        }
        $tbody .= "</tr>";
    }
    $tbody .= "</tbody>" . PHP_EOL;

    return $tbody;
}

/* Return an array filled with the names of the tables to display
 */
function get_table_names() {
    // TODO: read TODO in config.php
    global $table_names;
    return $table_names;
}

/* Print the table
 */
function get_table($tname) { ?>
    <table class="table table-condensed table-bordered" id="table">
        <?php echo table_header($tname); ?>
        <?php echo table_body($tname); ?>
    </table><?php
}

?>