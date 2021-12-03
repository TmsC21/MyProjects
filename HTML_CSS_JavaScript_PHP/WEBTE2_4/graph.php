<?php
header("Content-Type: application/json");
require "Connection.php";
require "User.php";

$conn = (new Connection())->connectDatabase();
$strm = $conn->prepare("SELECT * from lectures");
$strm2 = $conn->prepare("SELECT count(user_actions.id) as countPeople from user_actions JOIN lectures where user_actions.lecture_id = lectures.id and lectures.id = :id");
$strm->execute();
$lectures = $strm->fetchALL();
$myobj=[];
foreach ($lectures as $lecture){
    $strm2->bindParam(":id",$lecture["id"]);
    $strm2->execute();
    $tmp_count= $strm2->fetch();
    $count = $tmp_count["countPeople"];
    $timestamp = str_replace(" 00:00:00","",$lecture["timestamp"]);
    $tmp = ["count"=>$count,"timestamp"=>$timestamp];
    array_push($myobj,$tmp);
}
echo json_encode(["status"=>"success","msg"=> $myobj]);