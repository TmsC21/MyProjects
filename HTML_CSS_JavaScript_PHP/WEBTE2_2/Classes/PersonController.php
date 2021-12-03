<?php

require_once "Classes/Person.php";
require_once "Classes/Connection.php";
require_once "Classes/Placement.php";
class PersonController
{
    public PDO $conn;
    public function __construct(){
        $this->conn = (new Connection())->connectDatabase();
    }
    public function getPeople(){
        $stmt = $this->conn->prepare("select osoby.* from osoby join umiestnenia u on osoby.id = u.person_id group by osoby.id");
        $stmt->execute();
        $people = $stmt->fetchAll(PDO::FETCH_CLASS,"Person");

        foreach ($people as $person){
            $stmt = $this->conn->prepare("select umiestnenia.*, oh.city,oh.country,oh.type,oh.year from umiestnenia join oh on umiestnenia.oh_id = oh.id where person_id = :personID");
            $stmt->bindParam(":personID",$person->getId(), PDO::PARAM_INT);
            $stmt->execute();
            $placement = $stmt->fetchAll(PDO::FETCH_CLASS,"Placement");
            $person->setPlacements($placement);
        }
        $this->buildMainTable($people);
    }
    public function buildMainTable(&$people){
        echo "<thead><tr><th>Meno priezvisko</th><th>Rok ziskania medaile</th><th>Miesto konania</th><th>Typ olympiady</th><th>Disciplina</th></tr></thead><tbody>";
        foreach ($people as $person){
            foreach ($person->getPlacements() as $placement){
                echo "<tr><td><a href='displayPerson.php?id=".$person->getId()."'>".$person->getName()." ".$person->getSurname()."</a></td><td>".$placement->getYear()."</td><td>".$placement->getCity()." ".$placement->getCountry()."</td><td>".$placement->getType()."</td><td>".$placement->getDiscipline()."</td></tr>";
            }
        }
        echo "</tbody>";
    }
    public function getTopPeople(){
        $stmt = $this->conn->prepare("select osoby.*,sum(u.placing = 1) as gold_count from osoby join umiestnenia u on osoby.id = u.person_id group by osoby.id");
        $stmt->execute();
        $people = $stmt->fetchAll(PDO::FETCH_CLASS,"Person");
        $this->buildSecondTalbe($people);
    }

    public function buildSecondTalbe(&$people){
        echo "<thead><tr><th colspan ='4' style='border: none; background: white'>TOP 10 sportovcov</th></tr><tr><th>Meno priezvisko</th><th>Pocet medaily</th><th colspan='2'></th></thead><tbody>";
        $x =0;
        function usortTest($a, $b) {
            return ($a->getGoldCount() > $b->getGoldCount()) ? -1 : 1;
        }
        usort($people, "usortTest");
        foreach ($people as $person){
            if($x < 10 && $person->getGoldCount()>0){
                echo "<tr><td>".$person->getName()." ".$person->getSurname()."</td><td>".$person->getGoldCount()."</td><td><a href='editPerson.php?id=".$person->getId()."'><i class='fas fa-edit'></i></a></td><td><a href='deletePerson.php?id=".$person->getId()."'><i class='fas fa-trash-alt'></i></a></td></tr>";
                $x++;
            }
        }
        echo "</tbody>";
    }
    public function getPerson(int $id){
        $stmt = $this->conn->prepare("select osoby.*,sum(u.placing = 1) as gold_count from osoby join umiestnenia u on osoby.id = u.person_id where osoby.id = :personID");
        $stmt->bindParam(":personID",$id, PDO::PARAM_INT);
        $stmt->execute();
        $stmt->setFetchMode(PDO::FETCH_CLASS,"Person");
        $person = $stmt->fetch();

        $stmt = $this->conn->prepare("select umiestnenia.*, oh.city,oh.country,oh.type,oh.year from umiestnenia join oh on umiestnenia.oh_id = oh.id where person_id = :personID");
        $stmt->bindParam(":personID",$person->getId(), PDO::PARAM_INT);
        $stmt->execute();
        $placement = $stmt->fetchAll(PDO::FETCH_CLASS,"Placement");
        $person->setPlacements($placement);
        return $person;
    }
    public function setUmiestnenie(Person $person,int $place, int $type, string $discipline){
        $stmt = $this->conn->prepare("insert into umiestnenia(person_id,oh_id,placing,discipline) value (:person_id, :oh_id, :placing , :discipline)");
        $person_id = $person->getId();
        $stmt->bindParam(":person_id",$person_id, PDO::PARAM_INT);
        $stmt->bindParam(":oh_id",$type, PDO::PARAM_INT);
        $stmt->bindParam(":placing",$place, PDO::PARAM_INT);
        $stmt->bindParam(":discipline",$discipline, PDO::PARAM_STR);
        $stmt->execute();
    }
    public function insertPerson(Person $person){
        $name = $person->getName();
        $surname = $person->getSurname();
        $birth_day = $person->getBirthDay();
        $birth_place = $person->getBirthPlace();
        $birth_country = $person->getBirthCountry();
        $death_day = $person->getDeathDay();
        $death_place = $person->getDeathPlace();
        $death_country = $person->getDeathCountry();
        $stmt = $this->conn->prepare("insert into osoby(name,surname,birth_day,birth_place,birth_country,death_day,death_place,death_country) value (:name,:surname,:birth_day,:birth_place,:birth_country,:death_day,:death_place,:death_country)");
        $stmt->bindParam(":name",$name, PDO::PARAM_STR);
        $stmt->bindParam(":surname",$surname, PDO::PARAM_STR);
        $stmt->bindParam(":birth_day",$birth_day, PDO::PARAM_STR);
        $stmt->bindParam(":birth_place",$birth_place, PDO::PARAM_STR);
        $stmt->bindParam(":birth_country",$birth_country, PDO::PARAM_STR);
        $stmt->bindParam(":death_day",$death_day, PDO::PARAM_STR);
        $stmt->bindParam(":death_place",$death_place, PDO::PARAM_STR);
        $stmt->bindParam(":death_country",$death_country, PDO::PARAM_STR);

        try {
            $stmt->execute();
        }catch (Exception $e){
            return -1;
        }
        return $this->conn->lastInsertId();
    }
    public function updatePerson(Person $person,int $OG,int $placing){
        $stmt = $this->conn->prepare("Update osoby set osoby.name=:name, osoby.surname=:surname  where id = :ID");
        $name = $person->getName();
        $surname = $person->getSurname();
        $id = $person->getId();
        $stmt->bindParam(":name",$name, PDO::PARAM_STR);
        $stmt->bindParam(":surname",$surname, PDO::PARAM_STR);
        $stmt->bindParam(":ID",$id, PDO::PARAM_INT);
        $stmt->execute();

        $stmt = $this->conn->prepare("Update umiestnenia set placing=:place  where id = :ID");
        $stmt->bindParam(":place",$placing, PDO::PARAM_INT);
        $stmt->bindParam(":ID",$OG, PDO::PARAM_INT);
        $stmt->execute();
    }
}