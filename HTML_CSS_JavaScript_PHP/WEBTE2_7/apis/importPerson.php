<?php
require "../Connection.php";
$data = json_decode(file_get_contents('php://input'), true);
$conn = (new Connection())->connectDatabase();
$ip = $data["ip"];
$loc = $data["loc"];
$place = $data["place"];
$state = $data["state"];
$timestamp = $data["timestamp"];

$strm = $conn->prepare("insert IGNORE into visitors(GPS_loc,city,state,ip_address,timestamp ) values (:loc,:city,:country,:ip,:timestamp)");
$strm->bindParam(":loc",$loc);
$strm->bindParam(":city",$place);
$strm->bindParam(":country",$state);
$strm->bindParam(":ip",$ip);
$strm->bindParam(":timestamp",$timestamp);
$strm->execute();

?>