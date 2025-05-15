import java.util.Scanner;

public class shuttle extends vehicle implements VehicleMethods{

    private Scanner input = new Scanner(System.in);

    //declare variables
    private int routeposition = 0;
    private String[] route;
    private int[] fares;

    //constructor
    public shuttle(String companybase){

        //call to vehicle constructor passing company base for location
        super(companybase);

        //number of stops
        int routestops;

        //get stops
        System.out.println("Enter the number of stops for shuttle " + this.getId() + ":");
        routestops = input.nextInt();

        //error check for input
        if( routestops < 1){
            System.out.println("Please enter a positive number:");
            routestops = input.nextInt();
        } else {

            //create arrays for stop locations and fares
            fares = new int[routestops];
            route = new String[routestops];

            //loop to enter location names and fares
            for( int i = 0; i < routestops; i++){
                if(i == 0){
                    route[i] = companybase;
                    System.out.println("Enter the fare of company base (stop #1):");
                    fares[i] = input.nextInt();
                } else {

                    //the use of input.nextInt does not call a new line, a blank instance of nextLine removes the int and calls a new line for stop name
                    input.nextLine();
                    System.out.println("Enter the name of stop #" + (i + 1) + ":");
                    route[i] = input.nextLine();

                    System.out.println("Enter the fare of stop #" + (i + 1) + ":");
                    fares[i] = input.nextInt();
                }
            }

        }
        //set next stop to next location on route array
        this.setDestination(route[1]);
    }

    //arrived method
    public void arrived(){

        //increment route position, but reset to 0 if beyond array length
        if( routeposition < route.length - 1){
            routeposition++;
        } else {
            routeposition = 0;
        }

        //update location
        this.setLocation(route[routeposition]);

        //update next stop, set to position 0 if beyond array
        if(routeposition < route.length - 1){
            this.setDestination(route[routeposition + 1]);
        } else {
            this.setDestination(route[0]);
        }


    }

    //get status to check if next stop matches customer location
    public String getstatus(String destination){
        String status;
        String nextstop = this.getDestination();
        //check for match
        if(destination.equals(nextstop)){
            status = "Available";
        } else {
            status = "Unavailable";
        }
        return status;
    }

    //simple methods to get private data

    public int getFare(int pos){
        return fares[pos];
    }

    public String getRoute(int pos){
        return route[pos];
    }

    public int getRouteLength(){
        return route.length;
    }

}
