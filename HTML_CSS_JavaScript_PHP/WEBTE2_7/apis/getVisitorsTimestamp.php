<?php
require "../Connection.php";
header('Content-Type','application/json');
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
$strm = $conn->prepare("select timestamp from visitors");
$strm->execute();
$places = $strm->fetchAll();
$response = [];
foreach ($places as $place){
    $timeDate = [];
    $timeDate = str_getcsv($place["timestamp"]," ");
    array_push($response,$timeDate[1]);
}
echo json_encode($response);
