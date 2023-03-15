# FireSystem
The system consist of master and slave
The master have a password to log in ,it's cahangable as it save the password in the EEPROM ,when the user enter the password he/she has 2 options 
Change Password    
- Config
The config option make the master mcu to take the heat and smoke configuration and send it back to the slave mcu to work upon it
The slave is resonsible for sensors reading and showing it on Lcd <br />
There's 3 state : 
- Fine state   
- Heat State   
- Fire state 
if the system enters the fire state ,the slave mcu turn on the motor and get locked and send external interrupt to the master then the master tell the user that there's a fire but the system is nonreversable so  Puting out the fire the user needs to enter the password again to unlock the system
