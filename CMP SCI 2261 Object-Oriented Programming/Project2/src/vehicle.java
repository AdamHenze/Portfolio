import java.util.Scanner;

public class vehicle {

    private Scanner input = new Scanner(System.in);

    //variables for vehicle plate location and destination
    private String id;
    private String location;
    private String destination = null;

    //constructor to call setid for plate id and uses company base as initial location
    public vehicle(String companybase){
        this.setId();
        this.location = companybase;
    }

    //simple method to input plate id
    public void setId(){
        System.out.println("Enter the Vehicle Plate ID:");
        id = input.nextLine();
    }

    //simple methods for set/get of private data

    public String getId(){
        return id;
    }

    public void setDestination(String newDestination){
        destination = newDestination;
    }

    public String getDestination() {
        return destination;
    }

    public void setLocation(String newLocation){
        location = newLocation;
    }

    public String getLocation() {
        return location;
    }

}