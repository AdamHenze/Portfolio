//Adam Henze
//2261 Java
//3/13/2023
//HW3

//Main
public class Main {
    public static void main(String args[]) {

        //create and populate employee and manager
        Employee Worker = new Employee("Tom", 25, "3141231234", "123 Oak Lane", 25000, "Janitor", "Sanitation");
        Manager Boss = new Manager("Joe", 46, "3141287634", "Homeless", 45000, "Nothing", "Management");

        //print data
        System.out.println("--------------------------------------------------------------");
        Worker.printsalary();
        System.out.println("--------------------------------------------------------------");
        Boss.printsalary();
        System.out.println("--------------------------------------------------------------");
    }
}
