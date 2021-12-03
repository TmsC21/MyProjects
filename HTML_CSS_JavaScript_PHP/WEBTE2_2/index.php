<?php
require_once "Classes/PersonController.php";
$personConstroller = new PersonController();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <link rel="stylesheet" type="text/css" href="https://cdn.datatables.net/1.10.24/css/jquery.dataTables.css">
    <link rel="stylesheet" href="style.css">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script type="text/javascript" charset="utf8" src="https://cdn.datatables.net/1.10.24/js/jquery.dataTables.js"></script>
    <script src="JavaScript.js"></script>
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>

</head>
<body>
    <div id="container">
        <div id="firstTable">
            <table id="table_id" class="display">
                <?php
                echo $personConstroller->getPeople();
                ?>
            </table>
        </div>
        <div id="secondTableContainer">
            <table id="secondTable">
                <?php
                echo $personConstroller->getTopPeople(); ?>
            </table>
            <div id="buttons">
                <button id="firstButton" class="btn btn-secondary" onclick="location.href = 'createPerson.php';">Pridat sportovca</button>
                <button id="secondButton" class="btn btn-secondary" onclick="location.href = 'createPlacing.php';">Pridat umiestnenie</button>
            </div>
        </div>
    </div>
</body>
</html>

