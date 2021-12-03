<?php
require_once "Classes/Connection.php";
require_once "Classes/Person.php";

class OlympicPlayers
{
    public function __construct()
    {
        $this->conn = (new Connection())->connectDatabase();
    }
    public function getOptions(){
        $stmt = $this->conn->prepare("select * from osoby");
        $stmt->execute();
        $OH = $stmt->fetchAll(PDO::FETCH_CLASS,"Person");
        foreach ($OH as $Ogame){
            echo "<option value='".$Ogame->getId()."'>".$Ogame->getName()." ".$Ogame->getSurname()."</option>";
        }
    }
}