<?php
header("Content-Type: application/json");
$data = json_decode(file_get_contents('php://input'), true);
$file = fopen("input.txt","w+") or die("File not found");
$str = $data["data"]."-".$data["swtch"];
fwrite($file,$str);
fclose($file);
echo json_encode(["status"=>"success","msg"=> $str]);
