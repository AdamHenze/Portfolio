public class Company {
    //create data types
    public String Name;
    public int Age;
    public String Phone;
    public String Address;
    public int Salary;

    //populate data with class constructor
    public Company(String NewName, int NewAge, String NewPhone, String NewAddress, int NewSalary){
        Name = NewName;
        Age = NewAge;
        Phone = NewPhone;
        Address = NewAddress;
        Salary = NewSalary;
    }

    //print salary
    public void printsalary(){
        System.out.println(Salary);
    }
}
