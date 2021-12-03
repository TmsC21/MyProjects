<?php
require_once "Classes/PersonController.php";
$personControler = new PersonController();
if(isset($_POST["name"])) {
    if (isset($_POST["id"]) && $_POST["id"]) {
        $person = $personControler->getPerson($_POST["id"]);
        $person->setName($_POST["name"]);
        $person->setSurname($_POST["surname"]);
        foreach ($person->getPlacements() as $places){
            if($places->getId($_POST["rGroup"]) == $_POST["rGroup"]){
                $places->setPlacing($_POST["placing"]);
            }
        }
        $personControler->updatePerson($person,$_POST["rGroup"],$_POST["placing"]);
        $person = $personControler->getPerson($_POST["id"]);
    } else {
        $person = new Person();
        $person->setName($_POST["name"]);
        $person->setSurname($_POST["surname"]);
        $id = $personControler->insertPerson($person);
        if($id != -1){
            $person->setId($id);
            $personControler->setUmiestnenie($person,$_POST["placing"],$_POST["OlympicGame"],$_POST["discipline"]);
        }else{
            echo "V databaze sa nachadza tento sportovec";
        }
    }
}
if(isset($_GET["id"])){
    $person = $personControler->getPerson($_GET["id"]);
}
?>
<html>
<head>
    <meta charset="UTF-8">
    <title>Document</title>
    <link rel="stylesheet" href="styleEditPerson.css">
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script type="text/javascript" charset="utf8" src="https://cdn.datatables.net/1.10.24/js/jquery.dataTables.js"></script>
</head>
<body>
    <?php
        include "form/personForm.php";
    ?>

</body>
</html>

