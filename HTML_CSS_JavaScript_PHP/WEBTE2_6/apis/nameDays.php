<?php
include "../Connection.php";
header("Content-type: application/json");
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
if(isset($data["id"]) && isset($data["den"]) && isset($data["mesiac"]) && !isset($data["meno"])){
    $id = $data["id"];
    $day = $data["den"];
    $month = $data["mesiac"];
    $strmID = $conn->prepare("select name from records JOIN days WHERE records.day_id = days.id and records.country_id = :id and days.day=:day and days.month = :month and records.type = 'name'");
    $strmID->bindParam(":day",$day,PDO::PARAM_INT);
    $strmID->bindParam(":month",$month,PDO::PARAM_INT);
    $strmID->bindParam(":id",$id,PDO::PARAM_INT);
    $strmID->execute();
    $nameList = $strmID->fetchAll();
    echo json_encode($nameList);
}
if(isset($data["id"]) && isset($data["meno"])){
    $id = $data["id"];
    $meno = $data["meno"];
    $strmID = $conn->prepare("SELECT days.day, days.month from records JOIN countries ON records.country_id = countries.id join days on records.day_id = days.id WHERE records.name = :meno and countries.id = :id");
    $strmID->bindParam(":id",$id,PDO::PARAM_INT);
    $strmID->bindParam(":meno",$meno);
    $strmID->execute();
    $nameList = $strmID->fetchAll();
    echo json_encode($nameList);
}
?>

