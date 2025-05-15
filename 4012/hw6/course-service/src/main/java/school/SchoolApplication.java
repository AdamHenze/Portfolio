package school;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class SchoolApplication {

	public static void main(String[] args) {
		SpringApplication.run(SchoolApplication.class, args);
	}

//	@Autowired
//	StudentRepository studentRepository;
//
//	@PostConstruct
//	public List<Student> initTable() {
//		List<Student> list = studentRepository.saveAll(List.of(
//				new Student("Roger Fereder", "Art", 4),
//				new Student("Rafael Nadal", "Physics", 3),
//				new Student("Novak Djokovic", "Chemistry", 2)
//				));
//		return list;
//	}
}
