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
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="style.css">
    <title>Document</title>
</head>
<body>
<div id="con" class="container">
    <button class="btn btn-secondary" id="refresh" type="button" onclick=reset()><i class="fas fa-sync-alt"></i></button>
    <p>
        Meniny dany den(vyplnit): Den, Mesiac, Stat <br>
        Meniny podla mena(vyplnit): Meno, Stat<br>
        Importnut meno(vyplnit): Meno, Den, Mesiac, Stat<br>
    </p>
    <form>
        <div class="form-group">
            <div class="row" style="margin: 10px auto">
                <label for="den" style="margin-right: 2px">Den:</label>
                <input id="den" type="number" value="1" min="1" max="30">
                <label for="mesiac" style="margin-right: 2px">Mesiac:</label>
                <input id="mesiac" type="number" value="1" min="1" max="12">
            </div>
            <div class="row" style="margin: 10px auto">
                <label for="meno">Meno:</label>
                <input id="meno" type="text">
            </div>
            <div class="row">
                <div class="col-md-7">
                    <div id="radioBoxList">
                        <input value="1" name="country" checked type="radio" /> Maďarsko <br />
                        <input value="2" name="country" type="radio" /> Poľsko <br />
                        <input value="3" name="country" type="radio" /> Rakúsko <br />
                        <input value="4" name="country" type="radio" /> Slovensko <br />
                        <input value="5" name="country" type="radio" /> Česká republika <br />
                    </div>
                </div>
                <div class="col-md-5">
                    <form >
                        <div class="from-group">
                            <div id="checkBoxListH">
                                <input value="1" name="countryH" checked type="radio" /> SKsviatky <br />
                                <input value="2" name="countryH" type="radio" /> CZsviatky <br />
                                <input value="3" name="countryH" type="radio" /> SKdni <br />
                            </div>
                        </div>
                    </form>
                </div>
            </div>
            <div class="row" id="buttons" style="margin-top: 10px">
                <button class="btn btn-secondary" type="button" onclick=nameDays()>Meniny</button>
                <button class="btn btn-secondary" style="margin-left: 5px" type="button" onclick=importName()>Import</button>
                <button class="btn btn-secondary" style="margin-left: 50px" type="button" onclick=holiDays()>Sviatky</button>
            </div>
        </div>
    </form>
</div>
<div id="con2">
    <div style="margin: auto; width: 30%" id="nameDays"></div>
    <div id="holiDays"></div>
</div>
<script src="script.js"></script>
</body>
</html>
