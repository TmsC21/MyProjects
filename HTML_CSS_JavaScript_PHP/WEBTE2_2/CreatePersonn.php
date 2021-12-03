<?php
require_once "Classes/PersonController.php";
$personControler = new PersonController();
$person = new Person();
$person->setName($_POST["name"]);
$person->setSurname($_POST["surname"]);
$person->setBirthDay($_POST["birth_day"]);
$person->setBirthCountry($_POST["birth_country"]);
$person->setBirthPlace($_POST["birth_place"]);
$person->setDeathDay($_POST["death_day"]);
$person->setDeathCountry($_POST["death_country"]);
$person->setDeathPlace($_POST["death_place"]);

$id = $personControler->insertPerson($person);
if($id != -1){
    $person->setId($id);
    $personControler->setUmiestnenie($person,$_POST["placing"],$_POST["OlympicGame"],$_POST["discipline"]);
    header("Location: http://wt34.fei.stuba.sk/zad2/index.php", true, 301);
}else{
    header('Refresh: 1.5; http://wt34.fei.stuba.sk/zad2/createPerson.php');
    echo "V databaze sa nachadza tento sportovec";
}
?>
