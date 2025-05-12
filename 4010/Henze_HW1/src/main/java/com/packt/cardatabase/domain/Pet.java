//Adam Henze
//cs4010
//Henry Kang
//HW1
//2/12/2024

package com.packt.cardatabase.domain;

import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;

import java.time.LocalDate;

//pet entity
@Entity
public class Pet {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
//vars
    private Long id;

    private String name, species;

    private LocalDate dob;

    public Pet() {
    }

    // constructor
    public Pet(String name, String species, LocalDate dob, Owner owner) {
        super();
        this.name = name;
        this.species = species;
        this.dob = dob;
        this.owner = owner;
    }

    //defines one to many on owner
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "owner")
    private Owner owner;

    // Getter and setters
    public Owner getOwner() {
        return owner;
    }

    public void setOwner(Owner owner) {
        this.owner = owner;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSpecies() {
        return species;
    }

    public void setSpecies(String model) {
        this.species = species;
    }

    public LocalDate getDob() {
        return dob;
    }

    public void setDob(LocalDate dob) {
        this.dob = dob;
    }

}

