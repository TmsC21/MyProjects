<?php
require_once "Classes/PersonController.php";
$personControler = new PersonController();
$person = $personControler->getPerson($_GET["id"]);
function getFullName(&$person){
    echo "<h2>".$person->getName()." ".$person->getSurname()."</h2>";
}
function getInfo(&$person){
    echo "<div id='infoPerson'><p><strong>Narodenie: </strong>".$person->getBirthDay()."<br>".$person->getBirthPlace()." ".$person->getBirthCountry()."</p>
          <p><strong>Umrtie: </strong>".$person->getDeathDay()."<br>".$person->getDeathPlace()." ".$person->getDeathCountry()."</p></div>";
}
function getTableOG(&$person){
    echo "<h3>Olympijské hry</h3>";
    echo "<table ><thead><tr><th>Rok ziskania medaile</th><th>Miesto konania</th><th>Typ olympiady</th><th>Disciplina</th><th>Ziskane medaile</th><th></th></tr></thead><tbody>";
    foreach ($person->getPlacements() as $placement){
        if ($placement->getPlacing() == 1){
            $ocenenie = "Zlata";
        }
        else if($placement->getPlacing() == 2){
            $ocenenie = "Strieborna";
        }
        else if($placement->getPlacing() == 3){
            $ocenenie = "Bronzova";
        }
        else{
            $ocenenie = $placement->getPlacing()." miesto";
        }
        echo "<tr><td>".$placement->getYear()."</td><td>".$placement->getCity()." ".$placement->getCountry()."</td><td>".$placement->getType()."</td><td>".$placement->getDiscipline()."</td><td>".$ocenenie."</td></tr>";
    }
    echo "</tbody></table>";
}
?>

<html>
<head>
    <meta charset="UTF-8">
    <title>Document</title>
    <link rel="stylesheet" href="styleDisplayPerson.css">
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script type="text/javascript" charset="utf8" src="https://cdn.datatables.net/1.10.24/js/jquery.dataTables.js"></script>
</head>
<body>
    <div class="con">
        <img src="person.png" alt="person" height="300" width="300">
        <div class="info">
            <?php
                getFullName($person);
                getInfo($person);
            ?>
        </div>
        <div class="table">
            <?php
                getTableOG($person);
            ?>
        </div>
        <button class="btn btn-secondary" onclick="location.href = 'http://wt34.fei.stuba.sk/zad2/index.php';">spat</button>
    </div>

</body>
</html>
