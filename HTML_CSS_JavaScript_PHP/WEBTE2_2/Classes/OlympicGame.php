<?php
class OlympicGame{
    private int $id;
    private string $type;
    private int $year;
    private int $order;
    private string $city;
    private string $country;

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
    public function getCity(): string
    {
        return $this->city;
    }

    /**
     * @return string
     */
    public function getCountry(): string
    {
        return $this->country;
    }


}
