<?php
header("Content-Type: application/json");
require "Connection.php";
require "User.php";
$data = json_decode(file_get_contents('php://input'), true);
$strData = str_getcsv($data["content"],"-");
$idLecture = $strData[0];
$name = $strData[1]." ".$strData[2];

$conn = (new Connection())->connectDatabase();
$strm = $conn->prepare("SELECT lectures.timestamp as lcTimestamp,user_actions.action,user_actions.timestamp from  user_actions JOIN lectures where user_actions.lecture_id = lectures.id and name = :name and lectures.id = :id");
$strm->bindParam(":name",$name);
$strm->bindParam(":id",$idLecture);
$strm->execute();
$lectures = $strm->fetchAll(PDO::FETCH_CLASS,"User");
$myobj=[];
foreach ($lectures as $lecture){
    $tmp = array("lectureTimestamp"=>$lecture->lcTimestamp,"name"=>$name , "action"=>$lecture->action,"personOnLecture"=>$lecture->timestamp);
    array_push($myobj,$tmp);
}
echo json_encode(["status"=>"success","msg"=> $myobj]);
