#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uci.h>

static struct uci_context *ctx = NULL;

void help(void)
{
	printf("Usage:\n");
	printf("  load_config [config_dir]\n");
}

void show_option(struct uci_section *section)
{
	struct uci_element *e;
	struct uci_option *o;

	uci_foreach_element(&section->options, e) {
		o = uci_to_option(e);
		printf("\t%s.%s = %s\n", o->section->e.name, o->e.name, o->v.string);
	}
}

void show_section(struct uci_package *pkg)
{
	struct uci_element *e;
	struct uci_section *s;

	uci_foreach_element(&pkg->sections, e) {
		s = uci_to_section(e);
		printf("%s.%s = %s\n", s->package->e.name, s->e.name, s->type);
		show_option(s);
	}
}

int main(int argc, char *argv[])
{
	char config_dir[128] = {0};
	struct uci_package *pkg = NULL;
	int result;

	if (argc >= 2)
	{
		sprintf(config_dir, "%s", argv[1]);
	}

	ctx = uci_alloc_context();

	if (strlen(config_dir) != 0)
	{
		uci_set_confdir(ctx, config_dir);
	}

	result = uci_load(ctx, "phonebook", &pkg);

	show_section(pkg);

	uci_unload(ctx, pkg);

	uci_free_context(ctx);

	return 0;
}
