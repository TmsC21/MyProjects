<div class="con">
    <h1>Edit person</h1>
    <form method="post" action="editPerson.php?<?php ?>" >
        <div class="table">
            <?php
            require_once "Classes/PersonController.php";
            $prsn = null;
            isset($person) ? $prsn = $person : null;
            if($prsn){
                echo "<table ><thead><tr><th>Meno priezvisko</th><th>Rok ziskania medaile</th><th>Miesto konania</th><th>Typ olympiady</th><th>Disciplina</th><th>Umiestnenie</th><th></th></tr></thead><tbody>";
                $x = 0;
                foreach ($prsn->getPlacements() as $placement){
                    if($x==0){
                        echo "<tr><td>".$prsn->getName()." ".$prsn->getSurname()."</td><td>".$placement->getYear()."</td><td>".$placement->getCity()." ".$placement->getCountry()."</td><td>".$placement->getType()."</td><td>".$placement->getDiscipline()."</td><td>".$placement->getPlacing()."</td>
                    <td><input type='radio' name='rGroup' value=".$placement->getId()." id='r".$x."' checked='checked' /></td></tr>";
                    }else{
                        echo "<tr><td>".$prsn->getName()." ".$prsn->getSurname()."</td><td>".$placement->getYear()."</td><td>".$placement->getCity()." ".$placement->getCountry()."</td><td>".$placement->getType()."</td><td>".$placement->getDiscipline()."</td><td>".$placement->getPlacing()."</td>
                    <td><input type='radio' name='rGroup' value=".$placement->getId()." id='r".$x."'/></td></tr>";
                    }
                    $x++;
                }
                echo "</tbody></table>";
            }
            ?>
        </div>
        <input type="hidden" name="id" value="<?php echo isset($person) ? $person->getId() : null ?>">
        <div class="form-group" >
            <div class="row">
                <div class="col-md-4" >
                    <label for="name">Name</label>
                    <input type="text" name="name" id="name" value="<?php echo isset($person) ? $person->getName() : null ?>">
                </div>
                <div class="col-md-4">
                    <label for="surname">Surname</label>
                    <input type="text" name="surname" id="surname" value="<?php echo isset($person) ? $person->getSurname() : null ?>">
                </div>
                <div class="col-md-4">
                    <label for="placing">Placing</label>
                    <input type="number" name="placing" id="placing" min="1" value="1">
                </div>
            </div>
            <div class="row" style="justify-content: center; align-items: center; margin-top: 10px">
                <div class="col-md-3">
                    <button class="btn btn-secondary" style="width: 250px;" type="submit">Submit</button>
                </div>
                <div class="col-md-2">
                    <button class="btn btn-secondary" type="button" onclick="location.href ='http://wt34.fei.stuba.sk/zad2/index.php';">spat</button>
                </div>
            </div>
        </div>
    </form>
</div>

