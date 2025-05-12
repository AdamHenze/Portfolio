package com.packt.cardatabase;

import org.springframework.web.bind.annotation.*;

import com.packt.cardatabase.domain.Car;
import com.packt.cardatabase.domain.CarRepository;

@RestController
public class CarController {
	private final CarRepository repository;

	public CarController(CarRepository repository) {
		this.repository = repository;
	}

	@GetMapping("/cars")
	public Iterable<Car> getCars() {
		return repository.findAll();
	}
	@DeleteMapping("/cars/{id}")
	public void deleteById(@PathVariable("id") long id) { repository.deleteById(id);}
	@PostMapping("/cars")
	public void addCar(@RequestBody Car car) { repository.save(car);}
	@PutMapping("/cars/{id}")
	public void updateCar(@PathVariable("id") long id, @RequestBody Car car) {
		repository.deleteById(id);
		repository.save(car);
	}
}
