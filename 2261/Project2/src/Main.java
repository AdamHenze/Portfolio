import java.util.Scanner;

public class Main {
    public static void main(String args[]) {

        Scanner input = new Scanner(System.in);

        //number of companies
        int companycount = 0;
        //array of companies
        ezcab companies[] = null;
        //int to store menu input
        int userinput;
        //int to store company of available taxi
        int tempcompanytaxi;
        //int to store company of available shuttle
        int tempcompanyshuttle;
        //int to store taxi
        int temptaxi;
        //int to store shuttle
        int tempshuttle;
        //string for status check
        String status = null;
        //string for customer inputs
        String customerLocation = null;
        String customerDestination = null;

        //menu
        System.out.println("Welcome, Please select an option:");
        System.out.println("1.) Add a company to the register.");
        System.out.println("2.) Check the status of a Taxi or Shuttle.");
        System.out.println("3.) Book a Taxi or Shuttle.");
        System.out.println("4.) Wait for Vehicles to Arrive at Destination");
        System.out.println("5.) Exit program.");

        userinput = input.nextInt();

        //loop while not 5 (exit)
        while(userinput != 5){

            //error check for proper input
            while(userinput < 1 || userinput > 5){
                System.out.println("Please select between 1 and 4:");
                userinput = input.nextInt();
            }

            //case based on input
            switch(userinput){
                case 1:
                    //add company by temp copy of array, create new array with +1 size, copy contents to new array, populate new position
                    companycount++;

                    ezcab temp[] = companies;
                    companies = new ezcab[companycount];

                    if(temp != null) {
                        for (int i = 0; i < temp.length; i++) {
                            companies[i] = temp[i];
                        }
                    }
                    companies[companycount - 1] = new ezcab();
                    break;
                case 2:
                    //case to check on the status of vehicles, will parse array of companies and arrays of vehicles to check for matching ID and return status
                    input.nextLine();
                    System.out.println("Please enter the ID (Plate) of the Vehicle to check the status of:");
                    String taxiId = input.nextLine();

                    status = null;
                    if(companies != null) {
                        for (int i = 0; i < companies.length; i++) {
                            if (companies[i].Taxis != null) {
                                for (int j = 0; j < companies[i].Taxis.length; j++) {
                                    if (taxiId.equals(companies[i].Taxis[j].getId())) {
                                        status = companies[i].Taxis[j].getstatus(null);
                                        System.out.println("The location of this Taxi is " + companies[i].Taxis[j].getLocation() + ".");
                                        System.out.println("This taxi is " + status + ".");
                                        break;
                                    }
                                }
                            }
                            if (companies[i].Shuttles != null) {
                                for (int j = 0; j < companies[i].Shuttles.length; j++) {
                                    if (taxiId.equals(companies[i].Shuttles[j].getId())) {
                                        status = companies[i].Shuttles[j].getDestination();
                                        System.out.println("The location of this shuttle is " + companies[i].Shuttles[j].getLocation() + ".");
                                        System.out.println("The next stop of this shuttle is " + status + ".");
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if(status == null) {
                        System.out.println("That ID did not match any known records.");
                    }
                    break;
                case 3:
                    //Case for customer to book taxis and shuttles
                    status = null;

                    //customer input
                    input.nextLine();
                    System.out.println("Please enter your current location:");
                    customerLocation = input.nextLine();
                    System.out.println("Please enter your desired destination:");
                    customerDestination = input.nextLine();

                    //check for companies populated
                    if(companies != null) {
                        temptaxi = -1;
                        tempshuttle = -1;
                        tempcompanytaxi = -1;
                        tempcompanyshuttle = -1;

                        //parse companies
                        for (int i = 0; i < companies.length; i++) {
                            status = null;

                            //parse shuttles for mathcing location and destination, return shuttle and fare if matching
                            if (companies[i].Shuttles != null) {
                                for (int j = 0; j < companies[i].Shuttles.length; j++) {
                                    status = companies[i].Shuttles[j].getstatus(customerDestination);
                                    if(customerLocation.equals(companies[i].Shuttles[j].getLocation()) && status.equals("Available")){
                                        System.out.println("Shuttle " + companies[i].Shuttles[j].getId() + " is available from your location to your destination.");
                                        for(int k = 0; k < companies[i].Shuttles[j].getRouteLength(); k++){
                                            if(customerDestination.equals(companies[i].Shuttles[j].getRoute(k))){
                                                System.out.println("The fare for this route is $" + companies[i].Shuttles[j].getFare(k) + ".");
                                                tempcompanyshuttle = i;
                                                tempshuttle = j;
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                            //parse list of taxis to check for available, will select taxis at customer location, if now taxis at customer then will select first available taxi
                            if (companies[i].Taxis != null) {
                                for (int j = 0; j < companies[i].Taxis.length; j++) {
                                    status = companies[i].Taxis[j].getstatus(customerDestination);
                                    if(customerLocation.equals(companies[i].Taxis[j].getLocation()) && status.equals("Available")){
                                        System.out.println("Taxi " + companies[i].Taxis[j].getId() + " is available.");
                                        System.out.println("The fare for this route is $" + companies[i].Taxis[j].getFare() + ".");
                                        tempcompanytaxi = i;
                                        temptaxi = j;
                                        break;
                                    } else if (status.equals("Available")) {
                                        System.out.println("Taxi " + companies[i].Taxis[j].getId() + " is available.");
                                        System.out.println("The fare for this route is $" + companies[i].Taxis[j].getFare() + ".");
                                        tempcompanytaxi = i;
                                        temptaxi = j;
                                        break;
                                    }

                                }
                                break;
                            }
                        }
                        //if no vehicles
                        if(tempshuttle == -1 && temptaxi == -1){
                            System.out.println("There are currently no available Taxis or Shuttles from your location to your destination.");
                        } else {

                            //if tempshuttle not updated then only taxi available
                            if(tempshuttle == -1){
                                System.out.println("Would you like to book the available taxi?");
                                System.out.println("1.) Yes");
                                System.out.println("2.) No");

                                userinput = input.nextInt();

                                while(userinput < 1 || userinput > 2){
                                    System.out.println("Please enter 1 or 2.");
                                    userinput = input.nextInt();
                                }

                                if(userinput == 1){
                                    companies[tempcompanytaxi].Taxis[temptaxi].setDestination(customerDestination);
                                }

                            //if temp taxi not updated then only shuttle available
                            } else if (temptaxi == -1){

                                System.out.println("Would you like a ticket to the available Shuttle?");
                                System.out.println("1.) Yes");
                                System.out.println("2.) No");

                                userinput = input.nextInt();

                                while(userinput < 1 || userinput > 2){
                                    System.out.println("Please enter 1 or 2.");
                                    userinput = input.nextInt();
                                }

                            //if both temps updated then select between taxi and shuttle
                            } else {

                                System.out.println("Would you like a ticket to the available Shuttle, or the Taxi?");
                                System.out.println("1.) Shuttle");
                                System.out.println("2.) Taxi");
                                System.out.println("3.) None, Exit.");

                                userinput = input.nextInt();

                                while(userinput < 1 || userinput > 3){
                                    System.out.println("Please enter 1, 2,or 3.");
                                    userinput = input.nextInt();
                                }

                                //if taxi selected then update destination and status
                                if(userinput == 2){
                                    companies[tempcompanytaxi].Taxis[temptaxi].setDestination(customerDestination);
                                }

                            }


                        }
                    } else {
                        System.out.println("There are currently no companies registered with EZCab.");
                    }
                    break;
                case 4:
                    //case for vehicles to arrive at next location, parses arrays and runs arrived method
                    if(companies != null) {
                        for (int i = 0; i < companies.length; i++) {
                            if (companies[i].Shuttles != null) {
                                for (int j = 0; j < companies[i].Shuttles.length; j++) {
                                    companies[i].Shuttles[j].arrived();
                                }
                            }
                            if (companies[i].Taxis != null) {
                                for (int j = 0; j < companies[i].Taxis.length; j++) {
                                    status = companies[i].Taxis[j].getstatus(customerDestination);
                                    if(status.equals("Booked")){
                                        companies[i].Taxis[j].arrived();
                                    }
                                }
                            }
                        }
                    }



                    break;
                case 5:
                    break;
            }
            //recall menu until input of 5
            System.out.println("---------------------------------------------------------------------");
            System.out.println("Please select a new option:");
            System.out.println("1.) Add a company to the register.");
            System.out.println("2.) Check the status of a Taxi or Shuttle.");
            System.out.println("3.) Book a Taxi or Shuttle.");
            System.out.println("4.) Wait for Vehicles to Arrive at Destination");
            System.out.println("5.) Exit program.");
            userinput = input.nextInt();
        }


    }
}
