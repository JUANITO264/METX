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
        document.getElementById("tempInt").textContent = data.temperatura_interna;
        document.getElementById("tempExt").textContent = data.temperatura_externa;
        document.getElementById("humInt").textContent = data.humedad_interna;
        document.getElementById("humExt").textContent = data.humedad_externa;
        document.getElementById("weight").textContent = data.peso;
        document.getElementById("soundInt").textContent = data.sonido_interno;
        document.getElementById("soundExt").textContent = data.sonido_externo;

        // Actualiza las últimas mediciones
        const lastUpdate = new Date(data.fecha).toLocaleString();
        document.getElementById("lastUpdateTemp").textContent = lastUpdate;
        document.getElementById("lastUpdateHum").textContent = lastUpdate;
        document.getElementById("lastUpdateWeight").textContent = lastUpdate;
        document.getElementById("lastUpdateSound").textContent = lastUpdate;

    } catch (error) {
        console.error("Error al actualizar el dashboard:", error);
    }
}

// Función para inicializar las gráficas
async function initCharts() {
    try {
        const response = await fetch(apiEndpoint + "?historico=true");
        const data = await response.json();

        const labels = data.map(item => new Date(item.fecha).toLocaleTimeString());

        // Temperatura
        const tempDataInt = data.map(item => item.temperatura_interna);
        const tempDataExt = data.map(item => item.temperatura_externa);
        tempChart = new Chart(document.getElementById("tempInternaChart"), {
            type: "line",
            data: {
                labels: labels,
                datasets: [
                    { label: "Interna", data: tempDataInt, borderColor: "red", fill: false },
                    { label: "Externa", data: tempDataExt, borderColor: "orange", fill: false }
                ]
            }
        });

        // Humedad
        const humDataInt = data.map(item => item.humedad_interna);
        const humDataExt = data.map(item => item.humedad_externa);
        humChart = new Chart(document.getElementById("humExternaChart"), {
            type: "line",
            data: {
                labels: labels,
                datasets: [
                    { label: "Interna", data: humDataInt, borderColor: "blue", fill: false },
                    { label: "Externa", data: humDataExt, borderColor: "cyan", fill: false }
                ]
            }
        });

        // Peso
        const pesoData = data.map(item => item.peso);
        pesoChart = new Chart(document.getElementById("pesoChart"), {
            type: "line",
            data: {
                labels: labels,
                datasets: [{ label: "Peso", data: pesoData, borderColor: "green", fill: false }]
            }
        });

        // Sonido
        const soundDataInt = data.map(item => item.sonido_interno);
        const soundDataExt = data.map(item => item.sonido_externo);
        soundChart = new Chart(document.getElementById("soundInternoChart"), {
            type: "line",
            data: {
                labels: labels,
                datasets: [
                    { label: "Interno", data: soundDataInt, borderColor: "purple", fill: false },
                    { label: "Externo", data: soundDataExt, borderColor: "magenta", fill: false }
                ]
            }
        });

    } catch (error) {
        console.error("Error al inicializar las gráficas:", error);
    }
}

// Actualiza los dashboards y gráficas periódicamente
setInterval(updateDashboard, 60000); // Actualiza cada minuto
setInterval(initCharts, 60000); // Actualiza gráficas cada minuto

// Inicializa todo al cargar la página
document.addEventListener("DOMContentLoaded", () => {
    updateDashboard();
    initCharts();
});
