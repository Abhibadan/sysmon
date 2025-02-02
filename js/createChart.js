function createChart(label,color,backgroundColor) {
    ctx = document.getElementById('chart-area').getContext('2d');
    return new Chart(ctx, {
        type: 'line',
        data: {
            labels: Array(60).fill(0),
            datasets: [{
                label: '',
                data: Array(60).fill(0),
                borderColor: color,
                backgroundColor: backgroundColor,
                borderWidth: 1.5,
                fill: true,
                radius: 0,
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            plugins: {
                legend: {
                    display: false,
                },
                title: {
                    display: true,
                    color: '#9b9b9b',
                    text: label
                },
                tooltip: {
                    enabled: true,
                    position: 'nearest',
                    callbacks: {
                        title : () => null,
                        label:(context) =>context.formattedValue
                    }
                }
            },
            scales: {
                x: {
                    ticks: {
                        display: false,
                        color: '#9b9b9b'
                    },
                    grid: {
                        display: true,
                        color: '#9b9b9b40',
                    },
                    beginAtZero: true
                },
                y: {
                    ticks: {
                        display: true,
                        color: '#9b9b9b', 
                        callback: function(value, index, values) {
                            if (index === 0 || index === values.length - 1) {
                              return (Math.round(value * 10) / 10);
                            }
                            return '';
                        }
                    },
                    grid: {
                        display: true,
                        color: '#9b9b9b40',
                    },
                    beginAtZero: true
                }
            }
        }
    });
}