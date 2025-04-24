<?php

if(isset($_GET["data"])) {
   $datar = $_GET["data"]; // get temperature value from HTTP GET

   $servername = "localhost";
   $username = "JUANCHO";
   $password = "12345";
   $database_name = "apiario1";
   $data=explode("_",$datar);
   // Create MySQL connection fom PHP to MySQL server
   $connection = new mysqli($servername, $username, $password, $database_name);
   // Check connection
   if ($connection->connect_error) {
      die("MySQL connection failed: " . $connection->connect_error);
   }

   $sql = "INSERT INTO colmena1 VALUES (NOW(),$data[0],$data[1],$data[2],
   $data[3],$data[4],$data[5],$data[6])";

   if ($connection->query($sql) === TRUE) {
      echo "Dato Añadido";
   } else {
      echo "Error: " . $sql . " => " . $connection->error;
   }

   $connection->close();
} else {
   echo "data is not set in the HTTP request";
}
?>
