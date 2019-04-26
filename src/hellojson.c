#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

bool GetPrice(uint8_t priceListIndex, uint8_t itemIndex,uint32_t * priceValue);
uint8_t GetPricelistsNum(void);
bool GetNumPricesInPricelist(uint8_t priceListIndex, uint8_t * numPrices);
bool loadPricesFromFile(const char * fname);

char buffer[10000];

int main()
{
	cJSON * priceline = NULL;
	FILE * jsonfile = fopen("./json.txt", "r");
	if (jsonfile == NULL)
		exit(1);
	if (fread(buffer,1,10000,jsonfile) == 0)
		exit(1);

	cJSON * pricelines = cJSON_Parse(buffer);
	if (pricelines == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			fprintf(stderr, "Error before: %s\n", error_ptr);
		exit(1);
	}

	printf ("array size %d\n",cJSON_GetArraySize(pricelines));

	cJSON_ArrayForEach(priceline, pricelines)
	{
		printf ("subarray size %d\n",cJSON_GetArraySize(priceline));
	}

	return 0;
}
