<?php
include "../Connection.php";
header("Content-type: application/json");
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
if(isset($data["type"]) && isset($data["country"])){
    $type = $data["type"];
    $country = $data["country"];
    $strm = $conn->prepare("SELECT records.name, days.day,days.month from records JOIN countries ON records.country_id = countries.id join days on records.day_id = days.id WHERE records.type = :type and records.country_id = :country");
    $strm->bindParam(":type",$type);
    $strm->bindParam(":country",$country,PDO::PARAM_INT);
    $strm->execute();
    $holiDayList = $strm->fetchAll();
    echo json_encode($holiDayList);
}
?>
