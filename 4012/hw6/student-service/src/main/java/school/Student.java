package school;

import jakarta.persistence.*;

@Entity
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "student_seq_generator")
    @SequenceGenerator(name = "student_seq_generator", sequenceName = "student_id_seq", allocationSize = 1)
    private Long id;
    private String name;
    private String major;
    private Integer year;

    public Student() {
    }

    public Student(String name, String major, Integer year) {
        this.name = name;
        this.major = major;
        this.year = year;
    }

    public Student(Long id, String name, String major, Integer year) {
        this.id = id;
        this.name = name;
        this.major = major;
        this.year = year;
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

    public String getMajor() {
        return major;
    }

    public void setMajor(String major) {
        this.major = major;
    }

    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", major='" + major + '\'' +
                ", year=" + year +
                '}';
    }
}
