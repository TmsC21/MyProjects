<?php
include "../Connection.php";
header("Content-type: application/json");
$conn = (new Connection())->connectDatabase();
$data = json_decode(file_get_contents('php://input'), true);
if(isset($data["meno"]) && isset($data["den"]) && isset($data["mesiac"])){
    $name = $data["meno"];
    $day = $data["den"];
    $month = $data["mesiac"];
    $value = "name";
    $country_id = 4;
    $strm = $conn->prepare("select id from days where day=$day and month=$month");
    $strm->execute();
    $day_id = $strm->fetchColumn();
    $strm = $conn->prepare("insert IGNORE into records(day_id,country_id,name,type) values (:day_id,:country_id,:value,:type)");
    $strm->bindParam(":day_id",$day_id,PDO::PARAM_INT);
    $strm->bindParam(":country_id",$country_id,PDO::PARAM_INT);
    $strm->bindParam(":value",$name);
    $strm->bindParam(":type",$value);
    $strm->execute();
    echo json_encode(["message"=>$name." bol pridany do databazy"]);
}

?>
