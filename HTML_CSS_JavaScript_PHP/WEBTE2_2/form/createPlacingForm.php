<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <link rel="stylesheet" href="styleCreatePlacing.css">
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script type="text/javascript" charset="utf8" src="https://cdn.datatables.net/1.10.24/js/jquery.dataTables.js"></script>
</head>
<body>
<div class="con">
    <h1>Create placing</h1>
    <form method="post" action="placingUpdate.php">
        <input type="hidden" name="id">

        <div class="form-group row">
            <div class="col">
                <label for="disMenu">Olympic game<i>*</i></label>
                <div id="disMenu">
                    <select name="OlympicGame" size="5" id="oh" required>
                        <?php
                        include "Classes/ListBarOH.php";
                        $list = new ListBarOH();
                        $list->getOptions();
                        ?>
                    </select>
                </div>
            </div>
            <div class="col">
                <label for="disMenu2">Olympic players<i>*</i></label>
                <div id="disMenu2">
                    <select name="OlympicPlayers" size="5" id="oh" required>
                        <?php
                        include "Classes/OlympicPlayers.php";
                        $list = new OlympicPlayers();
                        $list->getOptions();
                        ?>
                    </select>
                </div>
            </div>
        </div>
        <div class="form-group row">
            <div class="col-md-5">
                <label for="discipline">Discipline<i>*</i></label>
                <input type="text" name="discipline" id="discipline" required>
            </div>
            <div class="col-md-5">
                <label for="placing">Placing<i>*</i></label>
                <input type="number" name="placing" id="placing" min="1" value="1" required>
            </div>
        </div>
        <div class="form-group row">
            <div class="col-md-5">
                <button class="btn btn-secondary" type="submit" style="width: 350px; height: 60px; margin-top: 5px; font-size: 30px">Submit</button>
            </div>
            <div class="col-md-5">
                <button class="btn btn-secondary" style="height: 60px; margin-left: 2px; margin-top: 5px; font-size: 30px" onclick="location.href = 'http://wt34.fei.stuba.sk/zad2/index.php';">spat</button>
            </div>
        </div>
    </form>
</div>
</body>
</html>
