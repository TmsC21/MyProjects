<?php
include "Connection.php";
$xml = simplexml_load_file("meniny.xml");
$countries = [
    "SK" => ["title"=>"Slovensko"],
    "CZ" => ["title"=>"Česká republika"],
    "AT" => ["title"=>"Rakúsko"],
    "HU" => ["title"=>"Maďarsko"],
    "PL" => ["title"=>"Poľsko"],
];
$conn = (new Connection())->connectDatabase();
$day = "";
$month = "";
$strmDays = $conn->prepare("insert IGNORE into days (day,month) values(:day,:month)");
$strmDays->bindParam(":day",$day);
$strmDays->bindParam(":month",$month);

$code = "";
$title = "";
$strmCountries = $conn->prepare("insert IGNORE into countries(code,title) values (:code,:title)");
$strmCountries->bindParam(":code",$code);
$strmCountries->bindParam(":title",$title);


$day_id = "";
$country_id = "";
$value = "";
$type = "";
$strmRecords = $conn->prepare("insert IGNORE into records(day_id,country_id,name,type) values (:day_id,:country_id,:value,:type)");
$strmRecords->bindParam(":day_id",$day_id,PDO::PARAM_INT);
$strmRecords->bindParam(":country_id",$country_id,PDO::PARAM_INT);
$strmRecords->bindParam(":value",$value);
$strmRecords->bindParam(":type",$type);

foreach ($xml->children() as $row){
    $day = substr($row->den,2,2);
    $month = substr($row->den,0,2);
    $strmDays->execute();

    $d = $conn->prepare("select id from days where day=$day and month=$month");
    $d->execute();
    $day_id = $d->fetchColumn();
    foreach (array_keys(((array)$row)) as $item){
        if(array_key_exists($item,$countries)){
            if(!isset($countries[$item]["id"])){
                $code = $item;
                $title = $countries[$item]["title"];
                $strmCountries->execute();

                $c = $conn->prepare("select id from countries where code='$code'");
                $c->execute();
                $country_id = $c->fetchColumn();
                $countries[$item]["id"] = $country_id;
            }

            $type = "name";
            $country_id= $countries[$item]["id"] ;
            foreach (explode(",",$row->$item) as $name){
                if($name == " " || $name=="" || !$name || $name == "-"){
                    continue;
                }else{
                    $value = trim($name);
                    $strmRecords->execute();
                }
            }
        }
    }
    $country_id= $countries["SK"]["id"];
    if($row->SKd){
        foreach (explode(",",$row->SKd) as $name){
            if($name == " " || $name=="" || !$name || $name == "-"){
                continue;
            }else{
                $value = trim($name);
                $strmRecords->execute();
            }
        }
    }
    if($row->SKdni){
        $type = "pday";
        $value = $row->SKdni;
        $country_id = 4;
        $strmRecords->execute();
    }
    if($row->SKsviatky){
        $type = "holiday";
        $value = $row->SKsviatky;
        $country_id = 4;
        $strmRecords->execute();
    }if($row->CZsviatky){
        $type = "holiday";
        $value = $row->CZsviatky;
        $country_id = 5;
        $strmRecords->execute();
    }
}