//Import Utilities
import java.util.Random;
import java.util.Scanner;

//Create Employee Class
public class Employee {

    //declare variables of employee
    private String First;
    private String Last;
    private String Pass;
    private String Email;
    private String Welcome;
    private int capacity = 1;

    //seed random
    private Random rnd = new Random();
    //create character for password randomize
    private char c;
    //create scanner for input
    private Scanner input = new Scanner(System.in);

    //empty constructor, data to be filled in methods
    public Employee() {
    }

    //print info after employee naming
    public void printinfo(){
        System.out.println("Your new password is:");
        System.out.println(Pass);
        System.out.println("Your new email is:");
        System.out.println(Email);
        System.out.println("Your mailbox capacity is: " + capacity + "gb.");

    }

    //set name strings
    public void getname(){
        System.out.print("Enter your first name: ");
        First = input.nextLine();
        System.out.print("Enter your last name: ");
        Last = input.nextLine();
    }

    //add name to make email
    public void setEmail(){
        Email = First + "_" + Last + "@umsl.edu";
    }

    //randomize pass word by creating a string of random characters
    public void setPass(){
        //empty pass
        Pass = "";
        //for loop 20 times
        for (int i = 0; i < 10; i++){
            //random char
            c = (char) ('!' + rnd.nextInt(93));
            //add to pass
            Pass = Pass + c;
        }
    }

    //method to set new pass
    public void getPass(){
        System.out.println("Enter new password: ");
        Pass = input.nextLine();
        System.out.println("Password changed.");
    }

    //method to add strings into welcome
    public void welcome(){
        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        Welcome = "\nWelcome Email!\n" +
                "Subject Line: Welcome to Umsl\n" +
                "Dear " + First + " " + Last + ",\n" +
                "Welcome to UMSL — we are excited to have you aboard. Just a reminder, your first \n" +
                "day is August 6. All you need to do is click the Zoom link in your calendar invite at 9 \n" +
                "a.m. CST to join our onboarding meeting.";
        System.out.println(Welcome);
    }

    //method to count words of welcome email
    public void countwords(){
        int wordcount;
        //creates array of strings based on input and separator of space " "
        String[] words = Welcome.split("\\s+");
        //length of array is now word count
        wordcount = words.length;
        //print wordcount
        System.out.println("Word count is: " + wordcount);
    }
}