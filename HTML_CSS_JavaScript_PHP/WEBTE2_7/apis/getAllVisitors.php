<?php
require "../Connection.php";
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
$strm = $conn->prepare("select * from visitors");
$strm->execute();
$people = $strm->fetchAll();
echo json_encode($people);
