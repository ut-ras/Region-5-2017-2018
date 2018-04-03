


import com.fazecast.jSerialComm.*;
//import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import javafx.application.Application; 
import javafx.scene.Group; 
import javafx.scene.Scene; 
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;  
import javafx.scene.text.Font; 
import javafx.scene.text.Text; 
import javafx.collections.ObservableList; 
import javafx.stage.Stage; 
//import javafx.scene.input.MouseEvent; 
import static javafx.application.Application.launch; 
import javafx.scene.control.Button;
import javafx.event.EventHandler;
import java.io.BufferedReader;
import javafx.application.Platform;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.control.TextField; 
import javafx.scene.input.KeyEvent;
import javafx.event.ActionEvent;
import java.io.OutputStream;
import java.io.IOException;
//import javax.comm.*;

/**
 *
 * @author Jacqueline Deans
 */
public class Robot_GUI extends Application {

    int[] tokenInventory = new int[8]; // red, green, blue, cyan, magenta, yellow, grey, unknown
    int tokenTotal = 0;
    
    ArrayList<String> path = new ArrayList<>();
    
    Text[] texts = new Text[10];
    
    // not really necessary
    int[][] boxCoordinates = { {20,20}, // red
                               {20,235}, // green
                               {20,450}, // blue 
                               {450,20}, // cyan
                               {450,235}, // magenta
                               {450,450}, // yellow
                               
                               {235,235}, // grey
                               {235,20}, // top white
                               {235,450} }; // bottom white
    
    
    int increment = 31;
   
    // huge layout map, used to determine direction
    String[][] grid = { {"R0",   "",   "",   "",   "",   "", "TW",  "",   "",   "",   "",   "", "C0"},
                        {""  , "R1",   "",   "",   "",   "",   "",  "",   "",   "",   "", "C1",   ""},
                        {""  ,   "", "R2",   "",   "",   "",   "",  "",   "",   "", "C2",   "",   ""},
                        {""  ,   "",   "", "R3",   "",   "",   "",  "",   "", "C3",   "",   "",   ""},
                        {""  ,   "",   "",   "", "R4",   "",   "",  "", "C4",   "",   "",   "",   ""}, 
                        {""  ,   "",   "",   "",   "", "R5",   "","C5",   "",   "",   "",   "",   ""},
                        {"G0", "G1", "G2", "G3", "G4", "G5",  "X","M5", "M4", "M3", "M2", "M1", "M0"}, 
                        {""  ,   "",   "",   "",   "", "B5",   "","Y5",   "",   "",   "",   "",   ""},                       
                        {""  ,   "",   "",   "", "B4",   "",   "",  "", "Y4",   "",   "",   "",   ""}, 
                        {""  ,   "",   "", "B3",   "",   "",   "",  "",   "", "Y3",   "",   "",   ""},
                        {""  ,   "", "B2",   "",   "",   "",   "",  "",   "",   "", "Y2",   "",   ""},
                        {""  , "B1",   "",   "",   "",   "",   "",  "",   "",   "",   "", "Y1",   ""},
                        {"B0",   "",   "",   "",   "",   "",  "BW",  "",   "",   "",   "",   "","Y0"}    };
    
    
    int[][] intersectionStarts = {  {50,50}, // red
                                    {50, 235}, // green
                                    {50, 420}, // blue
                                    {420, 50}, // cyan 
                                    {420, 235}, // magenta
                                    {420, 420}, // yellow
    };
    
