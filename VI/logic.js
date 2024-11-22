// URLs de los endpoints PHP
const apiEndpoint = "fetch_data.php";

// Variables para gráficas
let tempChart, humChart, pesoChart, soundChart;

// Función para actualizar dashboards con los últimos datos
async function updateDashboard() {
    try {
        const response = await fetch(apiEndpoint);
        const data = await response.json();

        // Actualiza datos en los dashboards
        document.getElementById("Tempin").textContent = data.Tempin;
        document.getElementById("Tempout").textContent = data.Tempout;
        document.getElementById("Humin").textContent = data.Humin;
        document.getElementById("Humout").textContent = data.Humout;
        document.getElementById("Peso").textContent = data.Peso;
        document.getElementById("Sonin").textContent = data.Sonin;
        document.getElementById("Sonout").textContent = data.Sonout;

        // Actualiza las últimas mediciones
        const lastUpdate = new Date(data.fecha).toLocaleString();
        document.getElementById("lastUpdateTemp").textContent = data.Fecha;
        document.getElementById("lastUpdateHum").textContent = data.Fecha;
        document.getElementById("lastUpdateWeight").textContent = data.Fecha;
        document.getElementById("lastUpdateSound").textContent = data.Fecha;

    } catch (error) {
        console.error("Error al actualizar el dashboard:", error);
    }
}

// Función para inicializar las gráficas
function initializeCharts() {
    const tempCtx = document.getElementById('tempInternaChart').getContext('2d');
    tempChart = new Chart(tempCtx, {
        type: 'line',
        data: {
            labels: [], // Etiquetas de tiempo
            datasets: [{
                label: 'Temperatura Interna',
                data: [],
                borderColor: 'rgba(255, 99, 132, 1)',
                borderWidth: 1,
                fill: false
            }, {
                label: 'Temperatura Externa',
                data: [],
                borderColor: 'rgba(54, 162, 235, 1)',
                borderWidth: 1,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'minute'
                    }
                },
                y: {
                    beginAtZero: true
                }
            }
        }
    });

    const humCtx = document.getElementById('humExternaChart').getContext('2d');
    humChart = new Chart(humCtx, {
        type: 'line',
        data: {
            labels: [], // Etiquetas de tiempo
            datasets: [{
                label: 'Humedad Interna',
                data: [],
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 1,
                fill: false
            }, {
                label: 'Humedad Externa',
                data: [],
                borderColor: 'rgba(153, 102, 255, 1)',
                borderWidth: 1,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'minute'
                    }
                },
                y: {
                    beginAtZero: true
                }
            }
        }
    });

    const pesoCtx = document.getElementById('pesoChart').getContext('2d');
    pesoChart = new Chart(pesoCtx, {
        type: 'line',
        data: {
            labels: [], // Etiquetas de tiempo
            datasets: [{
                label: 'Peso',
                data: [],
                borderColor: 'rgba(255, 206, 86, 1)',
                borderWidth: 1,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'minute'
                    }
                },
                y: {
                    beginAtZero: true
                }
            }
        }
    });

    const soundCtx = document.getElementById('soundInternoChart').getContext('2d');
    soundChart = new Chart(soundCtx, {
        type: 'line',
        data: {
            labels: [], // Etiquetas de tiempo
            datasets: [{
                label: 'Sonido Interno',
                data: [],
                borderColor: 'rgba(255, 159, 64, 1)',
                borderWidth: 1,
                fill: false
            }, {
                label: 'Sonido Externo',
                data: [],
                borderColor: 'rgba(255, 99, 132, 1)',
                borderWidth: 1,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'minute'
                    }
                },
                y: {
                    beginAtZero: true
                }
            }
        }
    });
}
// Función para actualizar las gráficas con los datos históricos
async function updateCharts() {
    try {
        const response = await fetch(apiEndpoint + "?historico=true");
        const data = await response.json();

        // Limpia los datos previos para evitar duplicados
        tempChart.data.labels = [];
        tempChart.data.datasets[0].data = [];
        tempChart.data.datasets[1].data = [];
        
        humChart.data.labels = [];
        humChart.data.datasets[0].data = [];
        humChart.data.datasets[1].data = [];
        
        pesoChart.data.labels = [];
        pesoChart.data.datasets[0].data = [];
        
        soundChart.data.labels = [];
        soundChart.data.datasets[0].data = [];
        soundChart.data.datasets[1].data = [];

        // Procesa los datos
        data.forEach(item => {
            const time = new Date(item.Fecha).toLocaleTimeString();

            // Actualizar gráfica de temperatura
            tempChart.data.labels.push(time);
            tempChart.data.datasets[0].data.push(item.Tempin);
            tempChart.data.datasets[1].data.push(item.Tempout);

            // Actualizar gráfica de humedad
            humChart.data.labels.push(time);
            humChart.data.datasets[0].data.push(item.Humin);
            humChart.data.datasets[1].data.push(item.Humout);

            // Actualizar gráfica de peso
            pesoChart.data.labels.push(time);
            pesoChart.data.datasets[0].data.push(item.Peso);

            // Actualizar gráfica de sonido
            soundChart.data.labels.push(time);
            soundChart.data.datasets[0].data.push(item.Sonin);
            soundChart.data.datasets[1].data.push(item.Sonout);
        });

        // Actualiza las gráficas
        tempChart.update();
        humChart.update();
        pesoChart.update();
        soundChart.update();

    } catch (error) {
        console.error("Error al actualizar las gráficas:", error);
    }
}


// Actualiza los dashboards y gráficas periódicamente
setInterval(updateDashboard, 60000); // Actualiza cada minuto
setInterval(initializeCharts, 60000); // Actualiza gráficas cada minuto
setInterval(updateCharts, 60000); // Actualiza gráficas cada minuto
// Inicializa todo al cargar la página
document.addEventListener("DOMContentLoaded", () => {
    updateDashboard();
    initializeCharts();
    updateCharts();
});
