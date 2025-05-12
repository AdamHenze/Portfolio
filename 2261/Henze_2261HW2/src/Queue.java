//Queue class
public class Queue {

    //declare necessary variables and array space
    private int[] elements;
    private int size;
    public static final int default_capacity = 8;

    //default constructor of size 8
    public Queue()
    {
        this(default_capacity);
    }

    //constructor with size of capacity entered
    public Queue(int capacity){
        elements = new int[capacity];
    }

    //process to enqueue integers
    public void enqueue(int value){
        //if statement to check if size will go beyond scope of array, double size if so
        if (size >= elements.length){
            //new temp size two times original size
            int[] temp = new int[elements.length * 2];
            //copy array elements into temp of new size
            System.arraycopy(elements, 0 , temp, 0, elements.length);
            //set element array to new size of temp w/ copied values
            elements = temp;
        }
        //increment size to check for double on next enqueue
        elements[size++] = value;
    }

    //process to dequeue integers
    public int dequeue()
    {
        //set temp value to current first-in-line value of elements
        int temp = elements[0];
        //for loop to parse through elements array and move values down one array space, moving them 'up' in queue
        for(int i = 0; i < size; i++)
        {
            //set i as the next element
            elements[i] = elements[i + 1];
        }
        //decrement size
        size--;
        //return the temp value of the old elements[0]
        return temp;
    }

    //check for empty
    public boolean empty(){
        return size == 0;
    }

    public int getSize()
    {
        return size;
    }

}