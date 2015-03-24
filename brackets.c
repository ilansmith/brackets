#include <stdlib.h>
#include <stdio.h>

struct bracket {
	struct bracket *next;
	struct bracket **prev;
	char brc;
};

#define BRC_OPEN(sym) ((sym) == '(' || (sym) == '[' || (sym) == '{')
#define MATCH_CLOSE(sym) ((sym) == ')' ? '(' : (sym) == ']' ? \
	'[' : (sym) == '}' ? '{' : 0)

static int check(char *text)
{
	struct bracket *list = NULL, **cur = &list;
	int ret = -1;

	for ( ; *text; text++) {
		char brc;

		if (BRC_OPEN(*text)) {
			if (!*cur && !(*cur = (struct bracket *)
					calloc(1, sizeof(struct bracket)))) {
				goto Exit;
			}
			(*cur)->brc = *text;
			(*cur)->prev = cur;
			cur = &(*cur)->next;
		} else if ((brc = MATCH_CLOSE(*text))) {
			if (cur == &list || brc != ((struct bracket *)cur)->brc)
				goto Exit;
			cur = ((struct bracket *)cur)->prev;
		}
	}
	ret = cur == &list ? 0 : -1;
Exit:
	for (cur = &list; *cur; list = *cur) {
		cur = &(*cur)->next;
		free(list);
	}
	return ret;
}

int main(int argc, char **argv)
{
	struct {
		char *str;
		int val;
	} *t, tests[] = {
		{ "a(b)", 0 },
		{ "[{}]", 0 },
		{ "[(]", -1 },
		{ "}{", -1 },
		{ "z([{}-()]{a})", 0 },
		{ "[{}a ] b", 0 },
		{ "", 0 }, 
		{ NULL }
	};

	for (t = tests; t->str; t++) {
		int val = check(t->str);

		printf("check(\"%s\") -> %s (%s)\n", t->str, val ?
			"false" : "true", val == t->val ? "CORRECT": "WRONG");
	}

	return 0;
}

