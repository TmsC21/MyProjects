<?php
header("Content-Type: application/json; charset=utf-8");
$decoded = json_decode(file_get_contents("php://input"),true)["path"];
$dir = scandir($decoded);
$response = array();
$x = 0;
array_push($response,array("path" => $decoded));
foreach($dir as $subor){
    if($x == 0 || $x == 1){
        $x++;
        continue;
    }else{
        $realfile = $decoded.$subor;
        if(!pathinfo($subor,PATHINFO_EXTENSION)){
            $file = array(
                "id" => $x-2,
                "fileName" => $subor,
                "fileType" => "directory",
                "fileSize" => 0,
                "fileDate" => 0
            );
            $x++;
            array_push($response,$file);
        }else{
            $FileType = strtolower(pathinfo($subor,PATHINFO_EXTENSION));
            $fileName = basename($subor,".$FileType");
            $fileNames= explode("_",$fileName);
            $file = array(
                "id" => $x-2,
                "fileType" => $FileType,
                "fileName" => $fileNames[0],
                "fileSize" => filesize($realfile),
                "fileDate" =>date("H:i:s d/m/Y",$fileNames[1]),
            );
            $x++;
            array_push($response,$file);
        }
    }
}
echo json_encode($response);
