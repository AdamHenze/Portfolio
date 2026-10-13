package com.example.school;

import javax.annotation.PostConstruct;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.util.List;

@SpringBootApplication
public class SchoolApplication {

	public static void main(String[] args) {
		SpringApplication.run(SchoolApplication.class, args);
	}

	@Autowired
	StudentRepository studentRepository;
	@Autowired
	CourseRepository courseRepository;

	@PostConstruct
	public List<Student> initTable() {
		List<Student> list = studentRepository.saveAll(List.of(
				new Student("Roger Fereder", "Art", 4),
				new Student("Rafael Nadal", "Physics", 3),
				new Student("Novak Djokovic", "Chemistry", 2),

				new Student("Alan Bigsby", "Magnets", 4),
				new Student("Ryan Aakjdsflakjdfh", "Undeclared", 7)
				));
		return list;
	}


	@PostConstruct
	public List<Course> initCourseTable() {
		List<Course> courselist = courseRepository.saveAll(List.of(
				new Course("Magnets", "46548", 50L),
				new Course("More Magnets", "48948", 15L),
				new Course("Else", "46001", 30L),
				new Course("Free Period", "42500", 20L),
				new Course("And Stuff", "00001", 60L)
		));
		return courselist;
	}
}
