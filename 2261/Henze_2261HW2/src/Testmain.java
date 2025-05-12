//Adam Henze
//Java 2261
//Laika Satish
// 13th February 2023
//HW2

//Main Program
public class Testmain {
    public static void main(String args[]){
        //creates new queue obj
        Queue newqueue = new Queue();

        //begin population
        System.out.println("Creating and printing Queue, first to last...");
        //for loop to incrementally add integers into queue
        for(int i = 0; i < 15; i++)
        {
            //print integers and add to queue
            System.out.print((i +1) + " ");
            newqueue.enqueue(i+1);
        }
        System.out.println("\nThe queue is now size:");
        System.out.println(newqueue.getSize());
        //begin dequeue and print
        System.out.println("\nPrinting and dequeueing Queue, in order of first-in-first-out...");

        //check for true or false values of queue being empty
        //print value at first posistion in queue if not empty
        while(!newqueue.empty())
        {
            System.out.print(newqueue.dequeue() + " ");
        }
        System.out.println("\nThe queue is now size:");
        System.out.println(newqueue.getSize());
        //End main program
    }
}