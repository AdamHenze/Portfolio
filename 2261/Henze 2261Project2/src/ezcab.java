import java.util.Scanner;

public class ezcab {

    private Scanner input = new Scanner(System.in);

    public String companyname;
    public String companybase;
    public taxi[] Taxis;
    public shuttle[] Shuttles;

    //constructor of excab objects to store arrays of taxis and shuttles under companynames
    public ezcab(){
        System.out.println("Enter a company name:");
        companyname = input.nextLine();
        System.out.println("Enter a company base:");
        companybase = input.nextLine();
        //call to add taxis and shuttles methods
        this.addtaxis();
        this.addshuttles();
    }

    //simple method to create array of vehicle-taxis and then parse array and populate with taxis
    public void addtaxis(){

        int addtaxis;

        System.out.println("Enter the number of taxis to add:");
        addtaxis = input.nextInt();

        if(addtaxis == 0){
            return;
        } else {
            Taxis = new taxi[addtaxis];
        }

        for( int i = 0; i < addtaxis; i++){
            System.out.println("Taxi #" + (i + 1) + ":");
            Taxis[i] = new taxi(companybase);
        }

    }

    //simple method to create an array of shuttles then parse the array while populating it with shuttle-vehicles
    public void addshuttles(){

        int addshuttles;

        System.out.println("Enter the number of shuttles to add:");
        addshuttles = input.nextInt();

        if(addshuttles == 0){
            return;
        } else {
            Shuttles = new shuttle[addshuttles];
        }

        for( int i = 0; i < addshuttles; i++){
            System.out.println("Shuttle #" + (i + 1) + ":");
            Shuttles[i] = new shuttle(companybase);
        }


    }

}
