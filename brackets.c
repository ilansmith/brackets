#include <stdlib.h>
#include <stdio.h>

struct bracket {
	struct bracket *prev;
	struct bracket *next;
	char open;
};

static int blk_open(char sym)
{
	return sym == '(' || sym == '[' || sym == '{';
}

static char match_close(char sym)
{
	return sym == ')' ? '(' : sym == ']' ? '[' : sym == '}' ? '{' : 0;
}

static int check(char *text)
{
	struct bracket *list = NULL, *cur;
	int ret = -1;

	for (cur = list; *text; text++) {
		char open;

		if (blk_open(*text)) {
			if (cur == list) {
				if (!(cur = (struct bracket *)
					calloc(1, sizeof(struct bracket)))) {
					goto Exit;
				}
				cur->next = list;
				if (list)
					list->prev = cur;
				list = cur;
			} else {
				cur = cur->prev;
			}
			cur->open = *text;
		} else if ((open = match_close(*text))) {
			if (!cur || open != ((struct bracket *)cur)->open)
				goto Exit;
			cur = cur->next;
		}
	}

	ret = 0;

Exit:
	while (list) {
		cur = list;
		list = list->next;
		free(cur);
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

