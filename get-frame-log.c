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

/*********** FLAGS *********************/
typedef struct can_frame can_frame_t;
uint8_t TIME_TO_READ = 0;
uint8_t ERROR_FILE_DESCRIPTOR_SET = 0;
uint8_t WAITING_CAN_FRAME = 0;

/*********** FUNCTIONS ******************/
/*!
 * @brief Creates a virtual socket with the name of 'virtual_socket'
 * @return Returns 0 if the socket was created successfully, otherwise, returns 1
 */
uint8_t create_virtual_socket(void)
{
    int check_return;
    char *VIRTUAL_SOCKET_NAME = "virtual_socket";
    const uint8_t LINUX_COMMAND_MAX_LEN = 100;
    char linux_command[LINUX_COMMAND_MAX_LEN];

    // Commands to create a virtual socket on kernel linux
    strcpy(linux_command, "sudo modprobe vcan");
    check_return = system(linux_command);
    sprintf(linux_command, "sudo ip link add dev %s type vcan", VIRTUAL_SOCKET_NAME);
    check_return = system(linux_command);
    sprintf(linux_command, "sudo ip link set up %s", VIRTUAL_SOCKET_NAME);
    check_return = system(linux_command);

    if (check_return == 0)
    {
        printf("Created virtual module, with name of %s", VIRTUAL_SOCKET_NAME);
        return 0;
    }
    else
    {
        printf("Error creating virtual module");
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
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
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

can_frame_t get_frame_data(int sock, int reading_watcher)
{
	// Read a frame
	//int nbytes;
	can_frame_t frame; 
	if(reading_watcher == -1)
	{
		frame.can_id = -1;
		return frame;
	}
	else if(reading_watcher == 0)
	{
		frame.can_id = -2;
		return frame;
	}
	else
	{
		read(sock, &frame, sizeof(can_frame_t));
		return frame;
	}
}
 
 /*!
 * @brief A debug to check the data stored in the can_frame
 * @param[in] frame The can frame
 * @return Returns 0 if it shows the data successfully, returns 1 otherwise.
 */
 uint8_t debugCAN(can_frame_t frame)
{ 
	int i;
	if(frame.can_id == -1)
	{
		printf("ERRO\n");
		return 1;
	}
	else if(frame.can_id == -2)
	{
		printf("Waiting Data \n");
		return 2;
	}
	else
	{
		printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);
		for (i = 0; i < frame.can_dlc; i++)
			printf("%02X ",frame.data[i]);
		printf("\r\n");
		return 0;
	}
}

/*!
 * @brief Close the virtual socket from the linux device list.
 * @return The status of remove socket. 0 if removed with success, otherwise, returns 1 if not succefull.
 */
uint8_t close_socket(void)
{
	// To check the return value of system function
    int check_return;
    // Var to store the command in linux terminal.
    char command[100];
	// send a command string to 'command' var
    strcpy(command, "sudo modprobe -r vcan");
    // set system returns on check_return
    check_return = system(command);

    if (check_return == 0)
    {
        printf(" Virtual device removed\n ");
        return 0;
    }
    else
    {
        printf(" Error removing virtual device \n ");
        return 1;
    }
}

/*!
 * @brief Checks for data on socket based on time set to 50 milliseconds.
 * @param[in] socket is the socket from which to get the data.
 * @return In case of success, returns the data generated on the socket, in case of error, returns the error code,
 * -1 for reading error, -2 for timeout.
 */
int timer_routine_service_int(int socket)
{
    const int ERROR = -1;
    const int WAITING_DATA = 0;
    const int READY_TO_READ = 1;
    // timeout treatment flag
    int socket_watcher;
    
    struct pollfd event_test[1];
    event_test[0].fd = socket;
    event_test[0].events = POLLIN;
    event_test[0].revents = POLLIN;
    
    socket_watcher = poll(event_test,1,1000);
    
    if(socket_watcher == -1)
        return ERROR;
    else if(socket_watcher == 0)
        return WAITING_DATA;
    else
        return READY_TO_READ;
}

/*!
 * @brief Read the can_frame from the 'virtual_socket' and returns that same can_frame
 * @param[in] s The virtual_socket
 * @return Returns the can_frame structure with the stored data,otherwise, the value of -1 
 * will return in can.id, reporting a reading error.
 */
can_frame_t get_frame_data(int s)
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
		printf("function read() in get_frame_data returns a erro");
		return 1;
	}
	else
	{
		int i;
		printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);

		for (i = 0; i < frame.can_dlc; i++)
			printf("%02X ",frame.data[i]);

		printf("\r\n");
		return 0;
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
		printf(" Erro ao ler o arquivo \n");
		return 1;
	}
	else 
	{
		do
		{
			fgets(line, MAX_LINE_LEN,read_log);
			printf("%s", line);
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
