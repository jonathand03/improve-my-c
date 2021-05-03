/* 
I'm still learning how to improve the sending
of commands securely. So, please if you have any tips, 
don't hold back to tell me :)
*/



/* libs needed to create and read socket */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
/*--------------------------------------*/

/*!
 * @brief Creates a virtual socket with the name of 'virtual_socket'
 * @return Returns 0 if the socket was created successfully, otherwise, returns 1
 */
uint8_t create_virtual_socket(void)
{
    int check_return ;
    char *VIRTUAL_SOCKET_NAME = "virtual_socket";
    const uint8_t LINUX_COMMAND_MAX_LEN = 100;
    char linux_command[LINUX_COMMAND_MAX_LEN];

	// Commands to create a virtual socket on kernel linux	
	strcpy(linux_command, "sudo modprobe vcan");
	check_return = system(linux_command);
	sprintf(linux_command,"sudo ip link add dev %s type vcan", VIRTUAL_SOCKET_NAME);
	check_return = system(linux_command);
	sprintf(linux_command,"sudo ip link set up %s", VIRTUAL_SOCKET_NAME);
	check_return = system(linux_command);

	if(check_return == 0)
    {
        debug(" Created virtual module, with name of %s \n", VIRTUAL_SOCKET_NAME);
        return 0;
    }
    else
    {   
        log_err(" \n Error creating virtual module \n");
        return 1;
    }
}

/*!
 * @brief prepares the virtual socket for reading data
 * @return returns the socket with its settings to initialize the reading
 */
int open_virtual_socket(void)
{
    char *VIRTUAL_SOCKET_NAME = "virtual_socket";                                
    // Opening and binding to a can socket
    int s;   
    // Verify if socket exist                                       
    if((s = socket(PF_CAN,SOCK_RAW,CAN_RAW)) < 0)
    {
        perror("Socket");
        return 1;
    }
    // Create a data frame struct to store data of 'cansend'
    struct ifreq ifr;
    // Copy the name to frame struct
    strcpy(ifr.ifr_name, VIRTUAL_SOCKET_NAME); 
    // control of socket
    ioctl(s, SIOCGIFINDEX, &ifr);

    struct sockaddr_can addr;
    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        perror("Bind");
        return 1;
    }
    else
    {
        return s;
    }                     
}

/*!
 * @brief Read the can_frame from the 'virtual_socket' and returns that same can_frame
 * @param[in] s The virtual_socket
 * @return Returns the can_frame structure with the stored data,otherwise, the value of -1 
 * will return in can.id, reporting a reading error.
 */
can_frame get_frame_data(int s)
{
    // Read a frame
    int nbytes;
    can_frame frame;  
    nbytes = read(s, &frame, sizeof(struct can_frame));

    if (nbytes < 0) 
    {
		frame.can_id = -1;
    }
	return frame;
}

/*!
 * @brief A debug to check the data stored in the can_frame
 * @param[in] frame The can frame
 * @return Returns 0 if it shows the data successfully, returns 1 otherwise.
 */
uint8_t debugCAN(can_frame frame)
{ 
	if(frame.can_id  == -1)
	{
		log_err("function read() in get_frame_data returns a erro");
		return 1;
	}
	else
	{
		int i;
		debug("0x%03X [%d] ",frame.can_id, frame.can_dlc);

		for (i = 0; i < frame.can_dlc; i++)
			debug("%02X ",frame.data[i]);

		printf("\r\n");
		return 0;
	}
}

/*!
 * @brief Get the pgn with frequency filter from a can frame
 * @param[in] frame The can frame
 * @param[in] pgn The pgn
 * @return The pgn after a certain time
 */
uint8_t close_socket(void)
{
    int check_return;
	char command[100];

	strcpy(command, "sudo modprobe -r vcan");
	check_return = system(command);

    if(check_return == 0)
    {
        debug(" Virtual device removed ");
        return 0;
    }
    else
    {
        debug(" Error removing virtual device ");
        return 1;
    }
}

/*!
 * @brief Reads all frames within the ".log" file
 * @param[in] log_dir Directory where the file is.
 * @return If the reading is successful, return 0 otherwise it will return 1
 */
uint8_t read_frame_log(char *log_dir)
{
	FILE *read_log;
	const int MAX_LINE_LEN = 47;
	char line[MAX_LINE_LEN];
	
	read_log = fopen(log_dir,"r");
	if ( read_log == NULL)
	{
		log_err(" Erro ao ler o arquivo \n");
		return 1;
	}
	else 
	{
		do
		{
			fgets(line, MAX_LINE_LEN,read_log);
			debug("%s", line);
		}while(!feof(read_log));

		fclose(read_log);
		return 0;
	}
}

/*!
 * @brief  Create a standard file name called 'frame.log'
 * @return Returns the name fram.log to be used by the open file function
 */
const char *create_log_dir(void)
{
	return "frame.log";	
}

void create_fisic_soc(void)
{

}
