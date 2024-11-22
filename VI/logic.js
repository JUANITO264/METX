let chart;

document.addEventListener('DOMContentLoaded', function() {
    initChart();
    updateData();
    
    // Actualizar datos cada 10 segundos
    setInterval(updateData, 10000);
});

function initChart() {
    const ctx = document.getElementById('sensorChart').getContext('2d');
    chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [
                {
                    label: 'Temperatura Interna (°C)',
                    borderColor: '#FF6B6B',
                    data: []
                },
                {
                    label: 'Temperatura Externa (°C)',
                    borderColor: '#4ECDC4',
                    data: []
                },
                {
                    label: 'Humedad Interna (%)',
                    borderColor: '#45B7D1',
                    data: []
                },
                {
                    label: 'Humedad Externa (%)',
                    borderColor: '#96CEB4',
                    data: []
                },
                {
                    label: 'Peso (kg)',
                    borderColor: '#FFBE0B',
                    data: []
                }
            ]
        },
        options: {
            responsive: true,
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'hour'
                    }
                },
                y: {
                    beginAtZero: true
                }
            }
        }
    });
}

function updateData() {
    const startDate = document.getElementById('startDate').value;
    const endDate = document.getElementById('endDate').value;

    fetch(`getData.php?start=${startDate}&end=${endDate}`)
        .then(response => response.json())
        .then(data => {
            updateDashboard(data[data.length - 1]);
            updateChart(data);
        })
        .catch(error => console.error('Error:', error));
}

function updateDashboard(latestData) {
    document.getElementById('tempInt').textContent = latestData.temp_interna.toFixed(1);
    document.getElementById('tempExt').textContent = latestData.temp_externa.toFixed(1);
    document.getElementById('humInt').textContent = latestData.hum_interna.toFixed(1);
    document.getElementById('humExt').textContent = latestData.hum_externa.toFixed(1);
    document.getElementById('weight').textContent = latestData.peso.toFixed(2);
    document.getElementById('soundInt').textContent = latestData.sonido_interno.toFixed(1);
    document.getElementById('soundExt').textContent = latestData.sonido_externo.toFixed(1);
}

function updateChart(data) {
    chart.data.labels = data.map(row => row.fecha);
    chart.data.datasets[0].data = data.map(row => row.temp_interna);
    chart.data.datasets[1].data = data.map(row => row.temp_externa);
    chart.data.datasets[2].data = data.map(row => row.hum_interna);
    chart.data.datasets[3].data = data.map(row => row.hum_externa);
    chart.data.datasets[4].data = data.map(row => row.peso);
    chart.update();
}