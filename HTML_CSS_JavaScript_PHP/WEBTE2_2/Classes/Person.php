<?php
require_once "Classes/Placement.php";

class Person
{
    private int $id;
    private string $name;
    private string $surname;
    private string $birth_day;
    private string $birth_place;
    private string $birth_country;
    private ?string $death_day;
    private ?string $death_place;
    private ?string $death_country;
    private int $gold_count;

    private $placements;

    /**
     * @return int
     */
    public function getGoldCount(): int
    {
        return $this->gold_count;
    }

    /**
     * @param int $gold_count
     */
    public function setGoldCount(int $gold_count): void
    {
        $this->gold_count = $gold_count;
    }


    /**
     * @return mixed
     */
    public function getPlacements()
    {
        return $this->placements;
    }

    /**
     * @return mixed
     */
    public function getOlympicGame()
    {
        return $this->OlympicGame;
    }

    /**
     * @param mixed $OlympicGame
     */
    public function setOlympicGame($OlympicGame): void
    {
        $this->OlympicGame = $OlympicGame;
    }

    /**
     * @param mixed $placements
     */
    public function setPlacements($placements): void
    {
        $this->placements = $placements;
    }

    /**
     * @return int
     */
    public function getId(): int
    {
        return $this->id;
    }

    /**
     * @return string
     */
    public function getName(): string
    {
        return $this->name;
    }

    /**
     * @return string
     */
    public function getSurname(): string
    {
        return $this->surname;
    }

    /**
     * @param string $name
     */
    public function setName(string $name): void
    {
        $this->name = $name;
    }

    /**
     * @return string
     */
    public function getBirthDay(): string
    {
        return $this->birth_day;
    }

    /**
     * @param string $birth_day
     */
    public function setBirthDay(string $birth_day): void
    {
        $this->birth_day = $birth_day;
    }

    /**
     * @return string
     */
    public function getBirthPlace(): string
    {
        return $this->birth_place;
    }

    /**
     * @param string $birth_place
     */
    public function setBirthPlace(string $birth_place): void
    {
        $this->birth_place = $birth_place;
    }

    /**
     * @return string
     */
    public function getBirthCountry(): string
    {
        return $this->birth_country;
    }

    /**
     * @return string|null
     */
    public function getDeathDay(): ?string
    {
        return $this->death_day;
    }

    /**
     * @param string|null $death_day
     */
    public function setDeathDay(?string $death_day): void
    {
        $this->death_day = $death_day;
    }

    /**
     * @param string|null $death_place
     */
    public function setDeathPlace(?string $death_place): void
    {
        $this->death_place = $death_place;
    }

    /**
     * @param string|null $death_country
     */
    public function setDeathCountry(?string $death_country): void
    {
        $this->death_country = $death_country;
    }

    /**
     * @return string|null
     */
    public function getDeathPlace(): ?string
    {
        return $this->death_place;
    }

    /**
     * @return string|null
     */
    public function getDeathCountry(): ?string
    {
        return $this->death_country;
    }

    /**
     * @param string $birth_country
     */
    public function setBirthCountry(string $birth_country): void
    {
        $this->birth_country = $birth_country;
    }

    /**
     * @param int $id
     */
    public function setId(int $id): void
    {
        $this->id = $id;
    }

    /**
     * @param string $surname
     */
    public function setSurname(string $surname): void
    {
        $this->surname = $surname;
    }


}