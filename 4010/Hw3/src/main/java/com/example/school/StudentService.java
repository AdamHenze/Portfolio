package com.example.school;

import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class StudentService {

    private final StudentRepository studentRepository;

    @Autowired
    public StudentService(StudentRepository studentRepository) {
        this.studentRepository = studentRepository;
    }

    public List<Student> getStudents() {
        return studentRepository.findAll();
    }

    public Optional<Student> getStudentByStudentId(Integer studentId) {
        return studentRepository.findByStudentId(studentId);
    }

    public Student addStudent(Student student) {
        return studentRepository.save(student);
    }

    public Student updateStudent(Integer studentId, Student student) {
        Student existingStudent = studentRepository.findByStudentId(studentId)
                .orElseThrow(() -> new IllegalStateException("[updateStudent] student with id " + studentId + " does not exist"));

        existingStudent.setName(student.getName());
        existingStudent.setMajor(student.getMajor());
        existingStudent.setYear(student.getYear());

        return studentRepository.save(existingStudent);
    }

    @Transactional
    public void deleteStudent(Integer studentId) {
        studentRepository.findByStudentId(studentId)
                .orElseThrow(() -> new IllegalStateException("[deleteStudent] student with id " + studentId + " does not exist"));

        studentRepository.deleteByStudentId(studentId);
    }
}