    @Override
    public void start(Stage primaryStage) throws IOException {
      
        //Scanner scan = new Scanner(new File ("data.in"));
        ImageView robot = initRobot();
        
        //String portName = "/dev/cu.usbserial-A6028U2C";
        
        ImageView background = loadBackground();
      
        Group root = new Group(background);  

        ObservableList list = root.getChildren();
        setText(list);

        Text commandInstr = new Text();
        // enum Commands{FWD1, FWD2, FWD3, BACK1, BACK2, BACK3, FWDNOLINE, LEFTIP, RIGHTIP, LEFT45, LEFT90, LEFT135, LEFT180, RIGHT45, RIGHT90, RIGHT135, RIGHT180, STOP};
        commandInstr.setText("Type a number to send the command over Serial");
        commandInstr.setX(520);
        commandInstr.setY(440);
        list.add(commandInstr);
       

        SerialPort serialPort = initPort();

//        
//        EventHandler<MouseEvent> eventHandler = new EventHandler<MouseEvent>() { 
//            @Override 
//            public void handle(MouseEvent e) { 
//                if (scan.hasNext()) {
//                    String command = scan.nextLine();
//                    parseCommand(command, robot, list);
//                    list.clear();
//                    setText(list);
//                    list.add(background);
//                    list.add(robot);
//                    list.add(pathToText());
//                    
//                    if (path.size() == 1) 
//                        list.add(getDirection("TW", path.get(0)));
//                    else
//                        list.add(getDirection(path.get(path.size()-2), path.get(path.size()-1)));
//                   
//                }
//                else {
//                    System.out.println("NO MORE COMMANDS");
//                }
//             } 
//        };

        TextField textField = new TextField();
        textField.setLayoutX(520); 
        textField.setLayoutY(460);
        list.add(textField);

        Button sendButton = new Button("Send");
        sendButton.setLayoutX(700);
        sendButton.setLayoutY(460);
        sendButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override 
            public void handle(ActionEvent e)  {
                int command = Integer.parseInt(textField.getText());

                try(OutputStream out = serialPort.getOutputStream()) {
                    out.write(command);
                }
                catch (Exception ex) {
                    ex.printStackTrace();
                }
                textField.clear();
            }
        });
        list.add(sendButton);

        list.add(robot);
        
        serialPort.addDataListener(new SerialPortPacketListener() {
            @Override
            public int getListeningEvents() { return SerialPort.LISTENING_EVENT_DATA_RECEIVED; }
            
            @Override
            public int getPacketSize() { return 6; }
          
           @Override
           public void serialEvent(SerialPortEvent event)
           {             
                byte[] newData = event.getReceivedData();

                System.out.println("\nPACKET READ: " + newData.length);
                StringBuilder str = new StringBuilder();
                for (int i = 0; i < newData.length; ++i) {
                      System.out.print((char)newData[i]);
                      str.append((char)newData[i]);
                }
                System.out.println();
                
                String command = str.toString();
                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        newParseCommand(command, robot, list);
                        list.clear();
                        setText(list);
                        list.add(background);
                        list.add(robot);
                        list.add(pathToText());
                        list.add(sendButton);
                        list.add(textField);
                        list.add(commandInstr);
                        if (path.size() == 1) 
                            list.add(getDirection("BW", path.get(0)));
                        else
                            list.add(getDirection(path.get(path.size()-2), path.get(path.size()-1)));
                        }
                 });           
            }
        });
            
        


