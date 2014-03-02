(function($){

var table_selector = '#table';
var menu_selector  = '#menu .dropdown-menu';


/* give functionality to the table */
var table_func = {

    init: function(){
        this.table = table_selector;
        this.showing = $('span.table_name').first().text();

        $(this.table).on('click', 'td.editable', this.td_insert);

        // add cells for adding and removing rows
        this.add_meta_cells();

        // add some data information to cells for better performance
        this.add_metadata();

        // start the sync process for the tabe
        //this.sync_table();
    },


    /* when clicked transform the cell into an input element */
    td_insert: function(){
        if ($(this).hasClass("warning"))
            return; // already in use

        // if another cell is in insert mode revert it to a normal table cell
        $(this.table).find('input').each(function(){
            // restore an eventual original value
            var orig_value = $(this).parent().data('orig_value');
            var val = $(this).val();
            $(this).parent()
                .removeClass('warning')
                .empty()
                .html(orig_value ? orig_value : val);
        });

        var curVal = $(this).text();
        var curWidth = $(this).width();
        var inputTag = $("<input type=\"text\"/>");
        inputTag.on('keydown', table_func.td_done); // add callback when done
        $(this).addClass("warning")
               .empty()
               .append(inputTag)
               .data('orig_value', curVal);
        inputTag.val(curVal)
                .width(curWidth)
                .select();
    },


    /* Callback triggered when the user press enter.
       Send the update to the database and transforms the input element back to
       a td */
    td_done: function(e){
        if (e.which !== 13)
            return; // not enter. do nothing

        var newVal = $(this).val();
        var cell = $(this).parent('td');

        cell.empty()
            .text(newVal)
            .removeClass("warning");

        if (cell.data('orig_value') === newVal)
            return; // same value. Don't send update

        // TODO use table_func.add_metadata
        var val = newVal;
        var id = cell.parent('tr').children('td').first().text();
        var colIdx = cell.parent().children().index(cell);
        var colName = cell.closest('table').find('th:nth-child(' + (1 + colIdx) + ')').text();

        // do the ajax request
        $.ajax({
            type: "POST",
            url: "ajax.php",
            data: {
                action: "update",
                table : this.showing,
                field : colName,
                val   : val,
                id    : id
            }
        });
    },


    /* add extra cell for adding and removing rows */
    add_meta_cells: function(){
        var row_deleter = $("<td></td>");
        row_deleter.text("delete")
                   .addClass("row_deleter");
        $(this.table).find("tbody tr").append(row_deleter);

        var row_adder = $("<tr></tr>");
        var colspan = $(this.table).find("tbody tr").last().children("td.editable").size();
        row_adder.append($("<td style=\"visibility:hidden;\"></td>"))
                 .append($("<td colspan=\"" + colspan + "\" class=\"row_adder\"></td>").text("add"));
        $(this.table).find("tbody").append(row_adder);
    },


    /* updates the column rValue every 1 second
     * TODO: something to fix here, like the vars (they should stay in another place)
     */
     sync_table: function(){
        var delay = 1; // seconds
        var col_sync_name = 'rValue';
        var table  = 'varList';
        var fn_update = function(){
            // do the ajax request
            $.ajax({
                type: "POST",
                url: "ajax.php",
                dataType: 'json',
                data: {
                    action: "get",
                    table : table,
                    field : col_sync_name
                }
            }).done(function(data){
                console.log("ajax done for column " + col_sync_name);
                $(table_func.table).find('tbody').children().each(function(row_idx,row){
                    var row_id = $(row).children().first().text(); // TODO this info should come with html5 data
                    $(row).children().each(function(idx,td){
                        if ($(td).data('col') === col_sync_name) {
                            $(td).text(data[row_id]);
                        };
                    });
                });
            });
        };
        window.setInterval(fn_update, 1000);
        // fn_update();

     },


     /* add html5 data values to the table cells */
     add_metadata: function(){
        // get a map composed of pairs of  <column position>: <column name>
        var theader_data = {};
        $(this.table).find('th').each(function(){
            var pos = $(this).parent().children().index($(this));
            var name = $(this).text();
            theader_data[pos] = name;
        });

        // add metadata to the entire table
        $(this.table).find('tbody tr').each(function(row_idx, row){
            $(row).children('td').each(function(idx, el){
                $(el).data("col", theader_data[idx]);
            });
        });
     },
};


/* give functionality to the table menu in the top bar */
var menu = {
    init: function(){
        this.menu = menu_selector;
        $(this.menu).on('click', 'li', this.change_table);
    },


    change_table: function(e) {
        var new_name = $(this).text();
        if ($('span.table_name').first().text() === new_name) {
            // Do nothing
            return;
        };
        $('span.table_name').text(new_name);

        var tmp_placeholder =
            '<p class="text-center" style="padding:20px;">' +
            '<img src="img/ajax-loader.gif"/><p>';

        var table_parent = $(table_selector).parent();

        table_parent.html(tmp_placeholder);
        $.ajax({
            type: "POST",
            url: "ajax.php",
            data: {
                action: "get_table",
                table : new_name
            }
        }).done(function(data){
            table_parent.html(data).hide().fadeIn('fast');
            table_func.init();
        });

    }
}

$(document).ready(function(){

    $('#content').fadeIn(); // show only if js enabled

    menu.init();
    table_func.init();
});

})(jQuery);