<?php
require_once "Classes/PersonController.php";
$personControler = new PersonController();
$stmt = $personControler->conn->prepare("delete from osoby where osoby.id =:ID");
$id = $_GET["id"];
$stmt->bindParam(":ID",$id, PDO::PARAM_INT);
$stmt->execute();
header("Location: http://wt34.fei.stuba.sk/zad2/index.php", true, 301);

