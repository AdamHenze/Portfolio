package com.example.school;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class StudentServiceTest {

    @Mock
    private StudentRepository studentRepository;

    @InjectMocks
    private StudentService studentService;

    @Test
    void getStudents_should_return_all_students() {
        List<Student> expected = Arrays.asList(
                new Student(12345, "John Smith", "Computer Science", 1),
                new Student(32289, "Jane Doe", "Physics", 3),
                new Student(98237, "Peter Parker", "Biology", 2));

        when(studentRepository.findAll()).thenReturn(expected);

        List<Student> actual = studentService.getStudents();

        assertThat(actual.size()).isEqualTo(expected.size());
        assertThat(actual).usingRecursiveComparison().isEqualTo(expected);
    }

    @Test
    void getStudentByStudentId_should_return_one_student() {
        Student expected = new Student(12345, "John Smith", "Computer Science", 1);

        when(studentRepository.findByStudentId(12345)).thenReturn(Optional.of(expected));

        Optional<Student> actual = studentService.getStudentByStudentId(12345);

        assertThat(actual.isPresent()).isTrue();
        assertThat(actual.get()).usingRecursiveComparison().isEqualTo(expected);
    }

    @Test
    void addStudent_should_save_one_student() {
        Student expected = new Student(12345, "John Smith", "Computer Science", 1);

        when(studentRepository.save(expected)).thenReturn(expected);

        Student actual = studentService.addStudent(expected);

        assertThat(actual).usingRecursiveComparison().isEqualTo(expected);
    }

    @Test
    void updateStudent_should_update_one_student() {
        Student existingStudent = new Student(12345, "John Smith", "Computer Science", 1);
        Student updatedStudent = new Student(12345, "John Smith", "Economics", 1);

        when(studentRepository.findByStudentId(12345)).thenReturn(Optional.of(existingStudent));

        when(studentRepository.save(existingStudent)).thenReturn(existingStudent);

        Student actual = studentService.updateStudent(12345, updatedStudent);

        assertThat(actual).usingRecursiveComparison().isEqualTo(updatedStudent);
    }

    @Test
    void updateStudent_should_throw_exception_if_id_not_found() {

        Student updatedStudent = new Student(12345, "John Smith", "Economics", 1);

        when(studentRepository.findByStudentId(12345)).thenReturn(Optional.ofNullable(null));

        assertThatThrownBy(() -> { studentService.updateStudent(12345, updatedStudent); })
                .isInstanceOf(IllegalStateException.class)
                .hasMessage("[updateStudent] student with id 12345 does not exist");
    }

    @Test
    void deleteStudent_should_delete_one_student() {

        Student existingStudent = new Student(12345, "John Smith", "Computer Science", 1);

        when(studentRepository.findByStudentId(12345)).thenReturn(Optional.of(existingStudent));

        doNothing().when(studentRepository).deleteByStudentId(12345);

        studentService.deleteStudent(12345);

        verify(studentRepository, times(1)).deleteByStudentId(12345);
    }

    @Test
    void deleteStudent_should_throw_exception_if_id_not_found() {

        when(studentRepository.findByStudentId(12345)).thenReturn(Optional.ofNullable(null));

        assertThatThrownBy(() -> { studentService.deleteStudent(12345); })
                .isInstanceOf(IllegalStateException.class)
                .hasMessage("[deleteStudent] student with id 12345 does not exist");
    }

}