<?php
?>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="style.css">
    <title>Document</title>
</head>
<body>
<div class="container">
    <div id="result"></div>
    <form>
        <div class="form-group row">
            <div class="col-md-4">
                <input id="input" type="number" name="num" value="1" min="1" onchange=changeData() style="width: 150px; height:80px;background-color: rgba(53,53,53,0.1); ">
            </div>
            <div class="col-md-4">
                <button class="btn btn-secondary" type="button" style="width: 170px; height:80px" onclick=allY()>All</button>
            </div>
        </div>
        <div class="form-group">
            <button class="btn btn-secondary" type="button" onclick=y1()>sin2</button>
            <button class="btn btn-secondary" type="button" onclick=y2()>cos2</button>
            <button class="btn btn-secondary" type="button" onclick=y3()>sin*cos</button>
        </div>
    </form>
</div>

<script>
    var swtch = 0;
    changeData();
    var sourse = new EventSource("sse.php");
    sourse.addEventListener("evt",(event)=>{
        var data = JSON.parse(event.data);
        console.log(event)
        if(swtch === 0){
            document.querySelector("#result").innerHTML = "[sin*cos: "+data.sincos +"]<br>[sin2: "+data.sin2 +"]<br>[cos2: "+data.cos2 +"]<br>";
        }
        if(swtch === 1){
            document.querySelector("#result").innerHTML = "[sin2: "+data.sin2 +"]<br>";
        }
        if(swtch === 2){
            document.querySelector("#result").innerHTML = "[cos2: "+data.cos2 +"]<br>";
        }
        if(swtch === 3){
            document.querySelector("#result").innerHTML = "[sin*cos: "+data.sincos +"]<br>";
        }
    })
    function changeData(){
        fetch("writeTxt.php",{
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body:JSON.stringify({data:document.getElementById("input").value,swtch:swtch})
        }).then((response)=>response.json())
            .then((data)=>{
                console.log(data)
            })
    }

    function y1(){
        swtch = 1;
        changeData();
    }
    function y2(){
        swtch = 2;
        changeData();
    }
    function y3(){
        swtch = 3;
        changeData();
    }
    function allY(){
        swtch = 0;
        changeData();
    }
</script>
</body>
</html>
