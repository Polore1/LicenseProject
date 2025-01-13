# Autonomous Navigation Robot with Artificial Intelligence  

This project focuses on developing an autonomous robot capable of navigating through a maze using artificial intelligence and ultrasonic sensors. The robot was built using an Arduino Nano development board and programmed through the Arduino IDE to execute its navigation and decision-making functionalities.  

## Documentation  
For an in-depth explanation of the project's design, implementation, and results, please refer to the detailed documentation:  
[**Licenta_Rebeca_Polocoser.pdf**](path/to/Licenta_Rebeca_Polocoser.pdf)  

## Features  
- **Ultrasonic Sensors for Obstacle Detection**:  
  The robot uses two ultrasonic sensors to detect obstacles in front and on the left side, ensuring safe navigation through the maze.  

- **Grid-Based Navigation Algorithm**:  
  The maze is represented as a matrix, where rows are indexed as `x` and columns as `y`. The robot marks its path by updating the matrix with `1` (SET) for traversed positions, while unvisited cells remain `0` (UNSET).  

- **Cardinal Direction Movement**:  
  Movement directions (North, West, South, East) are implemented using an enumerated `direction` variable. Depending on the robot’s surroundings, it updates its direction to move forward, turn left, right, or backtrack.  

- **Dynamic Path Optimization**:  
  During the first traversal, the robot identifies the shortest path to the maze exit. This path can later be replayed for faster traversal.  

## Technical Implementation  
### Pin Configuration  
- **Output Pins**:  
  - Two `trig` pins for ultrasonic sensors.  
  - Four motor driver pins.  
- **Input Pins**:  
  - Two `echo` pins for ultrasonic sensors.  
- All pins are initialized to `LOW` to ensure motors and lights are inactive at startup.  

### Main Loop Logic  
The robot continuously reads sensor values and checks if the current cell is open or blocked. Based on sensor feedback:  
- It moves forward if no obstacles are detected.  
- It turns left if the left sensor detects an open path.  
- It turns right in case of dead ends.  

### Matrix Navigation  
Position updates in the matrix are calculated using `xMove` and `yMove`, adjusted dynamically based on the robot's current direction.  

## Future Improvements  
- Add a button to toggle between learning mode (maze exploration) and playback mode (path replay).  
- Optimize traversal by enabling diagonal moves at intersections.  
- Integrate additional sensors for enhanced obstacle detection or a melodic buzzer for audience engagement.  
- Allow reverse traversal from the maze's end to its starting point.  

## Conclusion  
This project demonstrates the potential of autonomous robots in navigating complex paths and showcases the integration of robotics, algorithms, and artificial intelligence. With further enhancements, it can be applied in education, research, or even industrial automation.  

## How to Run the Code  
1. **Hardware Setup**:  
   Connect the ultrasonic sensors, motors, and Arduino Nano as per the circuit diagram provided.  

2. **Upload the Code**:  
   Use the Arduino IDE to upload the program to the Arduino Nano.  

3. **Test the Robot**:  
   Place the robot at the maze's starting point, and observe its autonomous navigation.  

## Gallery  
![Robot](path/to/image)  


Note: Feel free to contribute to this project or report issues in the repository.  
