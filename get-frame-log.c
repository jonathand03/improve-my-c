#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



uint8_t read_frame_log(char *log_dir)
{
	FILE *read_log;
	int MAX_LINE_LEN = 30;
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
			/* parametros de tratamento aqui */
			fgets(line,MAX_LINE_LEN,read_log);
			printf("%s", line);
		}while(!feof(read_log));
		
		fclose(read_log);
		return 0;
	}
}

char  *create_doc_log(void)
{
	return "frame.log";	
}

int main(){
	uint8_t check_return;
	check_return = read_frame_log(create_doc_log());
	
	if(check_return == 0)
		printf(" Passou no teste");
	else
		printf("Erro na função");

	return 0;
}
