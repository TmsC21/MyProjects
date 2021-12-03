<?php
require "../Connection.php";
header('Content-Type','application/json');
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
$strm = $conn->prepare("SELECT DISTINCT(visitors.state),x.pocet FROM visitors 
                            left join (SELECT COUNT(*) as pocet,state from visitors GROUP BY state) x on x.state = visitors.state");
$strm->execute();
$places = $strm->fetchAll();
echo json_encode($places);