//        background.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler); 
//        background.addEventFilter( SerialPort.LISTENING_EVENT_DATA_RECEIVED, SerialPortEvent); 
        Scene scene = new Scene(root, 1000, 600);  
        
        //Setting title to the Stage 
        primaryStage.setTitle("Robot GUI");  
     
        //Adding scene to the stage 
        primaryStage.setScene(scene);
      
        //Displaying the contents of the stage 
        primaryStage.show();
      
    }
    
    // Determine the direction in which the robot is facing if it has moved from node1 to node2
    private Text getDirection (String node1, String node2) {
        int[] coord1;
        
        coord1 = getLayoutCoordinates(node1);
        
        int[] coord2 = getLayoutCoordinates(node2);
        String direction = "";
        
        if (coord1[0] < coord2[0])
            direction += "S";
        if (coord1[0] > coord2[0])
            direction += "N";
        
        if (coord1[1] < coord2[1])
            direction += "E";
        if (coord1[1] > coord2[1])
            direction += "W";
        
        Text dirText = new Text("Direction: " + direction);
        dirText.setFont(Font.font("verdana", FontWeight.BOLD, FontPosture.REGULAR, 20));
        dirText.setX(520);
        dirText.setY(350);
        return dirText;
    }
    
    private int[] getLayoutCoordinates (String node) {
        
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[0].length; c++) {
                if (grid[r][c].equals(node))
                    return new int[] {r, c};
            
            }
        }
        return new int[] {-1, -1};
    }
    
    private Text pathToText() {
        StringBuilder str = new StringBuilder();
        str.append("Nodes Visited: [ ");
        for (int i = 0; i < path.size()-1; i++) {
            str.append(path.get(i));
            str.append("--");
            if (i % 20 == 0 && i > 0)
                str.append("\n");
        }
        str.append(path.get(path.size()-1));
        str.append(" ]");
        String pathString = str.toString();
        
        Text pathText = new Text(pathString);
        pathText.setX(30);
        pathText.setY(520);
        return pathText;
    }
    
    /* <name:visited:tokenColor>
       <R1:t:R>
    */
    private void newParseCommand (String command, ImageView robot, ObservableList list) {
        char color = command.charAt(0);
        char depth = command.charAt(1);
        
        String node = color + "" + depth;
        
        path.add(node);
        moveToIntersection(node, robot);
        System.out.println("Moved to " + node);
        
        char tokenColor = command.charAt(5);
        
        int tokenIndex = colorToIndex(tokenColor);
        tokenInventory[tokenIndex]++;
        tokenTotal++;
        System.out.println("Picked up token color " + tokenColor);
    }
    
    
    private ImageView initRobot() {
        ImageView robot = new ImageView(new Image("file:../reddot.png"));
        
        robot.setFitHeight(30); 
        robot.setFitWidth(30);
        
        robot.setPreserveRatio(true);
        
        int[] coordinates = boxCoordinates[colorToIndex('B')];
        robot.setX(coordinates[0]);
        robot.setY(coordinates[1]);
        
        return robot;
    }
    
    private void moveToIntersection (String node, ImageView robot) {
        char color = node.charAt(0);
        int depth = 0;
        if (!node.substring(1).equals("B"))
            depth = Integer.parseInt(node.substring(1));
        int x = intersectionStarts[colorToIndex(color)][0], y = intersectionStarts[colorToIndex(color)][1];
        //depth -= 1;
        if (depth == 0)
            depth = -1;
        
        if (color == 'R'){
            x += increment * depth;
            y += increment * depth;
        }
        if (color == 'G') {
            x += increment * (depth);
        }
        if (color == 'B'){
            x += increment * depth;
            y -= increment * depth;
        }
        if (color == 'C'){
            x -= increment * depth;
            y += increment * depth;
        }
        if (color == 'M') {
            x -= increment * (depth);
        }
        if (color == 'Y'){
            x -= increment * depth;
            y -= increment * depth;
        }
        
        
        robot.setX(x);
        robot.setY(y);
        
    }
    
    private ImageView loadBackground () {
        Image image = new Image("file:../playingfield.png");  
      
      //Setting the image view 
      ImageView imageView = new ImageView(image); 
      
      //Setting the position of the image 
      imageView.setX(0); 
      imageView.setY(0); 
      
      //setting the fit height and width of the image view 
      imageView.setFitHeight(500); 
      imageView.setFitWidth(500); 
      
      //Setting the preserve ratio of the image view 
      imageView.setPreserveRatio(true);  
      
      return imageView;
    }
    
    private void pickupToken (char color) {
        int index = colorToIndex (color);
        tokenInventory[index]++;
        tokenTotal++;
        
    }

    private SerialPort initPort() {
        SerialPort[] ports = SerialPort.getCommPorts();
        System.out.println("Select a port:");
        int i = 1;
        for(SerialPort port : ports)
            System.out.println(i++ +  ": " + port.getSystemPortName());
        Scanner s = new Scanner(System.in);
        int chosenPort = s.nextInt();
        SerialPort serialPort = ports[chosenPort-1];
        if(serialPort.openPort())
                System.out.println("Port opened successfully.");
        else {
                System.out.println("Unable to open the port.");
                return null;
        }

        return serialPort;
    }
    
    private int colorToIndex(char color) {
        int index = -1;
        switch (color) {
            case 'R':
                index = 0;
                break;
            case 'G':
                index = 1;
                break;
            case 'B':
                index = 2;
                break;
            case 'C':
                index = 3;
                break;
            case 'M':
                index = 4;
                break;
            case 'Y':
                index = 5;
                break;
            case 'X':
                index = 6;
                break;
            case 'U':
                index = 7;
                break;   
            default: break;
        }
        return index;
    }
    
    private void setText (ObservableList list) {
        texts[0] = new Text();
        texts[0].setFont(new Font(24));
        texts[0].setText("Token Inventory");
        texts[0].setX(520);
        texts[0].setY(20);

        texts[1] = new Text();
        texts[1].setText("Total:\t" + tokenTotal);
        texts[1].setX(520);
        texts[1].setY(50);

        texts[2] = new Text();
        texts[2].setText("Grey:\t" + tokenInventory[6]);
        texts[2].setX(520);
        texts[2].setY(80);

        texts[3] = new Text();
        texts[3].setText("Red:\t\t" + tokenInventory[0]);
        texts[3].setX(520);
        texts[3].setY(110);

        texts[4] = new Text();
        texts[4].setText("Green:\t" + tokenInventory[1]);
        texts[4].setX(520);
        texts[4].setY(140);

        texts[5] = new Text();
        texts[5].setText("Blue:\t" + tokenInventory[2]);
        texts[5].setX(520);
        texts[5].setY(170);

        texts[6] = new Text();
        texts[6].setText("Cyan:\t" + tokenInventory[3]);
        texts[6].setX(520);
        texts[6].setY(200);

        texts[7] = new Text();
        texts[7].setText("Magenta:\t"+ tokenInventory[4]);
        texts[7].setX(520);
        texts[7].setY(230);

        texts[8] = new Text();
        texts[8].setText("Yellow:\t" + tokenInventory[5]);
        texts[8].setX(520);
        texts[8].setY(260);
        
        texts[9] = new Text();
        texts[9].setText("Unknown: " + tokenInventory[7]);
        texts[9].setX(520);
        texts[9].setY(290);

        list.add(texts[0]);
        list.add(texts[1]);
        list.add(texts[2]);
        list.add(texts[3]);
        list.add(texts[4]);
        list.add(texts[5]);
        list.add(texts[6]);
        list.add(texts[7]);
        list.add(texts[8]);
        list.add(texts[9]);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    

    
}
