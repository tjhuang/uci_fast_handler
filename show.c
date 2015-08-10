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
	printf("  show [config_dir]\n");
}

int main(int argc, char *argv[])
{
	char query_buff[256] = {0};
	char config_dir[128] = {0};
	char *s;

	if (argc >= 2)
	{
		sprintf(config_dir, "%s", argv[1]);
	}

	ctx = uci_alloc_context();

	if (strlen(config_dir) != 0)
	{
		uci_set_confdir(ctx, config_dir);
	}

	sprintf(query_buff, "phonebook.Ben.phone");
	s = lc_uci_get(query_buff);
	if (s)
	{
		printf("Get Ben's phone: %s\n", s);
	}

	sprintf(query_buff, "phonebook.Ben.phone=%s", "+886-123-456-789");
	lc_uci_set(query_buff);

	sprintf(query_buff, "phonebook.Ben.phone");
	s = lc_uci_get(query_buff);
	if (s)
	{
		printf("Ben's phone number is changed into: %s\n", s);
	}

	uci_commit(ctx, &ptr.p, false);

	uci_free_context(ctx);

	return 0;
}
