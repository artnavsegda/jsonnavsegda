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
cJSON * pricelines;

bool loadPricesFromFile(const char * fname)
{
	FILE * jsonfile = fopen("./json.txt", "r");
	if (jsonfile == NULL)
		exit(1);
	if (fread(buffer,1,10000,jsonfile) == 0)
		exit(1);

	pricelines = cJSON_Parse(buffer);
	if (pricelines == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			fprintf(stderr, "Error before: %s\n", error_ptr);
		exit(1);
	}
}

bool GetNumPricesInPricelist(uint8_t priceListIndex, uint8_t * numPrices)
{
	*numPrices = cJSON_GetArraySize(pricelines);
}

//наркомания ебаная но ладно
uint8_t GetPricelistsNum(void)
{
	uint8_t pricelistnum;
	cJSON * priceline = NULL;
	cJSON_ArrayForEach(priceline, pricelines)
	{
		pricelistnum = cJSON_GetArraySize(priceline);	
	}
	return pricelistnum - 1;
}

//почему блять pricevalue uint32 а не double а а а а
bool GetPrice(uint8_t priceListIndex, uint8_t itemIndex,uint32_t * priceValue)
{
	cJSON * priceline = NULL;
	cJSON * priceindex = NULL;
	cJSON * pricevaluetmp = NULL;
	cJSON_ArrayForEach(priceline, pricelines)
	{
		priceindex = cJSON_GetArrayItem(priceline,1);//или 2 ?
		if (priceindex->valueint == itemIndex)
		{
			pricevaluetmp = cJSON_GetArrayItem(priceline,itemIndex+1);
			*priceValue = pricevaluetmp->valueint;//valuedouble should be actually
			return true;
		}
	}
	return false;
}

int main()
{
	/*cJSON * priceline = NULL;
	FILE * jsonfile = fopen("./json.txt", "r");
	if (jsonfile == NULL)
		exit(1);
	if (fread(buffer,1,10000,jsonfile) == 0)
		exit(1);

	pricelines = cJSON_Parse(buffer);
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
	}*/

	loadPricesFromFile("./json.txt");
	printf("number of pricelists is %d\n", GetPricelistsNum());
	unsigned char numprices;
	GetNumPricesInPricelist(0, &numprices);
	printf("number of pricelines is %d\n", numprices);

	return 0;
}
