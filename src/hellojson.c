#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

char buffer[10000];

int main()
{
	FILE * jsonfile = fopen("./json.txt", "r");
	if (jsonfile == NULL)
		exit(1);
	if (fread(buffer,1,10000,jsonfile) == 0)
		exit(1);
	
	cJSON *json = cJSON_Parse(buffer);
	if (monitor_json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			fprintf(stderr, "Error before: %s\n", error_ptr);
		exit(1);
	}
	
	return 0;
}

