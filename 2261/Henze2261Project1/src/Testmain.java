//Adam Henze
//Java 2261
//Laika Satish
//3rd March 2023
//Project 1

public class Testmain {
    public static void main(String args[]){
       //new employee
        Employee Newbie = new Employee();
        //method to seed password with random string
        Newbie.setPass();
        //method to get name of employee
        Newbie.getname();
        //method to create email address based on name
        Newbie.setEmail();
        //method to print current info
        Newbie.printinfo();
        //method to update password with user input
        Newbie.getPass();
        //methode to add strings into welcome email
        Newbie.welcome();
        //method to count words in welcome based on number of spaces
        Newbie.countwords();
    }
}
