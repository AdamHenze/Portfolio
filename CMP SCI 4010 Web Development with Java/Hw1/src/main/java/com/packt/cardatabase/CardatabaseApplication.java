//Adam Henze
//cs4010
//Henry Kang
//HW1
//2/12/2024

package com.packt.cardatabase;

import java.time.LocalDate;
import java.util.Arrays;

import com.packt.cardatabase.domain.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class CardatabaseApplication implements CommandLineRunner {
	private static final Logger logger = LoggerFactory.getLogger(CardatabaseApplication.class);

	private final CarRepository repository;
	private final OwnerRepository orepository;
	private final PetRepository prepository;

	public CardatabaseApplication(CarRepository repository, OwnerRepository orepository, PetRepository prepository) {
		this.repository = repository;
		this.orepository = orepository;
		this.prepository = prepository;
	}

	public static void main(String[] args) {
		SpringApplication.run(CardatabaseApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {
		// Add owner objects and save these to db

		LocalDate dob;

		//updated table additions

		Owner owner1 = new Owner("John" , "Johnson");
		Owner owner2 = new Owner("Mary" , "Robinson");
		Owner owner3 = new Owner("Fanny" , "May");
		Owner owner4 = new Owner("Mary" , "Mills");
		Owner owner5 = new Owner("Alan" , "Carr");
		Owner owner6 = new Owner("Rob" , "Robinson");
		Owner owner7 = new Owner("Mary" , "Shelly");
		Owner owner8 = new Owner("Tim" , "Robins");
		Owner owner9 = new Owner("Mary" , "Robin");
		Owner owner10 = new Owner("Sean" , "Robinson");
		orepository.saveAll(Arrays.asList(owner1, owner2, owner3, owner4, owner5, owner6, owner7, owner8, owner9, owner10));
			
		repository.save(new Car("Ford", "Mustang", "Red", "ADF-1121", 2023, 59000, owner1));
		repository.save(new Car("Nissan", "Leaf", "White", "SSJ-3002", 2020, 29000, owner2));
		repository.save(new Car("Dodge", "Challenger", "Black", "KKO-0212", 2022, 39000, owner2));

		repository.save(new Car("Ford", "Mustang", "Red", "ADF-1121", 2023, 59000, owner3));
		repository.save(new Car("Nissan", "Leaf", "White", "SSJ-3002", 2020, 29000, owner5));
		repository.save(new Car("Dodge", "Challenger", "Black", "KKO-0212", 2022, 39000, owner5));
		repository.save(new Car("Toyota", "Mustang", "Orange", "ADF-1121", 2023, 59000, owner7));
		repository.save(new Car("Citron", "Oldsmobile", "White", "SSJ-3002", 2020, 29000, owner6));
		repository.save(new Car("Porsche", "911", "Green", "KKO-0212", 2022, 39000, owner8));
		repository.save(new Car("Schwinn", "Bicycle", "Red", "ADF-1121", 2023, 59000, owner4));
		repository.save(new Car("VW", "Bug", "Yellow", "SSJ-3002", 2020, 29000, owner9));
		repository.save(new Car("BMW", "Something", "White", "KKO-0212", 2022, 39000, owner10));

		prepository.save(new Pet("Roxy", "Pit Bull", LocalDate.of(2020,9,24), owner2));
		prepository.save(new Pet("Basil", "Lab", LocalDate.of(2021,4,2), owner2));
		prepository.save(new Pet("That Cat", "Some Cat", LocalDate.of(2024,5,4), owner1));
		prepository.save(new Pet("Alan", "Fox", LocalDate.of(2013,9,18), owner6));
		prepository.save(new Pet("Mark", "Frog", LocalDate.of(2017,10,20), owner4));
		prepository.save(new Pet("NONE", "Rock", LocalDate.of(1963,2,27), owner3));
		prepository.save(new Pet("Bubbles", "Fish", LocalDate.of(2001,2,5), owner5));
		prepository.save(new Pet("Rowdy", "Dog - Mutt", LocalDate.of(2000,1,12), owner7));
		prepository.save(new Pet("Karen", "Bobcat", LocalDate.of(2013,6,1), owner7));
		prepository.save(new Pet("Danny", "Brown Bear", LocalDate.of(2001,9,2), owner4));



		// Fetch all cars and log to console
		for (Car car : repository.findAll()) {
			logger.info("brand: {}, model: {}", car.getBrand(), car.getModel());
		}

		// loop pets to logger
		for (Pet pet : prepository.findAll()) {
			logger.info("Name: {}, Species: {}, DOB: {}", pet.getName(), pet.getSpecies(), pet.getDob());
		}
	}
}
