//Create class of Assignment
public class assignment {
    //populate string fields with 'empty' if no data is passed to constructor
    String term = "Empty";
    String code = "Empty";
    String course = "Empty";

    //empty constructor
    assignment(){
    }

    //constructor with new data being passed to class variables
    assignment(String newcourse, String newterm, String newcode){
        course = newcourse;
        term = newterm;
        code = newcode;
    }

    //method to return full course name based on object data
    String coursename(){
        String name = (course + " " + term + " " + code);
        return (name);
    }
}
