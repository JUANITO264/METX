<?php
// 1. Configuración de la conexión
$host = 'localhost';     // Servidor de la base de datos
$db   = 'colmena_db';   // Nombre de la base de datos
$user = 'tu_usuario';    // Usuario de MariaDB
$pass = 'tu_contraseña'; // Contraseña de MariaDB
$charset = 'utf8mb4';    // Codificación de caracteres

// 2. Creación del DSN (Data Source Name)
$dsn = "mysql:host=$host;dbname=$db;charset=$charset";

// 3. Opciones de configuración para PDO
$options = [
    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,    // Manejo de errores
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,         // Formato de resultados
    PDO::ATTR_EMULATE_PREPARES   => false,                    // Preparación de consultas
];

// 4. Establecer la conexión
try {
    $pdo = new PDO($dsn, $user, $pass, $options);
    // Si llegas aquí, la conexión fue exitosa
    
    // El resto del código que usa la conexión...

} catch (\PDOException $e) {
    // Si hay un error en la conexión, se captura aquí
    echo json_encode(['error' => $e->getMessage()]);
}
?>