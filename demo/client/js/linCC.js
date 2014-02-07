(function($){

var linCC_highchart = {

    options: {
        chart: {
            renderTo: 'chart'
        },
        title: {
            text: 'Graphic',
            x: -20 //center
        },
        subtitle: {
            text: 'di LinCC',
            x: -20
        },
        xAxis: {
            categories: ['valore 1', 'valore 2', 'valore 3',
                'valore 4', 'valore 5', 'valore 6']
        },
        yAxis: {
            title: {
                text: 'Temperatura (°C)'
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: '°C'
        },
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle',
            borderWidth: 0
        },
        series: [{
            name: 'linea 1',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 20.4]
        }]
    },

    init: function() {
        this.chart = new Highcharts.Chart(this.options);
    },
};

// start highchart immediatly
linCC_highchart.init();

$(document).ready(function(){

    // handler input
    $('#input-section').on('change', 'input[type=text]', function(){
        var input_num = $(this).data('val');
        var input_val = $(this).val();

        // sanity check
        if (!$.isNumeric(input_val)) {
            $(this).parent().addClass('has-error');
            return false;
        }
        else {
            $(this).parent().removeClass('has-error');
        }

        // actual data is an object, new_data has to be an array of coords
        // (array-like [x,y])
        var actual_data = linCC_highchart.chart.series[0].data;
        var new_data = [];

        for (var i = 0; i < actual_data.length; i++) {
            // adapt datas in array-like coords
            new_data.push([actual_data[i].x, actual_data[i].y])
        }

        // modify changed value
        new_data[input_num-1][1] = parseInt(input_val);

        // set new data
        linCC_highchart.chart.series[0].setData(new_data);
    });
});

})(jQuery);