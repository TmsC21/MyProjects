<?php
require_once "Classes/Connection.php";
require_once "Classes/OlympicGame.php";

class ListBarOH
{
    public function __construct()
    {
        $this->conn = (new Connection())->connectDatabase();
    }
    public function getOptions(){
        $stmt = $this->conn->prepare("select oh.* from oh");
        $stmt->execute();
        $OH = $stmt->fetchAll(PDO::FETCH_CLASS,"OlympicGame");
        foreach ($OH as $Ogame){
            echo "<option value='".$Ogame->getId()."'>".$Ogame->getCity()." ".$Ogame->getCountry()."</option>";
        }
    }
}