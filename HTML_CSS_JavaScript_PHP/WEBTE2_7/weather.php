<!doctype html>
<html lang="`en`">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <meta http-equiv="Content-Security-Policy" content="upgrade-insecure-requests">
    <title>Document</title>
</head>
<body>
<a href="info.php">Info</a>
<a href="visits.php">Visits</a>
<div id="container">
    <p>Akceptujete spracovanie vasej IP?</p>
    <button type='button' id='ano'>ano</button>
    <button type='button' id='nie'>nie</button>
</div>
<div style="display: none" id="weather"></div>
<script src="script.js"></script>
<script>
    checkIP('<?php echo $_SERVER["REMOTE_ADDR"]?>')
    var ano = document.getElementById("ano")
    var nie = document.getElementById("nie")
    if(sessionStorage.getItem("idWeather")){
        document.getElementById('container').style.display = 'none';
        document.getElementById('weather').style.display = 'block';
        getWeather(JSON.parse(sessionStorage.getItem("idWeather"))["value"])
    }
    ano.onclick = function (){
        setWithExpiry("idWeather",'<?php echo $_SERVER["REMOTE_ADDR"]?>',300000)
        getWeather(JSON.parse(sessionStorage.getItem("idWeather"))["value"])
        document.getElementById('weather').style.display = 'block';
        document.getElementById('container').style.display = "none";
    }
    nie.onclick = function (){
        alert("Stranka sa vam nezobrazi")
    }
</script>
</body>
</html>
