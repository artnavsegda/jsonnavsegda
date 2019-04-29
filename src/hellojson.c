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
cJSON * pricelines = NULL;

bool loadPricesFromFile(const char * fname)
{
	FILE * jsonfile = fopen(fname, "r");
	if (jsonfile == NULL)
		return false;
	if (fread(buffer,1,10000,jsonfile) == 0)
		return false;

	pricelines = cJSON_Parse(buffer);
	if (pricelines == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			fprintf(stderr, "Error before: %s\n", error_ptr);
		return false;
	}
	return true;
}

bool GetNumPricesInPricelist(uint8_t priceListIndex, uint8_t * numPrices)
{
	*numPrices = cJSON_GetArraySize(pricelines);
}

//наркомания ебаная но ладно
uint8_t GetPricelistsNum(void)
{
	if (pricelines == NULL)
		return 0;

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
		priceindex = cJSON_GetArrayItem(priceline,0);
		if (priceindex->valueint == itemIndex)
		{
			pricevaluetmp = cJSON_GetArrayItem(priceline,priceListIndex);
			*priceValue = pricevaluetmp->valueint;//valuedouble should be actually
			return true;
		}
	}
	return false;
}

int main(int argc, char *argv[])
{
	uint32_t priceline;

	loadPricesFromFile(argv[1]);

	unsigned char numpricelists = GetPricelistsNum();
	printf("number of pricelists is %d\n", numpricelists);
	unsigned char numpricelines;
	GetNumPricesInPricelist(0, &numpricelines);
	printf("number of pricelines is %d\n", numpricelines);

	for (int i = 1; i <= numpricelists; i++)
	{
		printf("Pricelist %d: ", i);
		for (int y = 1; y <= 100; y++)
			if (GetPrice(i, y, &priceline) == true)
				printf("price %d = %d, ", y, priceline);
		printf("\n");
	}

	return 0;
}

