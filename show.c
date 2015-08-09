#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uci.h>

static struct uci_context *ctx = NULL;
static struct uci_ptr ptr;

static int lc_uci_set(const char *str)
{
	char *s;
	int ret = UCI_OK;

	s = strdup(str);
	if (uci_lookup_ptr(ctx, &ptr, s, true) != UCI_OK)
	{
		goto ERR_SET;
	}

	ret = uci_set(ctx, &ptr);

ERR_SET:
	free(s);

	return ret;
}

static char *lc_uci_get(const char *str)
{
	struct uci_ptr p;
	char *s;

	s = strdup(str);
	
	if (uci_lookup_ptr(ctx, &p, s, true) != UCI_OK)
	{
		free(s);
		return NULL;
	}

	if (p.o)
	{
		free(s);
		return p.o->v.string;
	}

	return NULL;
}


void help(void)
{
	printf("Usage:\n");
	printf("  show <CMD_FILE>\n");
}

int main(int argc, char *argv[])
{
	char query_buff[256];
	FILE *fp;
	char *s;

/*
	fp = fopen(argv[1], "r");
	if (!fp)
	{
		printf("Can not open file!\n");
		return -1;
	}
*/

	ctx = uci_alloc_context();

	int result = uci_set_confdir(ctx, "/home/jacob/Downloads/uci_fast_handler/test");

	sprintf(query_buff, "phonebook.Ben.phone");
	s = lc_uci_get(query_buff);
	if (s)
	{
		printf("Get Ben's phone: %s\n", s);
	}
/*
	while (fgets(line, 128, fp) != NULL)
	{
		int result;
		char type[8];
		char mac[32];
		char cmd3[32];
		char cmd4[32];
		char cmd5[32];
		char cmd6[32];

		result = sscanf(line, "%s %s %s %s %s %s", type, mac, cmd3, cmd4, cmd5, cmd6);
		format_mac_address(mac);
		if (result == 3 && strcmp(type, "grp") == 0)
		{
			char query_buff[256];
			char *s;
			sprintf(query_buff, "apg_dev.%s_%s.grp", mac, type);
			s = lc_uci_get(query_buff);
			if (s == NULL)
			{
				sprintf(query_buff, "apg_dev.%s_%s=section", mac, type);
				lc_uci_set(query_buff);

				sprintf(query_buff, "apg_dev.%s_%s.grp=-", mac, type);
				lc_uci_set(query_buff);

				sprintf(query_buff, "apg_dev.%s_%s.time=%d:%d,%d:%d,%d:%d,%d:%d,%d:%d,%d:%d,%d:%d", mac, type,
					TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX,
					TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX, TIME_MAX);
				lc_uci_set(query_buff);
			}

			sprintf(query_buff, "apg_dev.%s_%s.grp=%s", mac, type, cmd3);
			lc_uci_set(query_buff);
		}
	}
*/
//	fclose(fp);

	uci_commit(ctx, &ptr.p, false);

	uci_free_context(ctx);

	return 0;
}
