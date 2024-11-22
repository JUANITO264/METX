<?php
// 1. Configuración de la conexión
$host = 'localhost';     // Servidor de la base de datos
$db   = 'JUANCHOO';   // Nombre de la base de datos
$user = 'root';    // Usuario de MariaDB
$pass = 'root'; // Contraseña de MariaDB

// 2. Conexión a la base de datos
$conexion = mysqli_connect($host, $user, $pass, $db);

// 3. Verificar la conexión
if (!$conexion) {
    die("La conexión falló: " . mysqli_connect_error());
}
echo "Conexión exitosa";

?>