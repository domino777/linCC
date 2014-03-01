(function($){

var table_selector = '#table';
var menu_selector  = '#menu .dropdown-menu';

/* give functionality to the table */
var table_func = {
    init: function(){
        this.table = table_selector;
        $(this.table).on('click', 'td.editable', this.td_insert);
        this.addMetaCells();
    },

    /* transform the cell into an input element */
    td_insert: function(){
        if ($(this).hasClass("warning"))
            // already in use
            return;

        // if another cell is in insert mode revert it to a normal table cell
        table_func.normalize_td();

        var curVal = $(this).text();
        var curWidth = $(this).width();
        var inputTag = $("<input type=\"text\"/>");
        inputTag.on('keydown', table_func.td_done);
        $(this).addClass("warning")
               .empty()
               .append(inputTag)
               .data('orig_value', curVal);
        inputTag.val(curVal)
                .width(curWidth)
                .select();
    },

    /* revert all table cell currently in insert mode (with an input child) to
     * simple cells */
    normalize_td: function(){
        $(this.table).find('input').each(function(){
            var orig_value = $(this).parent().data('orig_value');
            var val = $(this).val();
            $(this).parent()
                .removeClass('warning')
                .empty()
                .html(orig_value ? orig_value : val);
        });
    },

    /* transform the input element back to a td*/
    td_done: function(e){
        // TODO: se ci sono altri celle che sono in input mode, che fare?
        // TODO: fare un sistema di undo? tipo salvando il vecchio dato con html5 data?
        if (e.which !== 13) {
            // not enter. do nothing
            return;
        }
        var newVal = $(this).val();
        var cell = $(this).parent('td');
        cell.empty()
            .text(newVal)
            .removeClass("warning");

        // TODO!!! dis-hardcodarlo
        var table = "varList";
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
                table : table,
                field : colName,
                val   : val,
                id    : id
            }
        });
    },

    /* add extra cell for adding and removing rows */
    addMetaCells: function(){
        var row_deleter = $("<td></td>");
        row_deleter.text("elimina")
                   .addClass("row_deleter");
        $(this.table).find("tbody tr").append(row_deleter);

        var row_adder = $("<tr></tr>");
        var colspan = $(this.table).find("tbody tr").last().children("td.editable").size();
        row_adder.append($("<td style=\"visibility:hidden;\"></td>"))
                 .append($("<td colspan=\"" + colspan + "\" class=\"row_adder\"></td>").text("aggiungi"));
        $(this.table).find("tbody").append(row_adder);
    }
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
    table_func.init();
    menu.init();
});

})(jQuery);