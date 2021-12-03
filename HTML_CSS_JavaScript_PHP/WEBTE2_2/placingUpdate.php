<?php
require_once "Classes/PersonController.php";
$personControler = new PersonController();
$person = new Person();
echo $_POST["OlympicGame"];
$person = $personControler->getPerson($_POST["OlympicPlayers"]);
$personControler->setUmiestnenie($person,$_POST["placing"],$_POST["OlympicGame"],$_POST["discipline"]);
header("Location: http://wt34.fei.stuba.sk/zad2/index.php", true, 301);