package com.example.school;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

import java.util.List;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest
@AutoConfigureMockMvc
//@ExtendWith(SpringExtension.class)
@ActiveProfiles("test")
class StudentIntegrationTest {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private StudentRepository studentRepository;

    private final ObjectMapper mapper = new ObjectMapper();

    @BeforeEach
    void setUp() {

        studentRepository.deleteAll();

        List<Student> expected = List.of(
                new Student(12345, "John Smith", "Computer Science", 1),
                new Student(32289, "Jane Doe", "Physics", 3),
                new Student(98237, "Peter Parker", "Biology", 2)
        );

        studentRepository.saveAll(expected);
    }

    @AfterEach
    void tearDown() {
        studentRepository.deleteAll();
    }

    @Test
    void getStudents_should_return_all_students() throws Exception {

        List<Student> expected = List.of(
                new Student(12345, "John Smith", "Computer Science", 1),
                new Student(32289, "Jane Doe", "Physics", 3),
                new Student(98237, "Peter Parker", "Biology", 2)
        );

        MvcResult mvcResult = mockMvc.perform(MockMvcRequestBuilders
                        .get("/student"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andReturn();

        List<Student> actual = mapper.readValue(mvcResult.getResponse().getContentAsString(), new TypeReference<>() {});

        assertThat(actual)
                .usingRecursiveComparison()
                .ignoringFields("id")
                .isEqualTo(expected);
    }

    @Test
    void getStudentByStudentId_should_return_one_student() throws Exception {

        Student expected = new Student(12345, "John Smith", "Computer Science", 1);

        MvcResult mvcResult = mockMvc.perform(MockMvcRequestBuilders
                        .get("/student/12345"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andReturn();

        Student actual = mapper.readValue(mvcResult.getResponse().getContentAsString(), Student.class);

        assertThat(actual)
                .usingRecursiveComparison()
                .ignoringFields("id")
                .isEqualTo(expected);
    }

    @Test
    void getStudentByStudentId_should_return_not_found() throws Exception {

        mockMvc.perform(MockMvcRequestBuilders
                        .get("/student/99999"))
                .andExpect(status().isNotFound());
    }

    @Test
    void addStudent_should_add_one_student() throws Exception {

        Student expected = new Student(54321, "Bruce Wayne", "Business Administration", 1);

        MvcResult mvcResult = mockMvc.perform(MockMvcRequestBuilders
                        .post("/student")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(mapper.writeValueAsString(expected)))
                .andExpect(status().isCreated())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andReturn();

        Student actual = mapper.readValue(mvcResult.getResponse().getContentAsString(), Student.class);

        assertThat(actual)
                .usingRecursiveComparison()
                .ignoringFields("id")
                .isEqualTo(expected);
    }

    @Test
    void updateStudent_should_update_one_student() throws Exception {
        Student expected = new Student(98237, "Peter Parker", "Criminology", 2);

        MvcResult mvcResult = mockMvc.perform(MockMvcRequestBuilders
                        .put("/student/98237")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(mapper.writeValueAsString(expected)))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andReturn();

        Student actual = mapper.readValue(mvcResult.getResponse().getContentAsString(), Student.class);

        assertThat(actual)
                .usingRecursiveComparison()
                .ignoringFields("id")
                .isEqualTo(expected);
    }

    @Test
    void deleteStudent_should_delete_one_student() throws Exception {

        mockMvc.perform(MockMvcRequestBuilders
                        .delete("/student/98237"))
                .andExpect(status().isNoContent());
    }
}