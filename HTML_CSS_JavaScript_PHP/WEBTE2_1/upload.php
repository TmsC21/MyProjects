<?php
header("Content-Type: application/json; charset=utf-8");
$response = array();
$filename = $_REQUEST["filename"];
$target_file = basename($_FILES["FileToUpload"]["name"]);
$uploadOk = 1;
$FileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
$target_file = basename($target_file , ".$FileType");

if($filename){
    $name = $filename;
}else{
    $name = $target_file;
}


// Check file size
if ($_FILES["FileToUpload"]["size"] > 500000) {
    $response = array("message" => "not");
    $uploadOk = 0;
}
// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    $response = array("message" => "not");
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["FileToUpload"]["tmp_name"], "files/".$name."_".time().".$FileType")) {
        $response = array("message" => "has been");
    } else {
        $response = array("message" => "not");
    }
}
echo json_encode($response);
