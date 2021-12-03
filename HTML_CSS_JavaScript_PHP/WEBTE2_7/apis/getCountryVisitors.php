<?php
require "../Connection.php";
header('Content-Type','application/json');
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
$state = $data["country"];
$strm = $conn->prepare("select * from visitors where state = :state");
$strm->bindParam(":state",$state);
$strm->execute();
$places = $strm->fetchAll();
echo json_encode($places);
