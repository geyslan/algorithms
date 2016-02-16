#define CMDS		100
#define CMDFIELDS	2

static char *app_name;
extern char *app_cmds[][CMDFIELDS];

static void print_usage()
{
        printf("Usage:\n");
        for (int i = 0; i < CMDS && app_cmds[i][0]; ++i) {
		printf("%s", app_name);
                printf(" %d %s\t%s\n", i, app_cmds[i][0], app_cmds[i][1]);
	}
}