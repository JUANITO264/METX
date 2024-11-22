<?php
header('Content-Type: application/json');

// Configuración de la base de datos
$host = 'localhost';
$dbname = 'nombre_de_tu_base_de_datos';
$username = 'tu_usuario';
$password = 'tu_contraseña';

try {
    // Conexión a la base de datos
    $conn = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Consulta SQL para obtener los últimos 10 datos
    $sql = "SELECT fecha, temperatura_interna, temperatura_externa, humedad_interna, humedad_externa, peso, sonido_interno, sonido_externo 
            FROM datos_sensor 
            ORDER BY fecha DESC 
            LIMIT 10";
    $stmt = $conn->prepare($sql);
    $stmt->execute();

    // Devuelve los datos en formato JSON
    $result = $stmt->fetchAll(PDO::FETCH_ASSOC);
    echo json_encode($result);
} catch (PDOException $e) {
    echo json_encode(['error' => $e->getMessage()]);
}
?>
