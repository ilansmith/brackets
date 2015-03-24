#include <stdlib.h>
#include <stdio.h>

struct bracket {
	struct bracket *next;
	char open;
};

static char blk_open(char sym)
{
	return sym == '(' || sym == '[' || sym == '{';
}

static char brk_close(char sym)
{
	return sym == ')' ? '(' : sym == ']' ? '[' : sym == '}' ? '{' : 0;
}

static int check(char *text)
{
	struct bracket *list = NULL, *tmp;
	int ret = 0;

	for ( ; *text; text++) {
		char open;

		if (blk_open(*text)) {
			if (!(tmp = (struct bracket *)
				malloc(sizeof(struct bracket)))) {
				ret = -1;
				goto Exit;
			}

			tmp->open = *text;
			tmp->next = list;
			list = tmp;
			continue;
		}

		if ((open = brk_close(*text))) {
			if (!list || open != list->open) {
				ret = -1;
				goto Exit;
			}

			tmp = list;
			list = list->next;
			free(tmp);
		}
	}

Exit:
	while (list) {
		tmp = list;
		list = list->next;
		free(tmp);
	}

	return ret;
}

int main(int argc, char **argv)
{
	char *strings[] = {
		"a(b)",
		"[{}]",
		"[(]",
		"}{",
		"z([{}-()]{a})",
		"",
		NULL
	};
	char **str = strings;

	while (*str) {
		printf("check(\"%s\") -> %s\n", *str, check(*str) ?
			"false" : "true");
		str++;
	}

	return 0;
}

