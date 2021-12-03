<?php
require "../Connection.php";
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
$ip = $data["ip"];
$strm = $conn->prepare("select * from visitors where ip_address = :ip");
$strm->bindParam(":ip",$ip);
$strm->execute();
$person = $strm->fetch();
echo json_encode($person);