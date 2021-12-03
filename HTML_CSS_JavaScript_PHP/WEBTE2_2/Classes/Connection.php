<?php
require_once "config.php";

class Connection
{
    private $conn;
    public function connectDatabase(){
        try {
            $this->conn = new PDO("mysql:host=".servername.";dbname=".dbname, username, password);
            $this->conn->exec("set names utf8");
            $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        } catch (PDOException $e) {
            echo "Error: " . $e->getMessage();
        }
        return $this->conn;
    }
}