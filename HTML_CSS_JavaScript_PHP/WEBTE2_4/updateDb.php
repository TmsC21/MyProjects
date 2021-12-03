<?php
header("Content-Type: application/json");
require_once "Connection.php";
$crl = curl_init();
curl_setopt($crl,CURLOPT_URL,"https://api.github.com/repos/apps4webte/curldata2021/contents");
curl_setopt($crl,CURLOPT_RETURNTRANSFER,1);
$header = ["User-Agent: apps4webte"];
curl_setopt($crl,CURLOPT_HTTPHEADER,$header);
$lectures = curl_exec($crl);
curl_close($crl);
$lecturesLines = explode("},",$lectures);
$lecturesLines = str_replace("[","",$lecturesLines);

$conn = (new Connection())->connectDatabase();
$conn2 = (new Connection())->connectDatabase();
$strm = $conn->prepare("select count(id) as count from lectures");
$strm->execute();
$lecturesCount = $strm->fetch();
$insertColums =  abs(sizeof($lecturesLines)-$lecturesCount["count"]);
if(sizeof($lecturesLines)!=$lecturesCount["count"]){
    foreach ($lecturesLines as $lecturesline){
        $timestamp = substr($lecturesline,9,8);
        $year = substr($timestamp,0,4);
        $month = substr($timestamp,4,2);
        $day = substr($timestamp,6,2);
        $urlLecture = $year."".$month."".$day;
        $timestamp = $year."-".$month."-".$day." 00:00:00";
        $tmp_strm = $conn->prepare("Select lectures.timestamp from lectures where lectures.timestamp = :tms");
        $tmp_strm->bindParam(":tms",$timestamp);
        $tmp_strm->execute();
        $tmp_tms = $tmp_strm->fetch();
        if (!$tmp_tms){
            $curl = curl_init();
            $url = "https://raw.githubusercontent.com/apps4webte/curldata2021/main/".$urlLecture."_AttendanceList_WebTe2.csv";
            curl_setopt($curl,CURLOPT_URL,$url);
            curl_setopt($curl,CURLOPT_RETURNTRANSFER,1);
            $out = curl_exec($curl);
            $out = mb_convert_encoding($out,"UTF-8","UTF-16LE");
            curl_close($curl);
            $lines = explode("\n", $out);
            $scv=[];
            $strm = $conn2->prepare("insert into lectures(timestamp) values (:timestamp)");
            $strm->bindParam(":timestamp",$timestamp);
            $strm->execute();
            $id = $conn2->lastInsertId();
            $strm = $conn->prepare("INSERT INTO user_actions (lecture_id,name,action,timestamp) VALUES (:id,:name, :action, :timestamp);");
            $strm->bindParam(":name",$username);
            $strm->bindParam(":action",$action);
            $strm->bindParam(":timestamp",$userTimestamp);
            $strm->bindParam(":id",$id,PDO::PARAM_INT);
            foreach ($lines as $index=>$line){
                $scv = str_getcsv($line,"\t");
                if($index > 0 && ($scv[0])){
                    $username = $scv[0];
                    $action = $scv[1];
                    if(strpos($scv[2]," AM")){
                        $time = str_replace(" AM","",$scv[2]);
                        $userTimestamp = date("Y-m-d H:i:s",date_create_from_format("m/d/Y, H:i:s",$time)->getTimestamp());
                    }else{
                        $userTimestamp = date("Y-m-d H:i:s",date_create_from_format("d/m/Y, H:i:s",$scv[2])->getTimestamp());

                    }
                    $strm->execute();
                }
            }
        }
    }

    echo json_encode(["status"=>"success","msg"=> "Table has been updated instert: ".$insertColums." lectures"]);
}else{
    echo json_encode(["status"=>"success","msg"=> "Table is already updated"]);
}

?>
