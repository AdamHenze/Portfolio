package com.example.school;

import jakarta.annotation.PostConstruct;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.util.List;

//@SpringBootApplication
//public class SchoolApplication {
//
//	public static void main(String[] args) {
//		SpringApplication.run(SchoolApplication.class, args);
//	}
//
//	@Autowired
//	StudentRepository studentRepository;
//
//	@PostConstruct
//	public List<Student> initTable() {
//		List<Student> list = studentRepository.saveAll(List.of(
//				new Student(12345, "Roger Fereder", "Art", 4),
//				new Student(43632, "Rafael Nadal", "Physics", 3),
//				new Student(23095, "Novak Djokovic", "Chemistry", 2)
//				));
//		return list;
//	}
//}

@SpringBootApplication
public class SchoolApplication implements CommandLineRunner {
	private static final Logger logger = LoggerFactory.getLogger(SchoolApplication.class);
	private final StudentRepository repository;
	//private final OwnerRepository orepository;
	private final AppUserRepository urepository;

	public SchoolApplication(StudentRepository repository, AppUserRepository urepository) {
		this.repository = repository;
		//this.orepository = orepository;
		this.urepository = urepository;
	}

	public static void main(String[] args) {
		SpringApplication.run(SchoolApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {
		// Add owner objects and save these to db
//		Owner owner1 = new Owner("John", "Johnson");
//		Owner owner2 = new Owner("Mary", "Robinson");
//		orepository.saveAll(Arrays.asList(owner1, owner2));
//
		repository.save(new Student(12345, "Roger Fereder", "Art", 4));
		repository.save(new Student(43632, "Rafael Nadal", "Physics", 3));
		repository.save(new Student(23095, "Novak Djokovic", "Chemistry", 2));
//
		// Username: user, password: user
		urepository.save(new AppUser("user", "$2a$10$NVM0n8ElaRgg7zWO1CxUdei7vWoPg91Lz2aYavh9.f9q0e4bRadue", "USER"));
		// Username: admin, password: admin
		urepository.save(new AppUser("admin","$2a$10$8cjz47bjbR4Mn8GMg9IZx.vyjhLXR/SKKMSZ9.mP9vpMu0ssKi8GW", "ADMIN"));
//
//		// Fetch all cars and log to console
//		for (Car car : repository.findAll()) {
//			logger.info("brand: {}, model: {}", car.getBrand(), car.getModel());
//		}
	}
}
