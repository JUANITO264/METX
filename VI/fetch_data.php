<?php
$host = 'localhost';
$dbname = 'apiario1';
$username = 'JUANCHO';
$password = '12345';

try {
    $conn = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if (isset($_GET['historico'])) {
        // Devuelve las últimas 10 mediciones
        $stmt = $conn->prepare("SELECT * FROM colmena1 ORDER BY Fecha DESC LIMIT 10");
        $stmt->execute();
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
    } else {
        // Devuelve la última medición
        $stmt = $conn->prepare("SELECT * FROM colmena1 ORDER BY Fecha DESC LIMIT 1");
        $stmt->execute();
        echo json_encode($stmt->fetch(PDO::FETCH_ASSOC));
    }

} catch (PDOException $e) {
    echo json_encode(['error' => $e->getMessage()]);
}
?>