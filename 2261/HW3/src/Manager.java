public class Manager extends Company{

    //create data extensions
    public String Special;
    public String Dept;

    //populate data with constructor
    public Manager(String NewName, int NewAge, String NewPhone, String NewAddress, int NewSalary, String NewSpecial, String NewDept){
        super(NewName, NewAge, NewPhone, NewAddress, NewSalary);
        Special = NewSpecial;
        Dept = NewDept;
    }

    public void printsalary(){
        //print data
        System.out.println("Name: " + Name);
        System.out.println("Age: " + Age);
        System.out.println("Phone: " + Phone);
        System.out.println("Address: " + Address);
        System.out.println("Special: " + Special);
        System.out.println("Department: " + Dept);
        System.out.print("Manager salary is: ");
        //override super method
        super.printsalary();
    }
}
