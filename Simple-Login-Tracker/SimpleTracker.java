
/**
 * SimpleTracker 
 * Takes curent time from system
 * 
 * Callum 
 * Version 1.1
     * formatted output string to
 */


// Standard import for the Scanner class
import java.util.Scanner;
import java.util.Date;


import java.io.*;

public class SimpleTracker {
    public static void main (String [] args) throws IOException {
        // Create a Scanner object attached to the keyboard
        //Scanner in = new Scanner (System.in);
        
        //"C:\\callumsJavatests\\Login Tracker\\Simple Login Tracker\\Simple-Login-Tracker\\Simple-Login-Tracker"
        //constructors
        File file = new File("TimeLog.txt");
        FileWriter fw = new FileWriter(file,true);// apenend to file true
        PrintWriter pw = new PrintWriter(fw);
        
        Date date = new Date();
        
        
        // Current milliseconds since UNIX epoch Jan 1 1970
        long totalMilliseconds = System.currentTimeMillis();
        // total seconds
        long totalSecond = totalMilliseconds / 1000;
        long currentSecond = (int) (totalSecond % 60);
        //get total miniutes
        long totalMinute = totalSecond / 60;
        long currentMinute = (int) (totalMinute % 60);
        //get the total hour
        long totalHour = totalMinute/ 60;
        long curentHour = (int) (totalHour % 24 + 6);//add +6 to convert GMT to MST
        
        
                
        
        //Print the current time 
        pw.printf("Current time: %s:%s:%s %n", currentSecond,currentMinute,curentHour);
        pw.println("Current date using a Date objecti is:" + date);
        pw.println();
        
        pw.close();// close print writer
        
        
    }
}
