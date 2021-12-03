<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <link rel="stylesheet" href="styleCreatePerson.css">
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script type="text/javascript" charset="utf8" src="https://cdn.datatables.net/1.10.24/js/jquery.dataTables.js"></script>

</head>
<body>
        <div id="cont">
            <h1>Create person</h1>
        <form method="post" action="CreatePersonn.php">
            <input type="hidden" name="id">
            <div class="form-group row">
                <div class="col-md-5">
                    <label for="name">Name<i>*</i></label>
                    <input type="text" name="name" id="name" required>
                </div>
                <div class="col-md-5">
                    <label for="surname">Surname<i>*</i></label>
                    <input type="text" name="surname" id="surname" required>
                </div>
            </div>
            <div class="row">
                <div class="col-md-5">
                    <div class="form-group">
                        <div class="row-md-4">
                            <label for="birth_day">Birth day<i>*</i></label>
                            <input type="date" name="birth_day" id="birth_day" required>
                        </div>
                        <div class="row-md-4">
                            <label for="birth_place">Birth place<i>*</i></label>
                            <input type="text" name="birth_place" id="birth_place" required>
                        </div>
                        <div class="row-md-4">
                            <label for="birth_country">Birth country<i>*</i></label>
                            <input type="text" name="birth_country" id="birth_country" required>
                        </div>
                    </div>
                </div>
                <div class="col-md-5">
                    <div class="form-group">
                        <div class="row-md-4">
                            <label for="death_day">Death day</label>
                            <input type="date" name="death_day" id="death_day" >
                        </div>
                        <div class="row-md-4">
                            <label for="death_place">Death place</label>
                            <input type="text" name="death_place" id="death_place" >
                        </div>
                        <div class="row-md-4">
                            <label for="death_country">Death country</label>
                            <input type="text" name="death_country" id="death_country" >
                        </div>
                    </div>
                </div>
            </div>
                <div class="form-group row">
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
                <div class="form-group row">
                    <div class="col">
                        <div class="row">
                            <div class="col-md-5">
                                <label for="discipline">Discipline<i>*</i></label>
                                <input type="text" name="discipline" id="discipline"" required>
                            </div>
                            <div class="col-md-5">
                                <label for="placing">Placing<i>*</i></label>
                                <input type="number" name="placing" id="placing" min="1" value="1" required>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-md-6">
                                <button class="btn btn-secondary" type="submit" style="width: 350px; height: 60px; margin-top: 5px; font-size: 30px">Submit</button>
                            </div>
                            <div class="col-md-6">
                                <button class="btn btn-secondary" type="button" style="height: 60px; margin-left: 2px; margin-top: 5px; font-size: 30px" onclick="location.href = 'http://wt34.fei.stuba.sk/zad2/index.php';">spat</button>
                            </div>
                        </div>
                    </div>
                </div>
        </form>
        </div>
    <script src="JavaScript.js"></script>
</body>
</html>

