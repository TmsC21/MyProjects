<?php
header("Content-Type: text/event-stream");
header("Cache-Control: no-cache");

$index = 0;
while (true){
    $file = fopen("input.txt","r+") or die("File not found");
    $str = str_getcsv(fgets($file),"-");
    $input = intval($str[0]);
    $swtch = $str[1];
    fclose($file);
    if($swtch == 1){
        $msg = json_encode(["sin2"=>pow(sin($index*$input),2)]);
    }else if($swtch == 2){
        $msg = json_encode(["cos2"=>pow(cos($index*$input),2)]);
    }else if($swtch == 3){
        $msg = json_encode(["sincos"=> sin($index*$input)*cos($index*$input)]);
    }else{
        $msg = json_encode(["sincos"=> sin($index*$input)*cos($index*$input), "sin2"=>pow(sin($index*$input),2),"cos2"=>pow(cos($index*$input),2)]);
    }
    sendSse(++$index,$msg);
    sleep(1);
}
function sendSse($id , $msg){
    echo "id: $id\n";
    echo "event: evt\n";
    echo "data: $msg\n\n";
    ob_flush();
    flush();
}
