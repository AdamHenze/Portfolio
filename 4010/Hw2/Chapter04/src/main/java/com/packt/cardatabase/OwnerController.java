package com.packt.cardatabase;

import com.packt.cardatabase.domain.Owner;
import com.packt.cardatabase.domain.OwnerRepository;
import org.springframework.web.bind.annotation.*;

import com.packt.cardatabase.domain.Car;
import com.packt.cardatabase.domain.CarRepository;

@RestController
public class OwnerController {
    private final OwnerRepository repository;

    public OwnerController(OwnerRepository repository) {
        this.repository = repository;
    }

    @GetMapping("/Owners")
    public Iterable<Owner> getOwners() {
        return repository.findAll();
    }
    @DeleteMapping("/Owners/{id}")
    public void deleteById(@PathVariable("id") long id) { repository.deleteById(id);}
    @PostMapping("/Owners")
    public void addOwner(@RequestBody Owner owner) { repository.save(owner);}
    @PutMapping("/Owners/{id}")
    public void updateOwner(@PathVariable("id") long id, @RequestBody Owner owner) {
        repository.deleteById(id);
        repository.save(owner);
    }
}
