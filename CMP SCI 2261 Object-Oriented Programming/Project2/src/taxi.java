import java.util.Scanner;

public class taxi extends vehicle implements VehicleMethods{

    private Scanner input = new Scanner(System.in);

    private int fare;

    //constructor
    public taxi(String companybase){
        //calls vehicle constructor, passing company base for location
        super(companybase);
        //set fare of taxi
        System.out.println("Enter the standard fare for taxi " + this.getId() + ":");
        fare = input.nextInt();
    }

    //arrive updates location to previous destination, set destination to null until booked again
    public void arrived(){
        this.setLocation(this.getDestination());
        this.setDestination(null);
    }

    //get status based on destination status
    public String getstatus(String destination){
        String status;
        if(this.getDestination() == null){
            status = "Available";
        } else {
            status = "Booked";
        }
        return status;
    }

    //simple return method
    public int getFare() {
        return fare;
    }
}

