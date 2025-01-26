## Summary
The goal of this project was to explore and implement robot system that are capable of travelling indoors and being aware of its own locations so that it can be used for robot formational travelling system development. 

The focus of the project focused on was implementing UWB-based localization. By utilizing one UWB tag placed on the robot and three fixed UWB anchors in the environment, the system measured distances to the anchors and employed triangulation to calculate the robot’s exact position. Testing of the UWB system showed that the system is reasonably accurate for distances up to 6 meters, with an error margin of up to 30 cm at greater distances and under 10 cm for shorter ranges. Such precision makes UWB localization system to be suitable for indoor applications where GPS is not reliable due to the presence of obstacles or its remote locations. 

Another experiments were done to test the accuracy of the triangulation method used in the system. Although raw data cannot be provided due to confidentiality, these experiments confirmed the reliability of the UWB localization system in determining the robot’s position.

Components like the Nucleo F411RE microcontroller, motor drivers, and an 11.1V LiPo battery, which provided power for the system, were used for the hardware. The hardware performed reliably during testing, although proper voltage regulation needs to be ensured to prevent potential damage to the microcontroller due to excessive voltage. 

Formational control, which is the ability of multiple robots to maintain coordinated movement, was not fully implemented due to time constraints, but the groundwork has been laid with a reliable localization system in place. Future work can focus on developing a formational control algorithm and enhancing communication between robots to enable real-time change of the formation. Additionally, the integration of obstacle detection and avoidance algorithms will improve the reliability of the system in environments that are unpredictable.

In summary, this project successfully established the foundations for a mobile robot system capable of precise localization and lays the groundwork for future development of fully autonomous, coordinated robot formations.

## Key Achievements: 
• Implemented an indoor UWB-based localization system with triangulation for synchronized formational traveling of multiple robots, achieving range accuracy of 10cm.
• Enabled real-time remote control of the robot by implementing an HTTP-based web server and integrated DWM1000 UWB board and internet module over UART
