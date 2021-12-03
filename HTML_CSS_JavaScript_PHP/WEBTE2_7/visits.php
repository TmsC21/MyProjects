<!doctype html>
<html lang="`en`">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <meta http-equiv="Content-Security-Policy" content="upgrade-insecure-requests">
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.7.1/dist/leaflet.css"
          integrity="sha512-xodZBNTC5n17Xt2atTPuE1HxjVMSvLVW9ocqUKLsCC5CXdbqCmblAshOMAS6/keqq/sMZMZ19scR4PsZChSR7A=="
          crossorigin=""/>
    <script src="https://unpkg.com/leaflet@1.7.1/dist/leaflet.js"
            integrity="sha512-XQoYMqMTK8LvdxXYG3nZ448hOEQiglfqkJs1NOQV44cWnUrBc8PkAOcXy20w0vlaXaVUearIOBhiXZ5V3ynxwA=="
            crossorigin=""></script>

    <title>Document</title>
</head>
<body>
<a href="info.php">Info</a>
<a href="weather.php">Weather</a>
<div id="container">
    <p>Akceptujete spracovanie vasej IP?</p>
    <button type='button' id='ano'>ano</button>
    <button type='button' id='nie'>nie</button>
</div>
<div style="display: none" id="visits"></div>
<div id="timestamp"></div>
<div id="visitsFromCountry"></div>
<div style="height: 300px; width: 700px" id="mapid"></div>
<script src="script.js"></script>
<script>
    checkIP('<?php echo $_SERVER["REMOTE_ADDR"]?>')
    var ano = document.getElementById("ano")
    var nie = document.getElementById("nie")
    if(sessionStorage.getItem("idVisits")){
        document.getElementById('container').style.display = 'none';
        document.getElementById('visits').style.display = 'block';
        getVisits();
        getTimestamp()
        settingMap();
    }
    ano.onclick = function (){
        setWithExpiry("idVisits",'<?php echo $_SERVER["REMOTE_ADDR"]?>',300000)
        getVisits();
        getTimestamp()
        settingMap();
        document.getElementById('visits').style.display = 'block';
        document.getElementById('container').style.display = "none";
    }
    nie.onclick = function (){
        alert("Stranka sa vam nezobrazi")
    }
</script>
</body>
</html>

